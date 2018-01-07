#include "FrameworkConsoleEvent.hpp"

FrameworkConsoleEvent::FrameworkConsoleEvent(nx::Engine *engine)
	:
	_thread(&FrameworkConsoleEvent::start, this),
	nx::ConsoleEventFrameworkTpl("FrameworkConsoleEvent"),
	_engine(engine) {
  std::cout << "New ConsoleEvent Framework created" << std::endl;
}

FrameworkConsoleEvent::~FrameworkConsoleEvent() {
  std::cout << "New ConsoleEvent Framework deleted" << std::endl;
}

void FrameworkConsoleEvent::start() {
  nx::Log::inform("[ConsoleEvent] Starting ...");

  std::string data;

  while (1) {
	std::cin >> data;
	std::cout << "DATA: [" << data << "]" << std::endl;
	this->runEvent(data);
	data.clear();
  }
}

void FrameworkConsoleEvent::runEvent(std::string event) {
  if (event == "listen") {
	nx::Log::inform("[ConsoleEvent] Listen (TCP) on localhost");

	nx::NetworkSystem::TcpAcceptEvent waitDataEvent;

	waitDataEvent._localhost = false;
	waitDataEvent._port = 4242;

	auto const ptr = reinterpret_cast<char*>(&waitDataEvent);
	std::vector<char> data(ptr, ptr + sizeof waitDataEvent);
	this->_engine->emit(nx::EVENT::NETWORK_TCP_ACCEPT, data);
  } else if (event == "connect") {
	nx::NetworkSystem::TcpConnectEvent connectEvent;

	connectEvent._ip = "127.0.0.1";
	connectEvent._port = 4242;

	auto const ptr = reinterpret_cast<char*>(&connectEvent);
	std::vector<char> data(ptr, ptr + sizeof connectEvent);
	this->_engine->emit(nx::EVENT::NETWORK_TCP_CONNECT, data);

	nx::Log::inform("[ConsoleEvent] Connect (TCP) to localhost");
  } else if (event == "sendC") {
	std::vector<char> data_r = {'e', 'r', 't'};

	auto eventR = nx::Event(nx::EVENT::SCRIPT_INIT, data_r);
	nx::NetworkSystem::TcpSendEvent tcpSendEvent = {1, eventR};

	auto const ptr = reinterpret_cast<char*>(&tcpSendEvent);
	std::vector<char> data(ptr, ptr + sizeof tcpSendEvent);
	this->_engine->emit(nx::EVENT::NETWORK_TCP_SEND, data);

	nx::Log::inform("[ConsoleEvent] Data send: [" + std::string(data_r.data()) + "]");
	nx::Log::inform("[ConsoleEvent] Send data (TCP) to localhost");
  }
}