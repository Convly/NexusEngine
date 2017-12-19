#include "Nexus/network.hpp"
#include "Nexus/engine.hpp"
#include "Nexus/frameworks/FrameworkManager.hpp"

nx::NetworkSystem::NetworkSystem()
	:
	nx::SystemTpl(__NX_NETWORK_KEY__),
	_framework_m(std::make_shared<nx::FrameworkManager<nx::NetworkFrameworkTpl>>(__NX_NETWORK_KEY__, true)) {
  this->connect("NetworkEventKey", nx::NetworkSystem::event_NetworkEventKey);
}

nx::NetworkSystem::~NetworkSystem() {

}

nx::NetworkFrameworkTpl *nx::NetworkSystem::getFramework() {
  return this->_framework_m->getFramework();
}

void nx::NetworkSystem::init() {

}

void nx::NetworkSystem::update() {
  auto f = this->getFramework();
  if (!f)
	nx::Log::print("Framework is nullptr");
  //std::cout << "Update for " << this->getName() << std::endl;
}

bool nx::NetworkSystem::checkIntegrity() const {
  if (this->_framework_m->getFramework()) {
	return true;
  }
  return false;
}

void nx::NetworkSystem::event_NetworkEventKey(const nx::Event &e) {
  auto &engine = nx::Engine::Instance();
  // We use the getSystemByName method to get a shared_ptr on the SystemTpl* instance of our choice.
  // Then we cast it into the system of our choice
  auto self = nx::Engine::cast<nx::NetworkSystem>(engine.getSystemByName(__NX_NETWORK_KEY__));
  // If the cast fails, our self variable is set to nullptr
  if (!self) return;

  // We can now use public member functions of the System
  self->getName();
  // As well as the public functions of the engine.
  engine.ping();
  // Finally we obviously also have access to the name and the data of the Event
  nx::Log::inform(e.data);
}