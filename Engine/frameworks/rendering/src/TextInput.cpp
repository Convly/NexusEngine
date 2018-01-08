#include "TextInput.hpp"

TextInput::TextInput(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, ColorInfo const& colorInfo, TextInfo const& textInfo) :
	GUIElement(pos, size, identifier), _state(false),
	_backgroundColor(colorInfo.backgroundColor), _borderColor(colorInfo.borderColor), _borderThickness(colorInfo.borderThickness),
	_font(sf::Font()), _body(sf::RectangleShape(size))
{
	this->_font.loadFromFile(textInfo.fontPath);
	this->_label = sf::Text(textInfo.textLabel, this->_font, textInfo.fontSize);
	this->_label.setFillColor(textInfo.textColor);
	this->_label.setStyle(textInfo.textStyle);
	this->_label.setPosition(pos.x + 5,
							 pos.y + this->getSize().y / 2.0f - this->_label.getLocalBounds().height / 2.0f - this->_borderThickness * 2);

	this->_body.setPosition(pos);
	this->_body.setFillColor(colorInfo.backgroundColor);
	this->_body.setOutlineThickness(colorInfo.borderThickness);
	this->_body.setOutlineColor(colorInfo.borderColor);

	this->setSize(sf::Vector2f(this->getSize().x + colorInfo.borderThickness, this->getSize().y + colorInfo.borderThickness));
}

TextInput::~TextInput()
{

}


// GUIElement's mouse event methods overload

void TextInput::onMoveInside(sf::Vector2i const& pos)
{
	//Will be called when mouse is moving into the element
	nx::Log::inform("Mouse moving inside the TextInput '" + this->getIdentifier() + "'");
}

void TextInput::onMoveOutside(sf::Vector2i const& pos)
{
	//Will be called when mouse is moving outside the element
	nx::Log::inform("Mouse moving outside the TextInput '" + this->getIdentifier() + "'");
}

void TextInput::onLeftClickPressedInside(sf::Vector2i const& pos)
{
	//Will be called when the element has been left-clicked
	nx::Log::inform("Left-click pressed inside the TextInput '" + this->getIdentifier() + "'");
	if (!this->_state)
	{
		this->_state = true;
		this->onStateChanged();
	}
}

void TextInput::onLeftClickReleasedInside(sf::Vector2i const& pos)
{
	//Will be called when the element has been left-released
	nx::Log::inform("Left-click released inside the TextInput '" + this->getIdentifier() + "'");
}

void TextInput::onRightClickPressedInside(sf::Vector2i const& pos)
{
	//Will be called when the element has been right-clicked
	nx::Log::inform("Right-click pressed inside the TextInput '" + this->getIdentifier() + "'");
}

void TextInput::onRightClickReleasedInside(sf::Vector2i const& pos)
{
	//Will be called when the element has been right-released
	nx::Log::inform("Right-click released inside the TextInput '" + this->getIdentifier() + "'");
}

void TextInput::onLeftClickPressedOutside(sf::Vector2i const& pos)
{
	//Will be called when a left-click is outside the element
	nx::Log::inform("Left-click pressed outside the TextInput '" + this->getIdentifier() + "'");
	if (this->_state)
	{
		this->_state = false;
		this->onStateChanged();
	}
}

void TextInput::onLeftClickReleasedOutside(sf::Vector2i const& pos)
{
	//Will be called when a left-release is outside the element
	nx::Log::inform("Left-click released outside the TextInput '" + this->getIdentifier() + "'");
}

void TextInput::onRightClickPressedOutside(sf::Vector2i const& pos)
{
	//Will be called when a right-click is outside the element
	nx::Log::inform("Right-click pressed outside the TextInput '" + this->getIdentifier() + "'");
}

void TextInput::onRightClickReleasedOutside(sf::Vector2i const& pos)
{
	//Will be called when a right-release is outside the element
	nx::Log::inform("Right-click released outside the TextInput '" + this->getIdentifier() + "'");
}

// Display

void TextInput::show(std::shared_ptr<sf::RenderWindow> const& win)
{
	if (this->isVisible())
	{
		win->draw(this->_body);
		win->draw(this->_label);
	}
}


// Specific functions for this element

void TextInput::onStateChanged()
{
	//Will be called when the TextInput's state has been changed
	nx::Log::inform("The TextInput '" + this->getIdentifier() + "' state is now " + std::to_string(this->_state));
}


// Setters
void	TextInput::setState(bool const state)
{
	this->_state = state;
}

void	TextInput::setLabel(sf::Text const& label)
{
	this->_label = label;
}

void	TextInput::setBackgroundColor(sf::Color const& color)
{
	this->_backgroundColor = color;
	this->_body.setFillColor(this->_backgroundColor);
}

void	TextInput::setBorderColor(sf::Color const& color)
{
	this->_borderColor = color;
	this->_body.setOutlineColor(this->_borderColor);
}

void	TextInput::setBorderThickness(int const thickness)
{
	this->_borderThickness = thickness;
	this->setSize(sf::Vector2f(this->getSize().x + thickness, this->getSize().y + thickness));
	this->_body.setOutlineThickness(this->_borderThickness);
}

void	TextInput::setPos(sf::Vector2f const& pos)
{
	GUIElement::setPos(sf::Vector2f(pos.x - this->_borderThickness, pos.y - this->_borderThickness));
	this->_body.setPosition(pos);
	this->_label.setPosition(pos.x + 5,
							 pos.y + this->getSize().y / 2.0f - this->_label.getLocalBounds().height / 2.0f - this->_borderThickness * 2);
}

void	TextInput::setSize(sf::Vector2f const& size)
{
	GUIElement::setSize(size);
	this->_body.setSize(sf::Vector2f(size.x - this->_borderThickness * 2, size.y - this->_borderThickness * 2));
	this->_label.setPosition(this->getPos().x + 5,
							 this->getPos().y + this->getSize().y / 2.0f - this->_label.getLocalBounds().height / 2.0f - this->_borderThickness * 2);
}

// Getters

std::string	const	TextInput::getType() const
{
	return ("TextInput");
}


// Specific getters

bool const			TextInput::getState() const
{
	return (this->_state);
}

sf::Text const &	TextInput::getLabel() const
{
	return (this->_label);
}

sf::Color const &	TextInput::getBackgroundColor() const
{
	return (this->_backgroundColor);
}

sf::Color const &	TextInput::getBorderColor() const
{
	return (this->_borderColor);
}

int const			TextInput::getBorderThickness() const
{
	return (this->_borderThickness);
}