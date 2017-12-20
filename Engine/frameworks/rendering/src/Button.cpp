#include "Button.hpp"

Button::Button(sf::Vector2f pos, sf::Vector2f size, std::string const& identifier, bool const isPushButton, sf::Text const& text) :
	GUIElement(pos, size, identifier), _state(false), _label(text), _backgroundColor(sf::Color(200, 200, 200, 255)),
	_borderColor(sf::Color(0, 0, 0, 255)), _isPushButton(isPushButton)
{
	this->update();
}

Button::~Button()
{

}


// GUIElement's mouse event methods overload

void Button::onEnter()
{
	//Will be called when mouse is entering into the element
}

void Button::onLeave()
{
	//Will be called when mouse is leaving the element
}

void Button::onClick()
{
	//Will be called when the element has been clicked
	if (!this->_isPushButton)
	{
		this->_state = !this->_state;
		this->onStateChanged();
	}
}

// Display

void Button::update()
{
	// TODO: Finish the Button drawing
	this->clearShapes();

	std::shared_ptr<sf::RectangleShape> body = std::make_shared<sf::RectangleShape>(this->getSize());

	body->setFillColor(this->_backgroundColor);
	body->setOutlineThickness(this->_borderThickness);
	body->setOutlineColor(this->_borderColor);

	this->addToShapes(body);
}


// Specific functions for this element

void Button::onStateChanged()
{
	//Will be called when the button's state has been changed
}


// Setters
void	Button::setState(bool const state)
{
	this->_state = state;
}

void	Button::setLabel(sf::Text const& label)
{
	this->_label = label;
}

void	Button::setBackgroundColor(sf::Color const& color)
{
	this->_backgroundColor = color;
}

void	Button::setBorderColor(sf::Color const& color)
{
	this->_borderColor = color;
}

void	Button::setBorderThickness(int const thickness)
{
	this->_borderThickness = thickness;
}

// Getters

std::string	const	Button::getType() const
{
	return ("Button");
}


// Specific getters

bool const			Button::getState() const
{
	return (this->_state);
}

sf::Text const &	Button::getLabel() const
{
	return (this->_label);
}

sf::Color const &	Button::getBackgroundColor() const
{
	return (this->_backgroundColor);
}

sf::Color const &	Button::getBorderColor() const
{
	return (this->_borderColor);
}

int const			Button::getBorderThickness() const
{
	return (this->_borderThickness);
}