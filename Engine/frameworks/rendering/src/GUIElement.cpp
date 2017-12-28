#include "GUIElement.hpp"

GUIElement::GUIElement(sf::Vector2f pos, sf::Vector2f size, std::string const& identifier) :
	_pos(pos), _size(size), _identifier(identifier), _isVisible(true)
{

}
GUIElement::~GUIElement()
{

}


// Mouse events

void	GUIElement::onEnter()
{

}

void	GUIElement::onLeave()
{

}

void	GUIElement::onLeftClickPressedInside()
{

}

void	GUIElement::onLeftClickReleasedInside()
{

}

void	GUIElement::onRightClickPressedInside()
{

}

void	GUIElement::onRightClickReleasedInside()
{

}

void	GUIElement::onLeftClickPressedOutside()
{

}

void	GUIElement::onLeftClickReleasedOutside()
{

}

void	GUIElement::onRightClickPressedOutside()
{

}

void	GUIElement::onRightClickReleasedOutside()
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