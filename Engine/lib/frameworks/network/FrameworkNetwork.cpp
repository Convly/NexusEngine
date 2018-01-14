#include "FrameworkNetwork.hpp"

FrameworkNetwork::FrameworkNetwork(nx::Engine *engine)
	:
	nx::NetworkFrameworkTpl("FrameworkNetwork"),
	_engine(engine),
	_tcp(engine),
	_udp(engine){
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
  this->_tcp.send(id, this->convertEventToNetworkData(event));
}

void FrameworkNetwork::udpReceive(unsigned short port)
{
	this->_udp.startReceive(port);
}

void FrameworkNetwork::udpSend(const std::string &ip, unsigned short port, nx::Event event)
{
	this->_udp.startSend(ip, port, this->convertEventToNetworkData(event));
}
