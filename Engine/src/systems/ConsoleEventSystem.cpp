#include "Nexus/consoleevent.hpp"
#include "Nexus/engine.hpp"
#include "Nexus/frameworks/FrameworkManager.hpp"

nx::ConsoleEventSystem::ConsoleEventSystem()
	:
	nx::SystemTpl(__NX_CONSOLEEVENT_KEY__),
	_framework_m(std::make_shared<nx::FrameworkManager<nx::ConsoleEventFrameworkTpl>>(__NX_CONSOLEEVENT_KEY__, true)) {
}

nx::ConsoleEventSystem::~ConsoleEventSystem() {

}

nx::ConsoleEventFrameworkTpl *nx::ConsoleEventSystem::getFramework() {
  return this->_framework_m->getFramework();
}

void nx::ConsoleEventSystem::init() {
}

void nx::ConsoleEventSystem::update() {
  auto f = this->getFramework();
  if (!f)
	nx::Log::print("Framework is nullptr");
  //std::cout << "Update for " << this->getName() << std::endl;
}

bool nx::ConsoleEventSystem::checkIntegrity() const {
  if (this->_framework_m->getFramework()) {
	return true;
  }
  return false;
}

void nx::ConsoleEventSystem::event_ConsoleEventEventKey(const nx::Event &e) {
  auto &engine = nx::Engine::Instance();
  // We use the getSystemByName method to get a shared_ptr on the SystemTpl* instance of our choice.
  // Then we cast it into the system of our choice
  auto self = nx::Engine::cast<nx::ConsoleEventSystem>(engine.getSystemByName(__NX_CONSOLEEVENT_KEY__));
  // If the cast fails, our self variable is set to nullptr
  if (!self) return;

  // We can now use public member functions of the System
  self->getName();
  // As well as the public functions of the engine.
  engine.ping();
  // Finally we obviously also have access to the name and the data of the Event
  nx::Log::inform(e.data);
}