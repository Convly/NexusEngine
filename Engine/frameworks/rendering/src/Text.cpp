#include "Text.hpp"

Text::Text(sf::Vector2f const& pos, std::string const& identifier, TextInfo const& textInfo) :
	GUIElement(pos, sf::Vector2f(), identifier), _font(sf::Font())
{
	if (!this->_font.loadFromFile(textInfo.fontPath))
		throw nx::InvalidFontException(textInfo.fontPath);
	this->_label = sf::Text(textInfo.textLabel, this->_font, textInfo.fontSize);
	this->_label.setFillColor(textInfo.textColor);
	this->_label.setStyle(textInfo.textStyle);
	this->_label.setPosition(pos);
	GUIElement::setSize(sf::Vector2f(this->_label.getLocalBounds().width, this->_label.getLocalBounds().height));
}

Text::~Text()
{

}


// GUIElement's mouse event methods overload

void Text::onMoveInside(sf::Vector2i const& pos)
{
	//Will be called when mouse is moving into the element
	//nx::Log::inform("Mouse moving inside the Text '" + this->getIdentifier() + "'");
}

void Text::onMoveOutside(sf::Vector2i const& pos)
{
	//Will be called when mouse is moving outside the element
	//nx::Log::inform("Mouse moving outside the Text '" + this->getIdentifier() + "'");
}

void Text::onLeftClickPressedInside(sf::Vector2i const& pos)
{
	//Will be called when the element has been left-clicked
	//nx::Log::inform("Left-click pressed inside the Text '" + this->getIdentifier() + "'");
}

void Text::onLeftClickReleasedInside(sf::Vector2i const& pos)
{
	//Will be called when the element has been left-released
	//nx::Log::inform("Left-click released inside the Text '" + this->getIdentifier() + "'");
}

void Text::onRightClickPressedInside(sf::Vector2i const& pos)
{
	//Will be called when the element has been right-clicked
	//nx::Log::inform("Right-click pressed inside the Text '" + this->getIdentifier() + "'");
}

void Text::onRightClickReleasedInside(sf::Vector2i const& pos)
{
	//Will be called when the element has been right-released
	//nx::Log::inform("Right-click released inside the Text '" + this->getIdentifier() + "'");
}

void Text::onLeftClickPressedOutside(sf::Vector2i const& pos)
{
	//Will be called when a left-click is outside the element
	//nx::Log::inform("Left-click pressed outside the Text '" + this->getIdentifier() + "'");
}

void Text::onLeftClickReleasedOutside(sf::Vector2i const& pos)
{
	//Will be called when a left-release is outside the element
	//nx::Log::inform("Left-click released outside the Text '" + this->getIdentifier() + "'");
}

void Text::onRightClickPressedOutside(sf::Vector2i const& pos)
{
	//Will be called when a right-click is outside the element
	//nx::Log::inform("Right-click pressed outside the Text '" + this->getIdentifier() + "'");
}

void Text::onRightClickReleasedOutside(sf::Vector2i const& pos)
{
	//Will be called when a right-release is outside the element
	//nx::Log::inform("Right-click released outside the Text '" + this->getIdentifier() + "'");
}

void Text::keyTextEntered(char const charEntered)
{
	//Will be called when text in entered
	//nx::Log::inform("Char pressed for the Text '" + this->getIdentifier() + "' is " + charEntered);
}

void Text::keyPressed(sf::Keyboard::Key const& keyPressed)
{
	//Will be called when a key is pressed
	//nx::Log::inform("Key pressed for the Text '" + this->getIdentifier());
}

// Display

void Text::show(std::shared_ptr<sf::RenderWindow> const& win)
{
	if (this->isVisible())
		win->draw(this->_label);
}


// Setters

void	Text::setLabel(sf::Text const& label)
{
	this->_label = label;
	GUIElement::setSize(sf::Vector2f(this->_label.getLocalBounds().width, this->_label.getLocalBounds().height));
}

void	Text::setText(std::string const& text)
{
	this->_label.setString(text);
	GUIElement::setSize(sf::Vector2f(this->_label.getLocalBounds().width, this->_label.getLocalBounds().height));
}

void	Text::setFontSize(unsigned int const fontSize)
{
	this->_label.setCharacterSize = fontSize;
}


void	Text::setPos(sf::Vector2f const& pos)
{
	GUIElement::setPos(pos);
	this->_label.setPosition(pos);
}

void	Text::setSize(sf::Vector2f const& size)
{
	// Can't modify a text size
}

// Getters

std::string	const	Text::getType() const
{
	return ("Text");
}


// Specific getters

sf::Text const &	Text::getLabel() const
{
	return (this->_label);
}

std::string const	Text::getText() const
{
	return (this->_label.getString().toAnsiString());
}

unsigned int const	Text::getFontSize() const
{
	return (this->_label.getCharacterSize());
}