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
  std::cout << "[consoleEvent] END START" << std::endl;
}

struct MaStruct {
  MaStruct(int id_, const nx::Event& event_) : id(id_), event(event_) {}
  int id;
  nx::Event event;
};

struct MyData {
  std::string name;
  int id;
};

void FrameworkConsoleEvent::runEvent(std::string event) {
  if (event == "listen") {
	{
	  nx::Log::inform("[ConsoleEvent] Listen (TCP) on localhost");

	  nx::NetworkSystem::TcpAcceptEvent waitDataEvent;

	  waitDataEvent._localhost = false;
	  waitDataEvent._port = 4242;

	  auto const ptr = reinterpret_cast<char *>(&waitDataEvent);
	  std::vector<char> data(ptr, ptr + sizeof waitDataEvent);
	  this->_engine->emit(nx::EVENT::NETWORK_TCP_ACCEPT, data);
	}
  } else if (event == "connect") {
	  {
	  nx::NetworkSystem::TcpConnectEvent connectEvent;

	  connectEvent._ip = "192.168.65.2";
	  connectEvent._port = 4242;

	  auto const ptr = reinterpret_cast<char *>(&connectEvent);
	  std::vector<char> data(ptr, ptr + sizeof connectEvent);
	  this->_engine->emit(nx::EVENT::NETWORK_TCP_CONNECT, data);

	  nx::Log::inform("[ConsoleEvent] Connect (TCP) to localhost");
	}
  } else if (event == "sendC") {
	{
	  std::string data_s = "scriptInit.c";
	  auto const ptr2 = reinterpret_cast<char*>(&data_s);
	  std::vector<char> data_r(ptr2, ptr2 + sizeof(data_s));

	  nx::Event eventR = nx::Event(nx::EVENT::SCRIPT_INIT, data_r);
	  nx::NetworkSystem::TcpSendEvent tcpSendEvent = {1, eventR};

	  auto const ptr = reinterpret_cast<char *>(&tcpSendEvent);
	  std::vector<char> data(ptr, ptr + sizeof(tcpSendEvent));
	  nx::Event eventE(nx::EVENT::NETWORK_TCP_SEND, data);
	  this->_engine->emit(eventE);

	  nx::Log::inform("[ConsoleEvent] Data send: [" + std::string(data_r.data()) + "]");
	  nx::Log::inform("[ConsoleEvent] Send data (TCP) to localhost");

	  const nx::NetworkSystem::TcpSendEvent *eventT;

	  eventT = reinterpret_cast<const nx::NetworkSystem::TcpSendEvent *>(eventE.data.data());
	}

  }
  else if (event == "recv")
  {
	  nx::NetworkSystem::UdpReceiveEvent receiveDataEvent;

	  receiveDataEvent._port = 4242;

	  auto const ptr = reinterpret_cast<char*>(&receiveDataEvent);
	  std::vector<char> data(ptr, ptr + sizeof receiveDataEvent);
	  this->_engine->emit(nx::EVENT::NETWORK_UDP_RECEIVE, data);
	  nx::Log::inform("[ConsoleEvent] startReceive (UDP) on localhost");
  }
  else if (event == "send")
  {
// -------- create event to send

	  // create argument
	  std::string random = "hey";
	  std::vector<char> data_r = nx::Event::stringToVector(random.c_str());

	  // create event with argument inside
	  auto eventR = nx::Event(nx::EVENT::SCRIPT_INIT, data_r);

// -------- create event to trigger

	  // create event for system
	  nx::NetworkSystem::UdpSendEvent sendDataEvent = { "127.0.0.1", 4242, eventR };

	  // convert event to vector<char>
	  auto const ptr = reinterpret_cast<char*>(&sendDataEvent);
	  std::vector<char> data(ptr, ptr + sizeof sendDataEvent);

	  nx::Log::inform("[ConsoleEvent] event.type: [" + std::to_string(sendDataEvent._event.type) + "]");
	  nx::Log::inform("[ConsoleEvent] event.arg: [" + std::string(sendDataEvent._event.data.data()) + "]");

// -------- emit the event
	  this->_engine->emit(nx::EVENT::NETWORK_UDP_SEND, data);
	  nx::Log::inform("[ConsoleEvent] Send data (UDP) to localhost");
  }
}