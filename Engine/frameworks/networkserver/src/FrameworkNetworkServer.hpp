#ifndef FRAMEWORK_NETWORKSERVER
# define FRAMEWORK_NETWORKSERVER

#include <future>
#include <iostream>
#include <vector>
#include <memory>
#include <array>
#include <thread>
#include <functional>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/array.hpp>

#include "Nexus/engine.hpp"
#include "Nexus/frameworks/NetworkServerFrameworkTpl.hpp"
#include "Nexus/frameworks/RenderingFrameworkTpl.hpp"
#include "Nexus/standalone/thread/ScopedLock.hpp"
#include "Nexus/standalone/network/netutils.hpp"
#include "Nexus/standalone/network/serialization.hpp"

nx::Engine* enginePtr;

#define NETSERV_MAXCON 4

class FrameworkNetworkServer : public nx::NetworkServerFrameworkTpl
{
	struct UdpServer {
		boost::asio::ip::udp::socket i_server_;
		boost::asio::ip::udp::socket o_server_;
		boost::asio::ip::udp::resolver resolver_;
		boost::asio::ip::udp::endpoint remote_endpoint_;
  		char recv_buffer_[800000];
		std::array<nx::netserv_client_t, NETSERV_MAXCON> clients_;

		explicit UdpServer(boost::asio::io_service& io_service)
		: 	i_server_(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 9898)),
			o_server_(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0)),
			resolver_(io_service)
  		{
			  nx::Log::inform("Udp server started on port 9898, now listening for requests...");
			  start_receive();
  		}
		
		void start_receive()
		{
			i_server_.async_receive_from(
				boost::asio::buffer(recv_buffer_),
				remote_endpoint_,
				boost::bind(&UdpServer::handle_receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		}

  		void handle_receive(const boost::system::error_code& error, size_t bufferSize)
		{
			if (!error || error == boost::asio::error::message_size)
			{
				nx::Log::inform("Query received from " + this->remote_endpoint_.address().to_string() + ":" + std::to_string(this->remote_endpoint_.port()));

				std::string archive_data(&recv_buffer_[0], bufferSize);
				
				nx::UdpEventPacket packet = nx::serialization::deserialize(archive_data);

				external::any obj = nx::nx_any_convert_serialize.at(packet.type_)(packet.object_);
				nx::Event e(packet.type_, obj);

				handleEvent(this->isRemoteAClient(), e);
				start_receive();
			}
		}

		void handleEvent(const bool con_status, nx::Event event)
		{
			if ((	con_status && event.type != nx::EVENT::NETSERV_CONNECT) 
				|| !con_status && (this->getClientListSize() < NETSERV_MAXCON && event.type == nx::EVENT::NETSERV_CONNECT))
			{
				if (!con_status)
				{
					nx::netserv_client_t newClientInfos(-1, nx::NETCON_STATE::UNDEFINED, remote_endpoint_.address().to_string(), remote_endpoint_.port());
					event.data = newClientInfos;
				}
				nx::Log::inform("Re-routing packet of type " + std::to_string(event.type) + " for " + remote_endpoint_.address().to_string() + ":" + std::to_string(remote_endpoint_.port()));
				this->dispatchEvent(event);
			} else {
				std::string err = (con_status)? " attempted to connect twice": " tried to interact with the server without a valid connection";
				nx::Log::inform(remote_endpoint_.address().to_string() + ":" + std::to_string(remote_endpoint_.port()) + err + ", skipping...");
			}
		}

		void dispatchEvent(const nx::Event& e)
		{
			std::future<void> eventEmit(std::async([&]() {
				enginePtr->emit(e);
			}));

			eventEmit.get();
		}

		bool isRemoteAClient() const
		{
			for (auto& client : clients_)
			{
				if (client.ip_ == remote_endpoint_.address().to_string().data() && client.port_ == remote_endpoint_.port())
					return true;
			}
			return false;
		}

		unsigned int getClientListSize() const
		{
			unsigned int k = 0;
			for (const auto& client : clients_)
			{
				if (client.id_ != -1 && client.ip_ != "" && client.port_ != 0)
					++k;
			}
			return k;
		}

		unsigned int getFreeSlot() const 
		{
			nx::thread::ScopedLock lock;
			unsigned int k = 0;
			for (const auto& client : clients_)
			{
				if (client.id_ == -1 && client.ip_[0] == 0 && client.port_ == 0)
					return k;
				++k;
			}
			return -1;
		}

		bool isAValidClient(const uint8_t idx)
		{
			return (idx >= 0 && idx < 4 && clients_[idx].id_ != -1 && clients_[idx].ip_ != "" && clients_[idx].port_ != 0 && clients_[idx].status_ == nx::NETCON_STATE::CONNECTED);
		}

		void sendEvent(nx::netserv_send_event_t& netInfos)
		{
			nx::thread::ScopedLock lock;

			if (!isAValidClient(netInfos.clientId_)) {
				return;
			}

			nx::Log::inform("About to send data to " + std::to_string(netInfos.clientId_));

			nx::netserv_client_t target = clients_[netInfos.clientId_];
			
			boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), std::string(target.ip_).c_str(), std::to_string(target.port_).c_str());
			boost::asio::ip::udp::resolver::iterator it = resolver_.resolve(query);

			nx::Any obj = nx::std_any_convert_serialize.at(netInfos.event_.type)(netInfos.event_.data);
			nx::UdpEventPacket packet(netInfos.event_.type, obj);

			std::string outbound_data = nx::serialization::serialize(packet);

			o_server_.async_send_to(boost::asio::buffer(outbound_data), *it, [&](const boost::system::error_code& error, std::size_t bytes_transferred){});
		}
	};

public:
	explicit FrameworkNetworkServer(nx::Engine*);
	~FrameworkNetworkServer();

public:
	void sendEvent(const nx::netserv_send_event_t& netInfos);
	void sendAll(const nx::netserv_send_event_t& net);
	void disconnect(const int clientId);
	void connectClient(const nx::netserv_client_t& clientInfos);
	void updateScene(const nx::netserv_send_event_t& netInfos);
	const bool isServerFull();

public:
	void setServerFullState(const bool);

protected:
	nx::Engine* _engine;
	bool full_;
	boost::asio::io_service io_service_;
	std::shared_ptr<std::thread> io_thread_;
	FrameworkNetworkServer::UdpServer udp_server_;
};

#if  defined(_MSC_VER)

extern "C"
{
	__declspec(dllexport) FrameworkNetworkServer* CObject(nx::Engine* engine)
	{
		return (new FrameworkNetworkServer(engine));
	}

	__declspec(dllexport) void DObject(FrameworkNetworkServer* obj)
	{
		delete obj;
	}
}

#elif defined(__GNUC__) || defined(__GNUG__)

extern "C"
{
	FrameworkNetworkServer* CObject(nx::Engine* engine)
	{
		return (new FrameworkNetworkServer(engine));
	}

	void DObject(FrameworkNetworkServer* obj)
	{
		delete obj;
	}
}

#endif

#endif
