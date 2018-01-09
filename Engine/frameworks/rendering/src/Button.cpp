#include "Button.hpp"

Button::Button(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, bool const isPushButton, ColorInfo const& colorInfo, TextInfo const& textInfo) :
	GUIElement(pos, size, identifier), _state(false), _isPushButton(isPushButton),
	_backgroundColor(colorInfo.backgroundColor), _borderColor(colorInfo.borderColor), _borderThickness(colorInfo.borderThickness),
	_font(sf::Font()), _body(sf::RectangleShape(size))
{
	this->_font.loadFromFile(textInfo.fontPath);
	this->_label = sf::Text(textInfo.textLabel, this->_font, textInfo.fontSize);
	this->_label.setFillColor(textInfo.textColor);
	this->_label.setStyle(textInfo.textStyle);
	this->_label.setPosition(pos.x + this->getSize().x / 2.0f - this->_label.getLocalBounds().width / 2.0f,
							 pos.y + this->getSize().y / 2.0f - this->_label.getLocalBounds().height / 2.0f - this->_borderThickness * 2);

	this->_body.setPosition(pos);
	this->_body.setFillColor(colorInfo.backgroundColor);
	this->_body.setOutlineThickness(colorInfo.borderThickness);
	this->_body.setOutlineColor(colorInfo.borderColor);

	this->setSize(sf::Vector2f(this->getSize().x + colorInfo.borderThickness, this->getSize().y + colorInfo.borderThickness));
}

Button::~Button()
{

}


// GUIElement's mouse event methods overload

void Button::onMoveInside(sf::Vector2i const& pos)
{
	//Will be called when mouse is moving into the element
	nx::Log::inform("Mouse moving inside the button '" + this->getIdentifier() + "'");
}

void Button::onMoveOutside(sf::Vector2i const& pos)
{
	//Will be called when mouse is moving outside the element
	nx::Log::inform("Mouse moving outside the button '" + this->getIdentifier() + "'");
}

void Button::onLeftClickPressedInside(sf::Vector2i const& pos)
{
	//Will be called when the element has been left-clicked
	nx::Log::inform("Left-click pressed inside the button '" + this->getIdentifier() + "'");
	this->_state = !this->_state;
	this->onStateChanged();
}

void Button::onLeftClickReleasedInside(sf::Vector2i const& pos)
{
	//Will be called when the element has been left-released
	nx::Log::inform("Left-click released inside the button '" + this->getIdentifier() + "'");
	if (this->_isPushButton)
	{
		bool oldState = this->_state;

		this->_state = false;
		if (this->_state != oldState)
			this->onStateChanged();
	}
}

void Button::onRightClickPressedInside(sf::Vector2i const& pos)
{
	//Will be called when the element has been right-clicked
	nx::Log::inform("Right-click pressed inside the button '" + this->getIdentifier() + "'");
}

void Button::onRightClickReleasedInside(sf::Vector2i const& pos)
{
	//Will be called when the element has been right-released
	nx::Log::inform("Right-click released inside the button '" + this->getIdentifier() + "'");
}

void Button::onLeftClickPressedOutside(sf::Vector2i const& pos)
{
	//Will be called when a left-click is outside the element
	nx::Log::inform("Left-click pressed outside the button '" + this->getIdentifier() + "'");
}

void Button::onLeftClickReleasedOutside(sf::Vector2i const& pos)
{
	//Will be called when a left-release is outside the element
	nx::Log::inform("Left-click released outside the button '" + this->getIdentifier() + "'");
	if (this->_isPushButton)
	{
		bool oldState = this->_state;

		this->_state = false;
		if (this->_state != oldState)
			this->onStateChanged();
	}
}

void Button::onRightClickPressedOutside(sf::Vector2i const& pos)
{
	//Will be called when a right-click is outside the element
	nx::Log::inform("Right-click pressed outside the button '" + this->getIdentifier() + "'");
}

void Button::onRightClickReleasedOutside(sf::Vector2i const& pos)
{
	//Will be called when a right-release is outside the element
	nx::Log::inform("Right-click released outside the button '" + this->getIdentifier() + "'");
}

void Button::keyTextEntered(char const charEntered)
{
	//Will be called when text in entered
	nx::Log::inform("Char pressed for the Button '" + this->getIdentifier() + "' is " + charEntered);
}

void Button::keyPressed(sf::Keyboard::Key const& keyPressed)
{
	//Will be called when a key is pressed
	nx::Log::inform("Key pressed for the Button '" + this->getIdentifier());
}

// Display

void Button::show(std::shared_ptr<sf::RenderWindow> const& win)
{
	if (this->isVisible())
	{
		win->draw(this->_body);
		win->draw(this->_label);
	}
}


// Specific functions for this element

void Button::onStateChanged()
{
	//Will be called when the button's state has been changed
	nx::Log::inform("The button '" + this->getIdentifier() + "' state is now " + std::to_string(this->_state));
	if (this->_state)
		this->_body.setFillColor(sf::Color(150, 150, 150, 255));
	else
		this->_body.setFillColor(sf::Color(200, 200, 200, 255));
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
	this->_body.setFillColor(this->_backgroundColor);
}

void	Button::setBorderColor(sf::Color const& color)
{
	this->_borderColor = color;
	this->_body.setOutlineColor(this->_borderColor);
}

void	Button::setBorderThickness(int const thickness)
{
	this->_borderThickness = thickness;
	this->setSize(sf::Vector2f(this->getSize().x + thickness, this->getSize().y + thickness));
	this->_body.setOutlineThickness(this->_borderThickness);
}

void	Button::setPos(sf::Vector2f const& pos)
{
	GUIElement::setPos(sf::Vector2f(pos.x - this->_borderThickness, pos.y - this->_borderThickness));
	this->_body.setPosition(pos);
	this->_label.setPosition(pos.x + this->getSize().x / 2.0f - this->_label.getLocalBounds().width / 2.0f - this->_borderThickness * 2,
							 pos.y + this->getSize().y / 2.0f - this->_label.getLocalBounds().height / 2.0f - this->_borderThickness * 2);
}

void	Button::setSize(sf::Vector2f const& size)
{
	GUIElement::setSize(size);
	this->_body.setSize(sf::Vector2f(size.x - this->_borderThickness * 2, size.y - this->_borderThickness * 2));
	this->_label.setPosition(this->getPos().x + this->getSize().x / 2.0f - this->_label.getLocalBounds().width / 2.0f - this->_borderThickness * 2,
							 this->getPos().y + this->getSize().y / 2.0f - this->_label.getLocalBounds().height / 2.0f - this->_borderThickness * 2);
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