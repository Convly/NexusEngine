#ifndef FRAMEWORK_NETWORKSERVER
# define FRAMEWORK_NETWORKSERVER

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <vector>
#include <future>
#include <memory>
#include <array>
#include <thread>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/array.hpp>
#include "Nexus/engine.hpp"
#include "Nexus/log.hpp"
#include "Nexus/frameworks/NetworkServerFrameworkTpl.hpp"

extern nx::Engine* enginePtr;

#define NETSERV_MAXCON 4

class FrameworkNetworkServer : public nx::NetworkServerFrameworkTpl
{

	struct UdpServer {
		boost::asio::ip::udp::socket sock_;
		boost::asio::ip::udp::endpoint remote_endpoint_;
  		char recv_buffer_[1024];
		std::array<nx::netserv_client_t, NETSERV_MAXCON> clients_;

		UdpServer(boost::asio::io_service& io_service)
		: sock_(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 9898))
  		{
			start_receive();
  		}
		
		void start_receive()
		{
			sock_.async_receive_from(
				boost::asio::buffer(recv_buffer_),
				remote_endpoint_,
				boost::bind(&UdpServer::handle_receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		}

  		void handle_receive(const boost::system::error_code& error, size_t bufferSize)
		{
			if (!error || error == boost::asio::error::message_size)
			{
				std::cout << "Query received from " << this->remote_endpoint_.address().to_string() << ":" << this->remote_endpoint_.port() << std::endl;

				nx::Event event(nx::EVENT::DEFAULT, {});
				std::string archive_data(&recv_buffer_[0], bufferSize);
				std::stringstream archive_stream(archive_data);
				{
					boost::archive::text_iarchive archive(archive_stream);
					archive >> event;
				}

				bool isConnected = this->isRemoteAClient();
				if ((	isConnected && event.type != nx::EVENT::NETCUST_CONNECT) 
					|| !isConnected && (this->getClientListSize() < NETSERV_MAXCON && event.type == nx::EVENT::NETCUST_CONNECT))
				{
					if (!isConnected)
					{
						nx::netserv_client_t newClientInfos(-1, nx::NETCON_STATE::UNDEFINED, remote_endpoint_.address().to_string(), remote_endpoint_.port());
						std::cout << newClientInfos.ip_ << std::endl;
						event.data = nx::Event::serializer<nx::netserv_client_t>(newClientInfos);
					}
					nx::Log::inform("Re-routing packet of type " + std::to_string(event.type) + " for " + remote_endpoint_.address().to_string() + ":" + std::to_string(remote_endpoint_.port()));
					this->dispatch(event);
				} else {
					nx::Log::inform(remote_endpoint_.address().to_string() + ":" + std::to_string(remote_endpoint_.port()) + " tried to interact with the server without a valid connection, skipping...");
				}

				start_receive();
			}
		}

		void dispatch(const nx::Event& e)
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
				std::cout << client.ip_ << " -- " << remote_endpoint_.address().to_string() << " | " << client.port_ << " -- " << remote_endpoint_.port() << std::endl;
				if (client.ip_ == remote_endpoint_.address().to_string() && client.port_ == remote_endpoint_.port())
					return true;
			}
			return false;
		}

		unsigned int getClientListSize() const
		{
			unsigned int k = 0;
			for (const auto& client : clients_)
			{
				std::cout << "AAA:" << std::strcmp(client.ip_, "") << std::endl;
				if (client.id_ != -1 && !std::strcmp(client.ip_, "") && client.port_ != 0)
					++k;
			}
			std::cout << k << " clients registered" << std::endl;
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

		void send(const nx::netserv_send_infos_t& netInfos)
		{
			// std::cout << "About to send data to " << netInfos.clientId_ << std::endl;
			// 				/// Holds the outbound data.
			// 	std::string outbound_data_;

			// 	/// Holds the inbound data.
			// 	std::vector<char> inbound_data_;
			
			// 	static bool ta = false;
			// 	test t;
			// 	std::string str = "Hello world!\0";
			// 	t.id = 42;
			// 	t.data[0] = 'H';
			// 	t.data[1] = 'e';
			// 	t.data[2] = 'l';
			// 	t.data[3] = 'l';
			// 	t.data[4] = 'o';
			// 	t.data[5] = '\0';
			// 	nx::EVENT ev = (ta)? nx::EVENT::NETSERV_SEND: nx::EVENT::SCRIPT_INIT;
			// 	ta = !ta;
			// 	nx::netserv_udp_t obj(true, nx::Event(ev, nx::Event::serializer<test>(t)));
			
			// 	std::cout<<"Got a connection, and sending.\n";

			// 	std::stringstream ss;
			// 	// boost::archive::text_oarchive archive(ss);
			// 	archive << obj;
			// 	outbound_data_ = ss.str();

			// 	// Write the serialized data to the socket. We use "gather-write" to send
			// 	this->sock_.async_send_to(boost::asio::buffer(outbound_data_), remote_endpoint_, [&](const boost::system::error_code& error, std::size_t bytes_transferred){
			// 		static int sent = 0;
			// 		sent++;
			// 		std::cout << sent << " packet sent" << std::endl;
			// 	});

		}
	};

	struct TcpServer {
		// TODO
	};

public:
	FrameworkNetworkServer(nx::Engine*);
	~FrameworkNetworkServer();

public:
	void send(const nx::netserv_send_infos_t& netInfos);
	void sendAll(const nx::netserv_udp_t& net);
	void disconnect(const uint8_t clientId);
	void connectClient(const nx::netserv_client_t& clientInfos);
	
protected:
	nx::Engine* _engine;
	boost::asio::io_service io_service_;
	std::shared_ptr<boost::thread> io_thread_;
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
