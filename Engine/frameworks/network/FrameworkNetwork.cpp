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
	nx::Log::inform("[FRAMEWORK NETWORK] event.type: [" + std::to_string(event.type) + "]");
	nx::Log::inform("[FRAMEWORK NETWORK] event.arg: [" + std::string(event.data.data()) + "]");

	auto const ptr = reinterpret_cast<char*>(&event);
	std::vector<char> data(ptr, ptr + sizeof event);
	data.reserve(4000);

	std::cout << "before udp start" << std::endl;
	this->_udp.startSend(ip, port, data);
	std::cout << "after udp start" << std::endl;
}
