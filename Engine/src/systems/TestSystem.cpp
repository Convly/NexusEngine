#include "Nexus/test.hpp"
#include "Nexus/engine.hpp"

nx::TestSystem::TestSystem()
:
	nx::SystemTpl(__SYSTEM_KEY__),
	_framework_m(__SYSTEM_KEY__, true)
{
	this->connect("TestEventKey", nx::TestSystem::event_TestEventKey);
}

nx::TestSystem::~TestSystem() {

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

void nx::TestSystem::event_TestEventKey(const nx::Event& e)
{
	auto& engine = nx::Engine::Instance();
	// We use the getSystemByName method to get a shared_ptr on the SystemTpl* instance of our choice.
	// Then we cast it into the system of our choice
	auto self = nx::Engine::cast<nx::TestSystem>(engine.getSystemByName("test"));
	// If the cast fails, our self variable is set to nullptr
	if (!self) return;

	// We can now use public member functions of the System
	self->getName();
	// As well as the public functions of the engine.
	engine.ping();
	// Finally we obviously also have access to the name and the data of the Event
	nx::Log::inform(e.data);
}