#include "GUIElement.hpp"

GUIElement::GUIElement(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, const std::vector<std::pair<std::string, std::string> >& events) :
	_pos(pos), _size(size), _identifier(identifier), _isVisible(true), _events(events)
{

}

GUIElement::GUIElement(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier) :
	_pos(pos), _size(size), _identifier(identifier), _isVisible(true)
{

}

GUIElement::~GUIElement()
{

}

// Tools

void GUIElement::dispatchMouseEvent(sf::Vector2i const& pos, std::string const& eventName)
{
	std::for_each(
		this->_events.begin(),
		this->_events.end(),
		[&](std::pair<std::string, std::string>& item) {
			if (item.first == eventName) {
				nx::Engine::Instance().emit(nx::EVENT::SCRIPT_RUN, nx::Event::stringToVector(item.second));
			}
		}
	);
}

// Mouse events

void	GUIElement::onMoveInside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onMoveInside");
}

void	GUIElement::onMoveOutside(sf::Vector2i const& pos)
{

}

void	GUIElement::onLeftClickPressedInside(sf::Vector2i const& pos)
{

}

void	GUIElement::onLeftClickReleasedInside(sf::Vector2i const& pos)
{

}

void	GUIElement::onRightClickPressedInside(sf::Vector2i const& pos)
{

}

void	GUIElement::onRightClickReleasedInside(sf::Vector2i const& pos)
{

}

void	GUIElement::onLeftClickPressedOutside(sf::Vector2i const& pos)
{

}

void	GUIElement::onLeftClickReleasedOutside(sf::Vector2i const& pos)
{

}

void	GUIElement::onRightClickPressedOutside(sf::Vector2i const& pos)
{

}

void	GUIElement::onRightClickReleasedOutside(sf::Vector2i const& pos)
{

}


// Setters

void	GUIElement::setPos(sf::Vector2f const& pos)
{
	this->_pos = pos;
}

void	GUIElement::setSize(sf::Vector2f const& size)
{
	this->_size = size;
}

void	GUIElement::setVisible(bool const state)
{
	this->_isVisible = state;
}

// Getters

sf::Vector2f const &	GUIElement::getPos() const
{
	return (this->_pos);
}

sf::Vector2f const &	GUIElement::getSize() const
{
	return (this->_size);
}

std::string	const &		GUIElement::getIdentifier() const
{
	return (this->_identifier);
}

bool					GUIElement::isVisible() const
{
	return (this->_isVisible);
}

std::vector<std::pair<std::string, std::string> > const& GUIElement::getEvents() const
{
	return this->_events;
}