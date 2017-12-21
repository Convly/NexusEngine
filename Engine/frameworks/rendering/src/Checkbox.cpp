#include "Checkbox.hpp"

Checkbox::Checkbox(sf::Vector2f pos, sf::Vector2f size, std::string const& identifier) :
	GUIElement(pos, size, identifier), _state(State::UNCHECKED)
{

}

Checkbox::~Checkbox()
{

}


// GUIElement's mouse event methods overload

void Checkbox::onEnter()
{
	//Will be called when mouse is entering into the element
}

void Checkbox::onLeave()
{
	//Will be called when mouse is leaving the element
}

void Checkbox::onClick()
{
	//Will be called when the element has been clicked
	if (this->_state != State::UNCHECKED)
		this->_state = State::UNCHECKED;
	else
		this->_state = State::CHECKED;
}

// Display

void Checkbox::show(std::shared_ptr<sf::RenderWindow> const& win)
{
	// TODO: Draw the Checkbox
}


// Specific functions for this element

void Checkbox::onStateChanged()
{
	//Will be called when the button's state has been changed
}


// Setters
void		Checkbox::setState(State const state)
{
	this->_state = state;
}

void		Checkbox::setBackgroundColor(sf::Color const& color)
{
	this->_backgroundColor = color;
}

void		Checkbox::setBorderColor(sf::Color const& color)
{
	this->_borderColor = color;
}

void		Checkbox::setBorderThickness(int const thickness)
{
	this->_borderThickness = thickness;
}

// Getters

std::string	const	Checkbox::getType() const
{
	return ("Checkbox");
}


// Specific getters

Checkbox::State const Checkbox::getState() const
{
	return (this->_state);
}

sf::Color const	&	Checkbox::getBackgroundColor() const
{
	return (this->_backgroundColor);
}

sf::Color const	&	Checkbox::getBorderColor() const
{
	return (this->_borderColor);
}

int const			Checkbox::getBorderThickness() const
{
	return (this->_borderThickness);
}