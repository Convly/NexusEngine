#include "Text.hpp"

nx::gui::Text::Text(sf::Vector2f const& pos, std::string const& identifier, nx::env::MouseEventsContainer const& events, TextInfo const& textInfo) :
	GUIElement(pos, sf::Vector2f(), identifier), _font(rxallocator<sf::Font>())
{
	if (!this->_font->loadFromFile(textInfo.fontPath))
		throw nx::InvalidFontException(textInfo.fontPath);
	this->_label = sf::Text(textInfo.textLabel, *this->_font, textInfo.fontSize);
	this->_label.setFillColor(textInfo.textColor);
	this->_label.setStyle(textInfo.textStyle);
	this->_label.setPosition(pos);
	GUIElement::setSize(sf::Vector2f(this->_label.getLocalBounds().width, this->_label.getLocalBounds().height));
}

nx::gui::Text::~Text()
{

}


// Display

void nx::gui::Text::show(std::shared_ptr<sf::RenderWindow> const& win)
{
	if (this->isVisible())
		win->draw(this->_label);
}


// Setters

void	nx::gui::Text::setText(std::string const& text)
{
	this->_label.setString(text);
	GUIElement::setSize(sf::Vector2f(this->_label.getLocalBounds().width, this->_label.getLocalBounds().height));
}

void	nx::gui::Text::setFontSize(unsigned int const fontSize)
{
	this->_label.setCharacterSize(fontSize);
}


void	nx::gui::Text::setPos(sf::Vector2f const& pos)
{
	GUIElement::setPos(pos);
	this->_label.setPosition(pos);
}

void	nx::gui::Text::setSize(sf::Vector2f const& size)
{
	// Can't modify a text size
}

// Getters

std::string	const	nx::gui::Text::getType() const
{
	return ("Text");
}


// Specific getters

std::string const	nx::gui::Text::getText() const
{
	return (this->_label.getString().toAnsiString());
}

unsigned int const	nx::gui::Text::getFontSize() const
{
	return (this->_label.getCharacterSize());
}