#include "Text.hpp"

Text::Text(sf::Vector2f const& pos, std::string const& identifier, TextInfo const& textInfo) :
	GUIElement(pos, sf::Vector2f(), identifier), _font(sf::Font())
{
	this->_font.loadFromFile(textInfo.fontPath);
	this->_label = sf::Text(textInfo.textLabel, this->_font, textInfo.fontSize);
	this->_label.setFillColor(textInfo.textColor);
	this->_label.setStyle(textInfo.textStyle);
	this->_label.setPosition(pos);
	GUIElement::setSize(sf::Vector2f(this->_label.getLocalBounds().width, this->_label.getLocalBounds().height));
}

Text::~Text()
{

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