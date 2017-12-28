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
	std::shared_ptr<Button> button = std::make_shared<Button>(sf::Vector2f(100, 100), sf::Vector2f(100, 40), "MyFirstButton", true,
															  ColorInfo(sf::Color(200, 200, 200, 255), sf::Color(200, 0, 0, 255), 2),
															  TextInfo("./fonts/Quicksand_Book.otf", "Press me!", 12, sf::Color(0, 0, 0, 255)));
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
			sf::Event event;

			while (this->_win->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					this->_win->close();
				this->_handler->processEvent(event);
			}
			
			// Clearing the window
			this->_win->clear(sf::Color(0, 0 , 0, 255));

			// Drawing stuff on screen
			this->_handler->drawLayers();

			// Displaying screen
			this->_win->display();
		}
	}
}