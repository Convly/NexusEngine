#include "GUIElement.hpp"

GUIElement::GUIElement(sf::Vector2f pos, sf::Vector2f size, std::string const& identifier) :
	_pos(pos), _size(size), _identifier(identifier)
{

}
GUIElement::~GUIElement()
{

}


// Mouse events

void GUIElement::onEnter()
{

}

void GUIElement::onLeave()
{

}

void GUIElement::onClick()
{

}


// Display

void GUIElement::show()
{

}


// Getters

sf::Vector2f GUIElement::getPos() const
{
	return (this->_pos);
}

sf::Vector2f GUIElement::getSize() const
{
	return (this->_size);
}

std::string GUIElement::getIdentifier() const
{
	return (this->_identifier);
}