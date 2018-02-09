#include "Nexus/networkclient.hpp"
#include "Nexus/engine.hpp"
#include "Nexus/frameworks/FrameworkManager.hpp"

nx::NetworkClientSystem::NetworkClientSystem()
:
	nx::SystemTpl(__NX_NETWORKCLIENT_KEY__),
	_framework_m(std::make_shared<nx::FrameworkManager<nx::NetworkClientFrameworkTpl>>(__NX_NETWORKCLIENT_KEY__, true))
{
	this->connect(nx::EVENT::NETCUST_CONNECT, nx::NetworkClientSystem::event_Connect);
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