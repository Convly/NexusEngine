#include "FrameworkRendering.hpp"

FrameworkRendering::FrameworkRendering(nx::Engine* engine)
:
	nx::RenderingFrameworkTpl("FrameworkRendering"),
	_engine(engine)
{
	nx::Log::inform("New Rendering Framework created");
}

FrameworkRendering::~FrameworkRendering()
{
	nx::Log::inform("New Rendering Framework deleted");
}

void FrameworkRendering::CreateWindow(int x, int y, const std::string& windowTitle)
{
	sf::Window App(sf::VideoMode(x, y), windowTitle);

	while (App.isOpen()) {
		sf::Event Event;
		while (App.pollEvent(Event)) {
			if (Event.type == sf::Event::Closed)
				App.close();
		}
		App.display();
	}
}