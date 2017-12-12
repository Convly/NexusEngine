#include "Nexus/test.hpp"
#include "Nexus/engine.hpp"

nx::TestSystem::TestSystem()
:
	nx::SystemTpl(__SYSTEM_KEY__),
	_framework_m(__SYSTEM_KEY__, true)
{

}

nx::TestSystem::~TestSystem() {

}

nx::TestSystem* nx::TestSystem::cast(const std::shared_ptr<nx::SystemTpl>& src)
{
	auto ptr = src.get();
	if (!ptr) return nullptr;
	return dynamic_cast<nx::TestSystem*>(ptr);
}

 nx::TestFrameworkTpl* nx::TestSystem::getFramework()
{
	return this->_framework_m.getFramework();
}

void nx::TestSystem::init()
{

}

void nx::TestSystem::update()
{
	auto f = this->getFramework();
	if (!f)
		nx::Log::print("Framework is nullptr");
	else
		f->TriggerTestEvent();
	std::cout << "Update for " << this->getName() << std::endl;
}

bool nx::TestSystem::checkIntegrity() const
{
	if (this->_framework_m.getFramework()) {
		return true;
	}
	return false;
}