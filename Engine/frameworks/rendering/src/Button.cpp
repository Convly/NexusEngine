#include "Button.hpp"

Button::Button(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, const nx::rendering::MouseEventsContainer& events, bool const isPushButton, ColorInfo const& colorInfo, TextInfo const& textInfo) :
	GUIElement(pos, size, identifier, events), _state(false), _isPushButton(isPushButton),
	_borderColor(colorInfo.borderColor), _borderThickness(colorInfo.borderThickness),
	_font(sf::Font()), _body(sf::RectangleShape(size)), _colorNotSelected(colorInfo.backgroundColor), _colorSelected(colorInfo.backgroundColor)
{
	this->_font.loadFromFile(textInfo.fontPath);
	this->_label = sf::Text(textInfo.textLabel, this->_font, textInfo.fontSize);
	this->_label.setFillColor(textInfo.textColor);
	this->_label.setStyle(textInfo.textStyle);
	this->_recenteringLabelText();

	this->_body.setPosition(pos);
	this->_body.setFillColor(colorInfo.backgroundColor);
	this->_body.setOutlineThickness(colorInfo.borderThickness);
	this->_body.setOutlineColor(colorInfo.borderColor);

	this->setSize(sf::Vector2f(this->getSize().x + colorInfo.borderThickness, this->getSize().y + colorInfo.borderThickness));
}

Button::~Button()
{

}


// Specific functions for this element

void Button::_onStateChanged()
{
	//Will be called when the button's state has been changed
	if (this->_state)
		this->_body.setFillColor(this->_colorSelected);
	else
		this->_body.setFillColor(this->_colorNotSelected);
}

void Button::_recenteringLabelText()
{
	this->_label.setPosition(this->getPos().x + this->getSize().x / 2.0f - this->_label.getLocalBounds().width / 2.0f,
							 this->getPos().y + this->getSize().y / 2.0f - this->_label.getLocalBounds().height / 2.0f - this->_borderThickness * 2);
}

// GUIElement's mouse event methods overload

void Button::onLeftClickPressedInside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onLeftClickPressedInside");
	
	//Will be called when the element has been left-clicked
	this->_state = !this->_state;
	this->_onStateChanged();
}

void Button::onLeftClickReleasedInside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onLeftClickReleasedInside");

	//Will be called when the element has been left-released
	if (this->_isPushButton)
	{
		bool oldState = this->_state;

		this->_state = false;
		if (this->_state != oldState)
			this->_onStateChanged();
	}
}

void Button::onLeftClickReleasedOutside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onLeftClickReleasedOutside");

	//Will be called when a left-release is outside the element
	if (this->_isPushButton)
	{
		bool oldState = this->_state;

		this->_state = false;
		if (this->_state != oldState)
			this->_onStateChanged();
	}
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


// Setters
void	Button::setState(bool const state)
{
	this->_state = state;
}

void	Button::setLabel(sf::Text const& label)
{
	this->_label = label;
}

void	Button::setText(std::string const& text)
{
	this->_label.setString(text);
	this->_recenteringLabelText();
}

void	Button::setFontSize(unsigned int const fontSize)
{
	this->_label.setCharacterSize(fontSize);
	this->_recenteringLabelText();
}

void	Button::setColorNotSelected(sf::Color const& color)
{
	this->_colorNotSelected = color;
	this->_body.setFillColor(this->_colorNotSelected);
}

void	Button::setColorSelected(sf::Color const& color)
{
	this->_colorSelected = color;
	this->_body.setFillColor(this->_colorSelected);
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
	this->_recenteringLabelText();
}

void	Button::setSize(sf::Vector2f const& size)
{
	GUIElement::setSize(size);
	this->_body.setSize(sf::Vector2f(size.x - this->_borderThickness * 2, size.y - this->_borderThickness * 2));
	this->_recenteringLabelText();
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

std::string const	Button::getText() const
{
	return (this->_label.getString().toAnsiString());
}

unsigned int const	Button::getFontSize() const
{
	return (this->_label.getCharacterSize());
}

sf::Color const &	Button::getColorNotSelected() const
{
	return (this->_colorNotSelected);
}

sf::Color const &	Button::getColorSelected() const
{
	return (this->_colorSelected);
}

sf::Color const &	Button::getBorderColor() const
{
	return (this->_borderColor);
}

int const			Button::getBorderThickness() const
{
	return (this->_borderThickness);
}