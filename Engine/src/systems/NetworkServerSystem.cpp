#include "Nexus/networkserver.hpp"
#include "Nexus/engine.hpp"
#include "Nexus/frameworks/FrameworkManager.hpp"

nx::NetworkServerSystem::NetworkServerSystem()
:
	nx::SystemTpl(__NX_NETWORKSERVER_KEY__),
	_framework_m(std::make_shared<nx::FrameworkManager<nx::NetworkServerFrameworkTpl>>(__NX_NETWORKSERVER_KEY__, true))
{

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
	auto f = this->getFramework();
	if (!f)
		nx::Log::print("Framework is nullptr");
	else
		f->pingNetworkServerFramework();
	std::cout << "Update for " << this->getName() << std::endl;
}

bool nx::NetworkServerSystem::checkIntegrity() const
{
	if (this->_framework_m->getFramework()) {
		return true;
	}
	return false;
}