#include "FrameworkNetworkServer.hpp"

FrameworkNetworkServer::FrameworkNetworkServer(nx::Engine* engine)
	:
	nx::NetworkServerFrameworkTpl("FrameworkNetworkServer"),
	_engine(engine),
	udp_server_(this->io_service_)
{
	enginePtr = engine;
	this->io_thread_ = std::make_shared<std::thread>([&]() {
		this->io_service_.run();
	});
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
	nx::Log::inform("Registering new client " + std::string(clientInfos.ip_) + ":" + std::to_string(clientInfos.port_) + " at slot " + std::to_string(freeSlotIndex));

	nx::Log::inform("Sending acceptor for new registered client ("+ std::string(clientInfos.ip_) + ":" + std::to_string(clientInfos.port_) + ")");
	nx::netserv_send_event_t s_event;
	s_event.clientId_ = freeSlotIndex;
	s_event.event_ = nx::Event(nx::NETSERV_CONNECT, this->udp_server_.clients_.at(freeSlotIndex));
	sendEvent(s_event);
	nx::Log::inform("Success!");
}

/* INTERFACING */

void FrameworkNetworkServer::sendEvent(const nx::netserv_send_event_t& netInfos)
{
	this->udp_server_.sendEvent(*const_cast<nx::netserv_send_event_t*>(&netInfos));
}

void FrameworkNetworkServer::sendAll(const nx::netserv_send_event_t& netInfos)
{
	if (netInfos.clientId_ == -1) {
		this->sendEvent(netInfos);
		return;
	}

	for (auto& client : udp_server_.clients_)
	{
		if (udp_server_.isAValidClient(client.id_)) {
			this->sendEvent(netInfos);
		}
	}
}

void FrameworkNetworkServer::disconnect(const int clientId)
{
	this->udp_server_.clients_[clientId].status_ = nx::NETCON_STATE::DISCONNECTED;
	nx::Log::inform("Status set to 'DISCONNECTED' for client " + std::to_string(clientId));
}