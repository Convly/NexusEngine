#include "Button.hpp"

nx::gui::Button::Button(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, nx::rendering::MouseEventsContainer const& events,
			   bool const isPushButton, ColorInfo const& colorInfo, TextInfo const& textInfo) :
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
	this->_body.setOutlineThickness(static_cast<float>(colorInfo.borderThickness));
	this->_body.setOutlineColor(colorInfo.borderColor);

	this->setSize(sf::Vector2f(this->getSize().x + colorInfo.borderThickness, this->getSize().y + colorInfo.borderThickness));
}

nx::gui::Button::~Button()
{

}


// Specific functions for this element

void nx::gui::Button::_onStateChanged()
{
	//Will be called when the button's state has been changed
	if (this->_state)
		this->_body.setFillColor(this->_colorSelected);
	else
		this->_body.setFillColor(this->_colorNotSelected);
}

void nx::gui::Button::_recenteringLabelText()
{
	this->_label.setPosition(this->getPos().x + this->getSize().x / 2.0f - this->_label.getLocalBounds().width / 2.0f,
							 this->getPos().y + this->getSize().y / 2.0f - this->_label.getLocalBounds().height / 2.0f - this->_borderThickness * 2);
}

// GUIElement's mouse event methods overload

void nx::gui::Button::onLeftClickPressedInside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onLeftClickPressedInside");
	
	//Will be called when the element has been left-clicked
	this->_state = !this->_state;
	this->_onStateChanged();
}

void nx::gui::Button::onLeftClickReleasedInside(sf::Vector2i const& pos)
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

void nx::gui::Button::onLeftClickReleasedOutside(sf::Vector2i const& pos)
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

void nx::gui::Button::show(std::shared_ptr<sf::RenderWindow> const& win)
{
	if (this->isVisible())
	{
		win->draw(this->_body);
		win->draw(this->_label);
	}
}


// Setters
void	nx::gui::Button::setState(bool const state)
{
	this->_state = state;
}

void	nx::gui::Button::setLabel(sf::Text const& label)
{
	this->_label = label;
}

void	nx::gui::Button::setText(std::string const& text)
{
	this->_label.setString(text);
	this->_recenteringLabelText();
}

void	nx::gui::Button::setFontSize(unsigned int const fontSize)
{
	this->_label.setCharacterSize(fontSize);
	this->_recenteringLabelText();
}

void	nx::gui::Button::setColorNotSelected(sf::Color const& color)
{
	this->_colorNotSelected = color;
	this->_body.setFillColor(this->_colorNotSelected);
}

void	nx::gui::Button::setColorSelected(sf::Color const& color)
{
	this->_colorSelected = color;
	this->_body.setFillColor(this->_colorSelected);
}

void	nx::gui::Button::setBorderColor(sf::Color const& color)
{
	this->_borderColor = color;
	this->_body.setOutlineColor(this->_borderColor);
}

void	nx::gui::Button::setBorderThickness(int const thickness)
{
	this->_borderThickness = thickness;
	this->setSize(sf::Vector2f(this->getSize().x + thickness, this->getSize().y + thickness));
	this->_body.setOutlineThickness(static_cast<float>(this->_borderThickness));
}

void	nx::gui::Button::setPos(sf::Vector2f const& pos)
{
	GUIElement::setPos(sf::Vector2f(pos.x - this->_borderThickness, pos.y - this->_borderThickness));
	this->_body.setPosition(pos);
	this->_recenteringLabelText();
}

void	nx::gui::Button::setSize(sf::Vector2f const& size)
{
	GUIElement::setSize(size);
	this->_body.setSize(sf::Vector2f(size.x - this->_borderThickness * 2, size.y - this->_borderThickness * 2));
	this->_recenteringLabelText();
}

// Getters

std::string	const	nx::gui::Button::getType() const
{
	return ("Button");
}


// Specific getters

bool const			nx::gui::Button::getState() const
{
	return (this->_state);
}

sf::Text const &	nx::gui::Button::getLabel() const
{
	return (this->_label);
}

std::string const	nx::gui::Button::getText() const
{
	return (this->_label.getString().toAnsiString());
}

unsigned int const	nx::gui::Button::getFontSize() const
{
	return (this->_label.getCharacterSize());
}

sf::Color const &	nx::gui::Button::getColorNotSelected() const
{
	return (this->_colorNotSelected);
}

sf::Color const &	nx::gui::Button::getColorSelected() const
{
	return (this->_colorSelected);
}

sf::Color const &	nx::gui::Button::getBorderColor() const
{
	return (this->_borderColor);
}

int const			nx::gui::Button::getBorderThickness() const
{
	return (this->_borderThickness);
}