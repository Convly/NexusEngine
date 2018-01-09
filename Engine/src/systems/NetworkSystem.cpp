#include "Nexus/network.hpp"
#include "Nexus/engine.hpp"
#include "Nexus/frameworks/FrameworkManager.hpp"
#include "Nexus/errors/NetworkTcpException.hpp"

nx::NetworkSystem::NetworkSystem()
	:
	nx::SystemTpl(__NX_NETWORK_KEY__),
	_framework_m(std::make_shared<nx::FrameworkManager<nx::NetworkFrameworkTpl>>(__NX_NETWORK_KEY__, true)) {
  this->connect(nx::EVENT::NETWORK_TCP_ACCEPT, nx::NetworkSystem::event_NetworkTcpAccept);
  this->connect(nx::EVENT::NETWORK_TCP_CONNECT, nx::NetworkSystem::event_NetworkTcpConnect);
  this->connect(nx::EVENT::NETWORK_TCP_SEND, nx::NetworkSystem::event_NetworkTcpSend);
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

void nx::NetworkSystem::event_NetworkTcpAccept(const nx::Event &e) {
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

  const nx::NetworkSystem::TcpAcceptEvent *waitDataEvent;

  waitDataEvent = reinterpret_cast<const nx::NetworkSystem::TcpAcceptEvent*>(e.data.data());

  nx::Log::debug(waitDataEvent->_port);

  try
  {
	  self->getFramework()->tcpStartAccept(waitDataEvent->_port);
  }
  catch (...)
  {
	  std::cerr << "error1" << std::endl;
  }
}

void nx::NetworkSystem::event_NetworkTcpConnect(const nx::Event &e) {
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

  const nx::NetworkSystem::TcpConnectEvent *connectEvent;

  connectEvent = reinterpret_cast<const nx::NetworkSystem::TcpConnectEvent*>(e.data.data());

  try
  {
	  self->getFramework()->tcpStartConnect(connectEvent->_ip, connectEvent->_port);
  }
  catch (...)
  {
	  std::cerr << "error2" << std::endl;
  }
}

void nx::NetworkSystem::event_NetworkTcpSend(const nx::Event &e) {
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

  const nx::NetworkSystem::TcpSendEvent *event;

  event = reinterpret_cast<const nx::NetworkSystem::TcpSendEvent*>(e.data.data());

  std::vector<char> data;

  try
  {
	  self->getFramework()->tcpSend(event->id, event->event);
  }
  catch (...)
  {
	  std::cerr << "error3" << std::endl;
  }
}