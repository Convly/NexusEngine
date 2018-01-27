#ifndef FRAMEWORK_NETWORKSERVER
# define FRAMEWORK_NETWORKSERVER

#include <iostream>
#include <vector>
#include <future>
#include <memory>
#include <array>
#include <thread>
#include <functional>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/array.hpp>
#include "Nexus/engine.hpp"
#include "Nexus/frameworks/NetworkServerFrameworkTpl.hpp"
#include "Nexus/frameworks/RenderingFrameworkTpl.hpp"
#include "Any.hpp"
#include "Nexus/standalone/external/any.hpp"
#include "Nexus/standalone/thread/ScopedLock.hpp"

extern nx::Engine* enginePtr;

struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

#define NETSERV_MAXCON 4

static const std::unordered_map<nx::EVENT, std::function<external::any(nx::Any&)>, EnumClassHash> nx_any_convert_serialize = {
	{nx::EVENT::SCRIPT_RUN,					[&](nx::Any& object) -> external::any {return nx::Anycast<std::string>(object);}},
	{nx::EVENT::SCRIPT_LOAD,				[&](nx::Any& object) -> external::any {return nx::Anycast<std::string>(object);}},
	{nx::EVENT::SCRIPT_INIT,				[&](nx::Any& object) -> external::any {return nx::Anycast<std::string>(object);}},
	{nx::EVENT::SCRIPT_UPDATE,				[&](nx::Any& object) -> external::any {return nx::Anycast<std::string>(object);}},
	{nx::EVENT::SCRIPT_EXEC_FUNCTION,		[&](nx::Any& object) -> external::any {return nx::Anycast<nx::script::ScriptInfos>(object);}},
	{nx::EVENT::NETCUST_CONNECT,			[&](nx::Any& object) -> external::any {return std::string("");}},
	{nx::EVENT::NETCUST_DISCONNECT,			[&](nx::Any& object) -> external::any {return std::string();}},
	{nx::EVENT::NETCUST_LISTEN,				[&](nx::Any& object) -> external::any {return nx::Anycast<std::string>(object);}},
	{nx::EVENT::NETCUST_SEND,				[&](nx::Any& object) -> external::any {return nx::Anycast<std::string>(object);}},
	{nx::EVENT::NETSERV_SEND,				[&](nx::Any& object) -> external::any {return nx::Anycast<nx::netserv_send_event_t>(object);}},
	{nx::EVENT::NETSERV_SEND_ALL,			[&](nx::Any& object) -> external::any {return nx::Anycast<nx::netserv_send_event_t>(object);}},
	{nx::EVENT::NETSERV_FORCE_DISCONNECT,	[&](nx::Any& object) -> external::any {return nx::Anycast<uint8_t>(object);}}
};

static const std::unordered_map<nx::EVENT, std::function<nx::Any(external::any&)>, EnumClassHash> std_any_convert_serialize = {
	{nx::EVENT::SCRIPT_RUN,					[&](external::any& object) -> nx::Any {return external::any_cast<std::string>(object);}},
	{nx::EVENT::SCRIPT_LOAD,				[&](external::any& object) -> nx::Any {return external::any_cast<std::string>(object);}},
	{nx::EVENT::SCRIPT_INIT,				[&](external::any& object) -> nx::Any {return external::any_cast<std::string>(object);}},
	{nx::EVENT::SCRIPT_UPDATE,				[&](external::any& object) -> nx::Any {return external::any_cast<std::string>(object);}},
	{nx::EVENT::SCRIPT_EXEC_FUNCTION,		[&](external::any& object) -> nx::Any {return external::any_cast<nx::script::ScriptInfos>(object);}},
	{nx::EVENT::NETCUST_CONNECT,			[&](external::any& object) -> nx::Any {return std::string();}},
	{nx::EVENT::NETCUST_DISCONNECT,			[&](external::any& object) -> nx::Any {return std::string();}},
	{nx::EVENT::NETCUST_LISTEN,				[&](external::any& object) -> nx::Any {return external::any_cast<std::string>(object);}},
	{nx::EVENT::NETCUST_SEND,				[&](external::any& object) -> nx::Any {return external::any_cast<std::string>(object);}},
	{nx::EVENT::NETSERV_SEND,				[&](external::any& object) -> nx::Any {return external::any_cast<nx::netserv_send_event_t>(object);}},
	{nx::EVENT::NETSERV_SEND_ALL,			[&](external::any& object) -> nx::Any {return external::any_cast<nx::netserv_send_event_t>(object);}},
	{nx::EVENT::NETSERV_FORCE_DISCONNECT,	[&](external::any& object) -> nx::Any {return external::any_cast<uint8_t>(object);}}
};

