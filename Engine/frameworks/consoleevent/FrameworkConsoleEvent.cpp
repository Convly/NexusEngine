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

	nx::NetworkSystem::WaitDataEvent waitDataEvent;

	waitDataEvent._localhost = false;
	waitDataEvent._port = 4242;

	auto const ptr = reinterpret_cast<char*>(&waitDataEvent);
	std::vector<char> data(ptr, ptr + sizeof waitDataEvent);
	this->_engine->emit("NetworkWaitData", data);
  } else if (event == "connect") {
	nx::NetworkSystem::ConnectEvent connectEvent;

	connectEvent._ip = "127.0.0.1";
	connectEvent._port = 4242;

	auto const ptr = reinterpret_cast<char*>(&connectEvent);
	std::vector<char> data(ptr, ptr + sizeof connectEvent);
	this->_engine->emit("NetworkConnect", data);

	nx::Log::inform("[ConsoleEvent] Connect (TCP) to localhost");
  } else if (event == "send") {
	nx::Log::print("Please enter data string for send to localhost !!!");
	std::string data;
	std::cin >> data;
	// emit
	nx::Log::inform("[ConsoleEvent] Data send: [" + data + "]");
	nx::Log::inform("[ConsoleEvent] Send data (TCP) to localhost");
  }
}