#include "Nexus/networkclient.hpp"
#include "Nexus/engine.hpp"
#include "Nexus/frameworks/FrameworkManager.hpp"

nx::NetworkClientSystem::NetworkClientSystem()
:
	nx::SystemTpl(__NX_NETWORKCLIENT_KEY__),
	_framework_m(std::make_shared<nx::FrameworkManager<nx::NetworkClientFrameworkTpl>>(__NX_NETWORKCLIENT_KEY__, true))
{
	connect(nx::EVENT::NETCUST_CONNECT, nx::NetworkClientSystem::event_Connect);
	connect(nx::EVENT::NETSERV_CONNECT, nx::NetworkClientSystem::event_ConnectAcceptor);
	connect(nx::EVENT::NETCUST_DISCONNECT, nx::NetworkClientSystem::event_Disconnect);
	connect(nx::EVENT::NETCUST_SEND_EVENT, nx::NetworkClientSystem::event_SendEvent);
	connect(nx::EVENT::ENV_CLIENT_KEYBOARD, nx::NetworkClientSystem::event_EnvClientKeyboard);
}

nx::NetworkClientSystem::~NetworkClientSystem() {

}

 nx::NetworkClientFrameworkTpl* nx::NetworkClientSystem::getFramework()
{
	return this->_framework_m->getFramework();
}

void nx::NetworkClientSystem::init()
{

}

void nx::NetworkClientSystem::update()
{
}

bool nx::NetworkClientSystem::checkIntegrity() const
{
	if (this->_framework_m->getFramework()) {
		return true;
	}
	return false;
}

void nx::NetworkClientSystem::event_Connect(const nx::Event& e)
{
	auto& engine = nx::Engine::Instance();
	auto self = nx::Engine::cast<nx::NetworkClientSystem>(engine.getSystemByName(__NX_NETWORKCLIENT_KEY__));
	if (!self) return;
	
	auto f = self->getFramework();
	if (!f) {
		nx::Log::warning("NetworkClient framework is corrupted", "NETWORK_SERVER_INTEGRITY");
		return;
	}

	f->connect(external::any_cast<nx::netcust_host_t>(e.data));
}

void nx::NetworkClientSystem::event_ConnectAcceptor(const nx::Event& e)
{
	auto& engine = nx::Engine::Instance();
	auto self = nx::Engine::cast<nx::NetworkClientSystem>(engine.getSystemByName(__NX_NETWORKCLIENT_KEY__));
	if (!self) return;
	
	auto f = self->getFramework();
	if (!f) {
		nx::Log::warning("NetworkClient framework is corrupted", "NETWORK_SERVER_INTEGRITY");
		return;
	}

	nx::netserv_client_t client = external::any_cast<nx::netserv_client_t>(e.data);
	nx::Log::inform("Connection established with host, registered as " + client.ip_ + std::to_string(client.port_) + " with ID " + std::to_string(client.id_));
	f->setClientId(client.id_);
}

void nx::NetworkClientSystem::event_Disconnect(const nx::Event& e)
{
	auto& engine = nx::Engine::Instance();
	auto self = nx::Engine::cast<nx::NetworkClientSystem>(engine.getSystemByName(__NX_NETWORKCLIENT_KEY__));
	if (!self) return;
	
	auto f = self->getFramework();
	if (!f) {
		nx::Log::warning("NetworkClient framework is corrupted", "NETWORK_SERVER_INTEGRITY");
		return;
	}

	f->disconnect();
}

void nx::NetworkClientSystem::event_SendEvent(const nx::Event& e)
{
	auto& engine = nx::Engine::Instance();
	auto self = nx::Engine::cast<nx::NetworkClientSystem>(engine.getSystemByName(__NX_NETWORKCLIENT_KEY__));
	if (!self) return;

	auto f = self->getFramework();
	if (!f)
	{
		nx::Log::warning("NetworkClient framework is corrupted", "NETWORK_SERVER_INTEGRITY");
		return;
	}

	nx::Event event = external::any_cast<nx::Event>(e.data);
	f->sendEvent(event);
}

void nx::NetworkClientSystem::event_EnvClientKeyboard(const nx::Event& e)
{
	auto& engine = nx::Engine::Instance();
	auto self = engine.cast<nx::NetworkClientSystem>(engine.getSystemByName(__NX_NETWORKCLIENT_KEY__));
	if (!self) return;

	auto f = self->getFramework();
	if (!f)
	{
		nx::Log::warning("NetworkClient framework is corrupted", "NETWORk_CLIENT_INTEGRITY");
		return;
	}

	nx::netserv_send_board_t netBoard = external::any_cast<nx::netserv_send_board_t>(e.data);
	netBoard.clientId_ = f->getClientId();
	f->sendEvent(nx::Event(nx::EVENT::ENV_CLIENT_KEYBOARD, netBoard));
}