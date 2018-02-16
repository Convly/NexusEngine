#include "Nexus/networkserver.hpp"
#include "Nexus/engine.hpp"
#include "Nexus/frameworks/FrameworkManager.hpp"

nx::NetworkServerSystem::NetworkServerSystem()
:
	nx::SystemTpl(__NX_NETWORKSERVER_KEY__),
	_framework_m(std::make_shared<nx::FrameworkManager<nx::NetworkServerFrameworkTpl>>(__NX_NETWORKSERVER_KEY__, true))
{
	connect(nx::EVENT::NETSERV_SEND, nx::NetworkServerSystem::event_Send);
	connect(nx::EVENT::NETSERV_SEND_ALL, nx::NetworkServerSystem::event_SendAll);
	connect(nx::EVENT::NETSERV_FORCE_DISCONNECT, nx::NetworkServerSystem::event_Disconnect);
	connect(nx::EVENT::NETCUST_DISCONNECT, nx::NetworkServerSystem::event_Disconnect);
	connect(nx::EVENT::NETSERV_CONNECT, nx::NetworkServerSystem::event_Connect);
	connect(nx::EVENT::ENV_UPDATE_SCENE, nx::NetworkServerSystem::event_SceneUpdate);
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

	f->sendEvent(external::any_cast<nx::netserv_send_event_t>(e.data));
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

	f->sendAll(external::any_cast<nx::netserv_send_event_t>(e.data));
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

	f->disconnect(external::any_cast<int>(e.data));
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

	f->connectClient(external::any_cast<nx::netserv_client_t>(e.data));
}

void nx::NetworkServerSystem::event_SceneUpdate(const nx::Event& e)
{
	auto& engine = nx::Engine::Instance();
	auto self = nx::Engine::cast<nx::NetworkServerSystem>(engine.getSystemByName(__NX_NETWORKSERVER_KEY__));
	if (!self) return;

	auto f = self->getFramework();
	if (!f)
	{
		nx::Log::warning("NetorkServer framework is corrupted", "NETWORK_SERVER_INTEGRITY");
		return;
	}
	
	f->updateScene(nx::netserv_send_event_t(-1, e));
}