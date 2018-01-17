#include "GraphicsHandler.hpp"
#include "Nexus/log.hpp"

nx::graphics::GraphicsHandler::GraphicsHandler(std::shared_ptr<sf::RenderWindow> const& win):
	_win(win)
{

}
nx::graphics::GraphicsHandler::GraphicsHandler::~GraphicsHandler()
{

}

void	nx::graphics::GraphicsHandler::addElement(std::shared_ptr<GraphicsElement> elem)
{
	this->_graphicsElements.push_back(elem);
}


// Events

void nx::graphics::GraphicsHandler::processEvent(sf::Event const& event)
{
	for (auto itElem : this->_graphicsElements)
	{
		if (itElem->isVisible())
		{
			sf::Rect<float> rect(itElem->getPos(), itElem->getSize());

			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (rect.contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
						itElem->onLeftClickPressedInside(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
					else
						itElem->onLeftClickPressedOutside(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				}
				else if (event.type == sf::Event::MouseButtonReleased)
				{
					if (rect.contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
						itElem->onLeftClickReleasedInside(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
					else
						itElem->onLeftClickReleasedOutside(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				}
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (rect.contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
						itElem->onRightClickPressedInside(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
					else
						itElem->onRightClickPressedOutside(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				}
				else if (event.type == sf::Event::MouseButtonReleased)
				{
					if (rect.contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
						itElem->onRightClickReleasedInside(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
					else
						itElem->onRightClickReleasedOutside(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				}
			}
			if (event.type == sf::Event::MouseMoved)
			{
				if (rect.contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
					itElem->onMoveInside(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
				else
					itElem->onMoveOutside(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
			}
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128)
					itElem->keyTextEntered(static_cast<char>(event.text.unicode));
			}
			if (event.type == sf::Event::KeyPressed)
				itElem->keyPressed(event.key.code);
		}
	}
}


// Display

void nx::graphics::GraphicsHandler::drawElements()
{
	for (auto itElem : this->_graphicsElements)
	{
		itElem->show(this->_win);
	}
}


// Getters

std::vector<std::shared_ptr<nx::graphics::GraphicsElement>>	const &			nx::graphics::GraphicsHandler::getElements() const
{
	return (this->_graphicsElements);
}

std::vector<std::shared_ptr<nx::graphics::GraphicsElement>>&			nx::graphics::GraphicsHandler::getElements()
{
	return (this->_graphicsElements);
}

std::shared_ptr<nx::graphics::GraphicsElement> const &			nx::graphics::GraphicsHandler::getElementByName(std::string const& identifier) const
{
	for (auto &it : this->_graphicsElements)
	{
		if (it->getIdentifier() == identifier)
			return (it);
	}
	throw (nx::LayerNotFoundException(identifier));
}

std::shared_ptr<nx::graphics::GraphicsElement>&			nx::graphics::GraphicsHandler::getElementByName(std::string const& identifier)
{
	for (auto &it : this->_graphicsElements)
	{
		if (it->getIdentifier() == identifier)
			return (it);
	}
	throw (nx::LayerNotFoundException(identifier));
}

const bool		nx::graphics::GraphicsHandler::object_exists(const std::string& identifier) const
{
	for (auto &it : this->_graphicsElements)
	{
		if (it->getIdentifier() == identifier)
			return (true);
	}

	return (false);
}