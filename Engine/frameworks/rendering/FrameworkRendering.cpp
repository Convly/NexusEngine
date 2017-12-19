#include "FrameworkRendering.hpp"

FrameworkRendering::FrameworkRendering(nx::Engine* engine)
	:
	nx::RenderingFrameworkTpl("FrameworkRendering"),
	_engine(engine),
	_win(nullptr)
{
	std::cout << "New Rendering Framework created" << std::endl;
}

FrameworkRendering::~FrameworkRendering()
{
	std::cout << "New Rendering Framework deleted" << std::endl;
}

void FrameworkRendering::InitializeWindow(int width, int height, std::string titleWin)
{
	this->_win = std::make_shared<sf::Window>(sf::VideoMode(width, height), titleWin);
}

void FrameworkRendering::RefreshRendering()
{
	if (this->_win) 
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
			// Drawing stuff on screen
			//this->_handler.drawGUIElements();

			// Displaying screen
			this->_win->display();
		}
	}
}