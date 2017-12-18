#include "Nexus/${__NX_LOWER_SYSTEM__}.hpp"
#include "Nexus/engine.hpp"
#include "Nexus/frameworks/FrameworkManager.hpp"

nx::${__NX_BASE_SYSTEM__}System::${__NX_BASE_SYSTEM__}System()
:
	nx::SystemTpl(__NX_${__NX_UPPER_SYSTEM__}_KEY__),
	_framework_m(std::make_shared<nx::FrameworkManager<nx::${__NX_BASE_SYSTEM__}FrameworkTpl>>(__NX_${__NX_UPPER_SYSTEM__}_KEY__, true))
{
	this->connect("${__NX_BASE_SYSTEM__}EventKey", nx::${__NX_BASE_SYSTEM__}System::event_${__NX_BASE_SYSTEM__}EventKey);
}

nx::${__NX_BASE_SYSTEM__}System::~${__NX_BASE_SYSTEM__}System() {

}

 nx::${__NX_BASE_SYSTEM__}FrameworkTpl* nx::${__NX_BASE_SYSTEM__}System::getFramework()
{
	return this->_framework_m->getFramework();
}

void nx::${__NX_BASE_SYSTEM__}System::init()
{

}

void nx::${__NX_BASE_SYSTEM__}System::update()
{
	auto f = this->getFramework();
	if (!f)
		nx::Log::print("Framework is nullptr");
	else
		f->Trigger${__NX_BASE_SYSTEM__}Event();
	std::cout << "Update for " << this->getName() << std::endl;
}

bool nx::${__NX_BASE_SYSTEM__}System::checkIntegrity() const
{
	if (this->_framework_m->getFramework()) {
		return true;
	}
	return false;
}

void nx::${__NX_BASE_SYSTEM__}System::event_${__NX_BASE_SYSTEM__}EventKey(const nx::Event& e)
{
	auto& engine = nx::Engine::Instance();
	// We use the getSystemByName method to get a shared_ptr on the SystemTpl* instance of our choice.
	// Then we cast it into the system of our choice
	auto self = nx::Engine::cast<nx::${__NX_BASE_SYSTEM__}System>(engine.getSystemByName(__NX_${__NX_UPPER_SYSTEM__}_KEY__));
	// If the cast fails, our self variable is set to nullptr
	if (!self) return;

	// We can now use public member functions of the System
	self->getName();
	// As well as the public functions of the engine.
	engine.ping();
	// Finally we obviously also have access to the name and the data of the Event
	nx::Log::inform(e.data);
}