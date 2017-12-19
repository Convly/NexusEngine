#include "PushButton.hpp"

PushButton::PushButton(sf::Vector2f pos, sf::Vector2f size, std::string const& identifier, std::string const& label) :
	GUIElement(pos, size, identifier), _state(false), _label(label)
{

}

PushButton::~PushButton()
{

}


// GUIElement's mouse event methods overload

void PushButton::onEnter()
{
	//Will be called when mouse is entering into the element
}

void PushButton::onLeave()
{
	//Will be called when mouse is leaving the element
}

void PushButton::onClick()
{
	//Will be called when the element has been clicked
	this->_state = !this->_state;
	this->onStateChanged();
}

// Specific functions for this element

void PushButton::onStateChanged()
{
	//Will be called when the push button's state has been changed
}


// Getters

bool PushButton::getState() const
{
	return (this->_state);
}

std::string PushButton::getLabel() const
{
	return (this->_label);
}