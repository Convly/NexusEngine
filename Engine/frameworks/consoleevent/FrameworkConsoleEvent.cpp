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
	//std::pair<std::string, std::string> data("127.0.0.1", "4242");
	//this->_engine->emit("NetworkConnect");
  } else if (event == "connect") {
	// emit
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