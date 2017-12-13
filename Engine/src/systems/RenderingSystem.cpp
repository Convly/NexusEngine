#include "Nexus/rendering.hpp"
#include "Nexus/engine.hpp"
#include "Nexus/frameworks/FrameworkManager.hpp"

nx::RenderingSystem::RenderingSystem()
:
	nx::SystemTpl(__NX_RENDERING_KEY__),
	_framework_m(std::make_shared<nx::FrameworkManager<nx::RenderingFrameworkTpl>>(__NX_RENDERING_KEY__, true))
{
	this->connect("RenderingEventKey", nx::RenderingSystem::event_RenderingEventKey);
}

nx::RenderingSystem::~RenderingSystem() {

}

 nx::RenderingFrameworkTpl* nx::RenderingSystem::getFramework()
{
	return this->_framework_m->getFramework();
}

void nx::RenderingSystem::init()
{

}

void nx::RenderingSystem::update()
{
	auto f = this->getFramework();
	if (!f)
		nx::Log::print("Framework is nullptr");
	else
		f->TriggerRenderingEvent();
	std::cout << "Update for " << this->getName() << std::endl;
}

bool nx::RenderingSystem::checkIntegrity() const
{
	if (this->_framework_m->getFramework()) {
		return true;
	}
	return false;
}

void nx::RenderingSystem::event_RenderingEventKey(const nx::Event& e)
{
	auto& engine = nx::Engine::Instance();
	// We use the getSystemByName method to get a shared_ptr on the SystemTpl* instance of our choice.
	// Then we cast it into the system of our choice
	auto self = nx::Engine::cast<nx::RenderingSystem>(engine.getSystemByName(__NX_RENDERING_KEY__));
	// If the cast fails, our self variable is set to nullptr
	if (!self) return;

	// We can now use public member functions of the System
	self->getName();
	// As well as the public functions of the engine.
	engine.ping();
	// Finally we obviously also have access to the name and the data of the Event
	nx::Log::inform(e.data);
}