class FrameworkNetworkServer : public nx::NetworkServerFrameworkTpl
{

	struct UdpEventPacket {
		UdpEventPacket() {}
		UdpEventPacket(const nx::EVENT type, const nx::Any& object) : type_(type), object_(object) {}
		UdpEventPacket(const UdpEventPacket& other) : type_(other.type_), object_(other.object_) {}
		
		nx::EVENT type_;
		nx::Any object_;

		template <typename Archive>
		void serialize(Archive& ar, unsigned int version)
		{
			ar & type_;
			ar & object_;
		}
	};

	struct UdpServer {
		boost::asio::ip::udp::socket i_server_;
		boost::asio::ip::udp::socket o_server_;
		boost::asio::ip::udp::resolver resolver_;
		boost::asio::ip::udp::endpoint remote_endpoint_;
  		char recv_buffer_[1024];
		std::array<nx::netserv_client_t, NETSERV_MAXCON> clients_;

		UdpServer(boost::asio::io_service& io_service)
		: 	i_server_(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 9898)),
			o_server_(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0)),
			resolver_(io_service)
  		{
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

				UdpEventPacket packet;

				std::string archive_data(&recv_buffer_[0], bufferSize);
				std::stringstream archive_stream(archive_data);
				{
					boost::archive::text_iarchive archive(archive_stream);
					archive >> packet;
				}

				external::any obj = nx_any_convert_serialize.at(packet.type_)(packet.object_);
				nx::Event e(packet.type_, obj);

				handleEvent(this->isRemoteAClient(), e);
				start_receive();
			}
		}

		void handleEvent(const bool con_status, nx::Event event)
		{
			if ((	con_status && event.type != nx::EVENT::NETCUST_CONNECT) 
				|| !con_status && (this->getClientListSize() < NETSERV_MAXCON && event.type == nx::EVENT::NETCUST_CONNECT))
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
				if (!std::strcmp(client.ip_, remote_endpoint_.address().to_string().data()) && client.port_ == remote_endpoint_.port())
					return true;
			}
			return false;
		}

		unsigned int getClientListSize() const
		{
			unsigned int k = 0;
			for (const auto& client : clients_)
			{
				if (client.id_ != -1 && std::strcmp(client.ip_, "") && client.port_ != 0)
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
			return (idx >= 0 && idx < 4 && clients_[idx].id_ != -1 && std::strcmp(clients_[idx].ip_, "") && clients_[idx].port_ != 0);
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

			std::string outbound_data;
			std::vector<char> inbound_data;

			nx::Any obj = std_any_convert_serialize.at(netInfos.event_.type)(netInfos.event_.data);
			UdpEventPacket packet(netInfos.event_.type, obj);

			std::stringstream ss;
			boost::archive::text_oarchive archive(ss);
			archive << packet;
			outbound_data = ss.str();

			o_server_.async_send_to(boost::asio::buffer(outbound_data), *it, [&](const boost::system::error_code& error, std::size_t bytes_transferred){});
		}
	};

public:
	FrameworkNetworkServer(nx::Engine*);
	~FrameworkNetworkServer();

public:
	void sendEvent(const nx::netserv_send_event_t& netInfos);
	void sendAll(const nx::netserv_send_event_t& net);
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
