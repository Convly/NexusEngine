#include "FrameworkNetworkClient.hpp"

FrameworkNetworkClient::FrameworkNetworkClient(nx::Engine* engine)
:
	nx::NetworkClientFrameworkTpl("FrameworkNetworkClient"),
	_engine(engine)
{
	enginePtr = engine;
	nx::Log::inform("New NetworkClient Framework created");
}

FrameworkNetworkClient::~FrameworkNetworkClient()
{
	this->io_service_.stop();	
	if (this->io_thread_->joinable())
		this->io_thread_->join();
}

void FrameworkNetworkClient::connect(const nx::netcust_host_t& host)
{
	if (!this->udp_client_.get()) {
		nx::Log::inform("Client already connected to an host");
		return ;
	}

	this->udp_client_ = std::make_shared<FrameworkNetworkClient::UdpClient>(this->io_service_, host.ip_, host.port_);
	this->io_thread_ = std::make_shared<std::thread>([&]() {
		this->io_service_.run();
	});
}

void FrameworkNetworkClient::disconnect()
{

}

void FrameworkNetworkClient::send(const nx::netserv_send_event_t& event)
{
}