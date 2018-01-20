#include "Nexus/networkclient.hpp"
#include "Nexus/engine.hpp"
#include "Nexus/frameworks/FrameworkManager.hpp"

nx::NetworkClientSystem::NetworkClientSystem()
:
	nx::SystemTpl(__NX_NETWORKCLIENT_KEY__),
	_framework_m(std::make_shared<nx::FrameworkManager<nx::NetworkClientFrameworkTpl>>(__NX_NETWORKCLIENT_KEY__, true))
{

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
	auto f = this->getFramework();
	if (!f)
		nx::Log::print("Framework is nullptr");
	else
		f->pingNetworkClientFramework();
	std::cout << "Update for " << this->getName() << std::endl;
}

bool nx::NetworkClientSystem::checkIntegrity() const
{
	if (this->_framework_m->getFramework()) {
		return true;
	}
	return false;
}