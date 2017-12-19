#include "FrameworkConsoleEvent.hpp"

FrameworkConsoleEvent::FrameworkConsoleEvent(nx::Engine *engine)
	:
	nx::ConsoleEventFrameworkTpl("FrameworkConsoleEvent"),
	_engine(engine) {
  std::cout << "New ConsoleEvent Framework created" << std::endl;
}

FrameworkConsoleEvent::~FrameworkConsoleEvent() {
  std::cout << "New ConsoleEvent Framework deleted" << std::endl;
}

void FrameworkConsoleEvent::TriggerConsoleEventEvent() {
  this->_engine->emit("ConsoleEventEventKey", "ConsoleEventEventValue");
}