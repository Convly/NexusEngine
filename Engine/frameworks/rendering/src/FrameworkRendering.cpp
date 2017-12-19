#include "FrameworkRendering.hpp"

FrameworkRendering::FrameworkRendering(nx::Engine *engine)
	:
	nx::RenderingFrameworkTpl("FrameworkRendering"),
	_engine(engine) {
  std::cout << "New Rendering Framework created" << std::endl;
}

FrameworkRendering::~FrameworkRendering() {
  std::cout << "New Rendering Framework deleted" << std::endl;
}

void FrameworkRendering::TriggerRenderingEvent() {
  sf::Window App(sf::VideoMode(800, 600), "myproject");

  while (App.isOpen()) {
	sf::Event Event;
	while (App.pollEvent(Event)) {
	  if (Event.type == sf::Event::Closed)
		App.close();
	}
	App.display();
  }
}