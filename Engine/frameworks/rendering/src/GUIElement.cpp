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

void	GUIElement::onClick()
{

}


// Setters
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