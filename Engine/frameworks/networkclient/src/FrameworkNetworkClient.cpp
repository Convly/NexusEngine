#include "FrameworkNetworkClient.hpp"

FrameworkNetworkClient::FrameworkNetworkClient(nx::Engine* engine)
:
	nx::NetworkClientFrameworkTpl("FrameworkNetworkClient"),
	_engine(engine),
	clientId_(-1)
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
	if (this->udp_client_.get()) {
		nx::Log::inform("Client already connected to an host");
		return ;
	}

	this->udp_client_ = std::make_shared<FrameworkNetworkClient::UdpClient>(this->io_service_, host.ip_, host.port_);
	this->io_thread_ = std::make_shared<std::thread>([&]() {
		this->io_service_.run();
	});

	nx::Event e = nx::Event(nx::EVENT::NETSERV_CONNECT, nx::netserv_client_t());
	this->udp_client_->sendEvent(e);
	this->connected_ = true;
	nx::Log::inform("Connected");
}

void FrameworkNetworkClient::disconnect()
{
	if (!connected_)
	{
		nx::Log::inform("No host attached, disconnect operation aborted");
		return;
	}

	this->io_service_.stop();	
	if (this->io_thread_->joinable())
		this->io_thread_->join();
	connected_ = false;
	this->udp_client_.reset();
	nx::Log::inform("You have been successfully disconnected from the host");
}

void FrameworkNetworkClient::send(const nx::netserv_send_event_t& event)
{
}

const bool FrameworkNetworkClient::connected() const
{
	return connected_;
}


void FrameworkNetworkClient::setConnect(const bool conn)
{
	connected_ = conn;
}

int FrameworkNetworkClient::getClientId()
{
	return (connected_)? udp_client_->getClientId(): -1;
}

void FrameworkNetworkClient::setClientId(const int id)
{
	if (connected_)
		udp_client_->setClientId(id);
}
