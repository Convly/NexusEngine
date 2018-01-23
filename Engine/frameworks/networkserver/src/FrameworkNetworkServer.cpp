#include "FrameworkNetworkServer.hpp"

nx::Engine* enginePtr = nullptr;

FrameworkNetworkServer::FrameworkNetworkServer(nx::Engine* engine)
:
	nx::NetworkServerFrameworkTpl("FrameworkNetworkServer"),
	_engine(engine),
	udp_server_(this->io_service_)
{
	enginePtr = engine;
	this->io_thread_ = std::make_shared<boost::thread>(boost::bind(&boost::asio::io_service::run, &this->io_service_));
}

FrameworkNetworkServer::~FrameworkNetworkServer()
{
	this->io_service_.stop();	
	if (this->io_thread_->joinable())
		this->io_thread_->join();
}

/* TOOLS */

void FrameworkNetworkServer::connectClient(const nx::netserv_client_t& clientInfos)
{
	nx::thread::ScopedLock lock;

	unsigned int freeSlotIndex = this->udp_server_.getFreeSlot();
	if (freeSlotIndex == -1)
	{
		nx::Log::warning("Unable to register " + std::string(clientInfos.ip_) + ":" + std::to_string(clientInfos.port_) + ", server full", "SERVER_FULL_INVALID_CONNECTION");		
		return;
	}
	this->udp_server_.clients_[freeSlotIndex] = clientInfos;
	this->udp_server_.clients_[freeSlotIndex].id_ = static_cast<int>(freeSlotIndex);
	this->udp_server_.clients_[freeSlotIndex].status_ = nx::NETCON_STATE::CONNECTED;
	nx::Log::inform("Register new client " + std::string(clientInfos.ip_) + ":" + std::to_string(clientInfos.port_) + " at slot " + std::to_string(freeSlotIndex));
}

/* INTERFACING */

void FrameworkNetworkServer::send(const nx::netserv_send_infos_t& netInfos)
{
	if (netInfos.prot_ == nx::NETPROT::UDP)
		this->udp_server_.send(netInfos);
	// // Get sender endpoint by netInfos.clientId_ 
	// boost::asio::ip::udp::endpoint sender_endpoint;
	// std::string outbound_data_;

	// std::stringstream ss;
	// boost::archive::text_oarchive archive(ss);
	// archive << netInfos.net_;
	// outbound_data_ = ss.str();
	// this->udp_sock_.send_to(boost::asio::buffer(outbound_data_), sender_endpoint);
}

void FrameworkNetworkServer::sendAll(const nx::netserv_udp_t& net)
{
	// Send to net to all clients;
}

void FrameworkNetworkServer::disconnect(const uint8_t clientId)
{
	// Force disconnect for client nb: clientId
}