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

void	GUIElement::clearShapes()
{
	this->_shapes.clear();
}

void	GUIElement::addToShapes(std::shared_ptr<sf::Shape> const& shape)
{
	this->_shapes.push_back(shape);
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

std::vector<std::shared_ptr<sf::Shape>> const &	GUIElement::getShapes() const
{
	return (this->_shapes);
}