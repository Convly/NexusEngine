#ifndef FRAMEWORK_NETWORKCLIENT
# define FRAMEWORK_NETWORKCLIENT

#include <iostream>
#include <vector>
#include <future>
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

class FrameworkNetworkClient : public nx::NetworkClientFrameworkTpl
{
	struct UdpClient {
		std::string ip_;
		unsigned short port_;
		boost::asio::ip::udp::socket sock_;
		boost::asio::ip::udp::resolver resolver_;
		boost::asio::ip::udp::resolver::query query;
		boost::asio::ip::udp::endpoint remote_endpoint_;
		boost::asio::ip::udp::resolver::iterator it;
  		char recv_buffer_[800000];
		int clientId_ = -1;

		UdpClient(boost::asio::io_service& io_service, const std::string& ip, const unsigned short port)
		:
			ip_(ip),
			port_(port),
			sock_(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0)),
			resolver_(io_service),
      		query(boost::asio::ip::udp::v4(), ip_.c_str(), std::to_string(port))
  		{
			  it = resolver_.resolve(query);
			  nx::Log::inform("Udp network client started...");
			  start_receive();
  		}

		  ~UdpClient()
		  {
			  
		  }
		
		void start_receive()
		{
			sock_.async_receive_from(
				boost::asio::buffer(recv_buffer_),
				remote_endpoint_,
				boost::bind(&UdpClient::handle_receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		}

  		void handle_receive(const boost::system::error_code& error, size_t bufferSize)
		{
			if (!error || error == boost::asio::error::message_size)
			{
				std::string archive_data(&recv_buffer_[0], bufferSize);
				
				nx::UdpEventPacket packet = nx::serialization::deserialize(archive_data);

				external::any obj = nx::nx_any_convert_serialize.at(packet.type_)(packet.object_);
				nx::Event e(packet.type_, obj);

				this->dispatchEvent(e);
				start_receive();
			}
		}

		void handleEvent(const bool con_status, nx::Event event)
		{

		}

		void dispatchEvent(const nx::Event e)
		{
			std::future<void> eventEmit(std::async([&]() {
				enginePtr->emit(e);
			}));

			eventEmit.get();
		}

		void sendEvent(const nx::Event& event)
		{
			nx::thread::ScopedLock lock;
			
			boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), std::string(ip_).c_str(), std::to_string(port_).c_str());
			boost::asio::ip::udp::resolver::iterator it = resolver_.resolve(query);

			nx::Event& e = const_cast<nx::Event&>(event);
			nx::Any obj = nx::std_any_convert_serialize.at(e.type)(e.data);
			nx::UdpEventPacket packet(event.type, obj);

			std::string outbound_data = nx::serialization::serialize(packet);

			sock_.async_send_to(boost::asio::buffer(outbound_data), *it, [&](const boost::system::error_code& error, std::size_t bytes_transferred){});
		}

		void setClientId(const int id)
		{
			clientId_ = id;
		}

		const int getClientId()
		{
			return clientId_;
		}
	};
public:
	explicit FrameworkNetworkClient(nx::Engine*);
	~FrameworkNetworkClient();

public:
	const bool connected() const;
	void setConnect(const bool conn);
	
protected:
	nx::Engine* _engine;
	bool connected_;
	boost::asio::io_service io_service_;
	std::shared_ptr<std::thread> io_thread_;
	std::shared_ptr<FrameworkNetworkClient::UdpClient> udp_client_;

public:
	void sendEvent(const nx::Event&);
	void connect(const nx::netcust_host_t&);
	void disconnect();
	int getClientId();
	void setClientId(const int);
};

#if  defined(_MSC_VER)

extern "C"
{
	__declspec(dllexport) FrameworkNetworkClient* CObject(nx::Engine* engine)
	{
		return (new FrameworkNetworkClient(engine));
	}

	__declspec(dllexport) void DObject(FrameworkNetworkClient* obj)
	{
		delete obj;
	}
}

#elif defined(__GNUC__) || defined(__GNUG__)

extern "C"
{
	FrameworkNetworkClient* CObject(nx::Engine* engine)
	{
		return (new FrameworkNetworkClient(engine));
	}

	void DObject(FrameworkNetworkClient* obj)
	{
		delete obj;
	}
}

#endif

#endif
