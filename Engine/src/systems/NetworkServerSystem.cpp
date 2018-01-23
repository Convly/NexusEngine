#include "Nexus/networkserver.hpp"
#include "Nexus/engine.hpp"
#include "Nexus/frameworks/FrameworkManager.hpp"

nx::NetworkServerSystem::NetworkServerSystem()
:
	nx::SystemTpl(__NX_NETWORKSERVER_KEY__),
	_framework_m(std::make_shared<nx::FrameworkManager<nx::NetworkServerFrameworkTpl>>(__NX_NETWORKSERVER_KEY__, true))
{
	this->connect(nx::EVENT::NETSERV_SEND, nx::NetworkServerSystem::event_Send);
	this->connect(nx::EVENT::NETSERV_SEND_ALL, nx::NetworkServerSystem::event_SendAll);
	this->connect(nx::EVENT::NETSERV_FORCE_DISCONNECT, nx::NetworkServerSystem::event_Disconnect);
	this->connect(nx::EVENT::NETCUST_CONNECT, nx::NetworkServerSystem::event_Connect);
}

nx::NetworkServerSystem::~NetworkServerSystem() {

}

 nx::NetworkServerFrameworkTpl* nx::NetworkServerSystem::getFramework()
{
	return this->_framework_m->getFramework();
}

void nx::NetworkServerSystem::init()
{

}

void nx::NetworkServerSystem::update()
{

}

bool nx::NetworkServerSystem::checkIntegrity() const
{
	if (this->_framework_m->getFramework()) {
		return true;
	}
	return false;
}

void nx::NetworkServerSystem::event_Send(const nx::Event& e)
{
	auto& engine = nx::Engine::Instance();
	auto self = nx::Engine::cast<nx::NetworkServerSystem>(engine.getSystemByName(__NX_NETWORKSERVER_KEY__));
	if (!self) return;
	
	auto f = self->getFramework();
	if (!f) {
		nx::Log::warning("NetworkServer framework is corrupted", "NETWORK_SERVER_INTEGRITY");
		return;
	}

	nx::netserv_send_infos_t netInfos = nx::Event::deserializer<nx::netserv_send_infos_t>(e.data);

	f->send(netInfos);
}

void nx::NetworkServerSystem::event_SendAll(const nx::Event& e)
{
	auto& engine = nx::Engine::Instance();
	auto self = nx::Engine::cast<nx::NetworkServerSystem>(engine.getSystemByName(__NX_NETWORKSERVER_KEY__));
	if (!self) return;
	
	auto f = self->getFramework();
	if (!f) {
		nx::Log::warning("NetworkServer framework is corrupted", "NETWORK_SERVER_INTEGRITY");
		return;
	}

	nx::netserv_udp_t net = nx::Event::deserializer<nx::netserv_udp_t>(e.data);

	f->sendAll(net);
}

void nx::NetworkServerSystem::event_Disconnect(const nx::Event& e)
{
	auto& engine = nx::Engine::Instance();
	auto self = nx::Engine::cast<nx::NetworkServerSystem>(engine.getSystemByName(__NX_NETWORKSERVER_KEY__));
	if (!self) return;
	
	auto f = self->getFramework();
	if (!f) {
		nx::Log::warning("NetworkServer framework is corrupted", "NETWORK_SERVER_INTEGRITY");
		return;
	}

	uint8_t clientId = nx::Event::deserializer<uint8_t>(e.data);

	f->disconnect(clientId);
}

void nx::NetworkServerSystem::event_Connect(const nx::Event& e)
{
	auto& engine = nx::Engine::Instance();
	auto self = nx::Engine::cast<nx::NetworkServerSystem>(engine.getSystemByName(__NX_NETWORKSERVER_KEY__));
	if (!self) return;

	auto f = self->getFramework();
	if (!f) {
		nx::Log::warning("NetworkServer framework is corrupted", "NETWORK_SERVER_INTEGRITY");
		return ;
	}

	nx::netserv_client_t clientInfos = nx::Event::deserializer<nx::netserv_client_t>(e.data);

	std::cout << "YOLO: " << clientInfos.id_ << " - " << clientInfos.ip_ << " - " << clientInfos.port_ << " - " << clientInfos.status_ << " - " << std::endl;
	f->connectClient(clientInfos);
}