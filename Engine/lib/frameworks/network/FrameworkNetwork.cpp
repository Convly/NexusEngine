#include "FrameworkNetwork.hpp"

FrameworkNetwork::FrameworkNetwork(nx::Engine *engine)
	:
	nx::NetworkFrameworkTpl("FrameworkNetwork"),
	_engine(engine),
	_tcp(engine){
  std::cout << "New Network Framework created" << std::endl;
}

FrameworkNetwork::~FrameworkNetwork() {
  std::cout << "New Network Framework deleted" << std::endl;
}

void FrameworkNetwork::tcpStartAccept(unsigned short port) {
  this->_tcp.startAccept(port);
}

void FrameworkNetwork::tcpStartConnect(std::string ip, unsigned short port) {
  this->_tcp.startConnect(ip, port);
}

void FrameworkNetwork::tcpSend(unsigned int id, nx::Event event) {
  this->_tcp.send(id, event.data);
}