#include "FrameworkNetwork.hpp"

FrameworkNetwork::FrameworkNetwork(nx::Engine *engine)
	:
	nx::NetworkFrameworkTpl("FrameworkNetwork"),
	_engine(engine) {
  std::cout << "New Network Framework created" << std::endl;
}

FrameworkNetwork::~FrameworkNetwork() {
  std::cout << "New Network Framework deleted" << std::endl;
}

void FrameworkNetwork::TriggerNetworkEvent() {
  this->_engine->emit("NetworkEventKey", "NetworkEventValue");
}

void FrameworkNetwork::listen(std::string port) {
}

void FrameworkNetwork::connect(std::string ip, std::string port) {
}
