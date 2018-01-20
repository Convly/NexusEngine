#include "Nexus/network.hpp"
#include "Nexus/engine.hpp"
#include "Nexus/frameworks/FrameworkManager.hpp"

nx::NetworkSystem::NetworkSystem()
:
	nx::SystemTpl(__NX_NETWORK_KEY__),
	_framework_m(std::make_shared<nx::FrameworkManager<nx::NetworkFrameworkTpl>>(__NX_NETWORK_KEY__, true))
{

}

nx::NetworkSystem::~NetworkSystem() {

}

 nx::NetworkFrameworkTpl* nx::NetworkSystem::getFramework()
{
	return this->_framework_m->getFramework();
}

void nx::NetworkSystem::init()
{

}

void nx::NetworkSystem::update()
{
	auto f = this->getFramework();
	if (!f)
		nx::Log::print("Framework is nullptr");
	else
		f->pingNetworkFramework();
	std::cout << "Update for " << this->getName() << std::endl;
}

bool nx::NetworkSystem::checkIntegrity() const
{
	if (this->_framework_m->getFramework()) {
		return true;
	}
	return false;
}