#include "FrameworkRendering.hpp"

FrameworkRendering::FrameworkRendering(nx::Engine* engine)
	:
	nx::RenderingFrameworkTpl("FrameworkRendering"),
	_engine(engine),
	_win(nullptr),
	_handler(nullptr)
{
	std::cout << "New Rendering Framework created" << std::endl;
}

FrameworkRendering::~FrameworkRendering()
{
	std::cout << "New Rendering Framework deleted" << std::endl;
}

void FrameworkRendering::InitializeWindow(int width, int height, std::string titleWin)
{
	this->_win = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), titleWin);
	this->_handler = std::make_shared<GUIHandler>(this->_win);

	std::shared_ptr<GUILayer> layer = std::make_shared<GUILayer>("MainLayer");
	std::shared_ptr<Button> button = std::make_shared<Button>(sf::Vector2f(100, 100), sf::Vector2f(50, 30), "MyFirstButton");
	button->update();
	layer->add(button);
	this->_handler->addLayer(layer);
}

void FrameworkRendering::RefreshRendering()
{
	if (this->_win && this->_handler) 
	{
		while (this->_win->isOpen())
		{
			// Getting input events
			sf::Event Event;

			while (this->_win->pollEvent(Event))
			{
				if (Event.type == sf::Event::Closed)
					this->_win->close();
			}
			
			// Clearing the window
			this->_win->clear(sf::Color(0,0,0,255));

			// Drawing stuff on screen
			this->_handler->drawLayers();

			/*sf::RectangleShape r(sf::Vector2f(100, 100));
			r.setFillColor(sf::Color(100, 250, 50));

			this->_win->draw(r);*/

			// Displaying screen
			this->_win->display();
		}
	}
}