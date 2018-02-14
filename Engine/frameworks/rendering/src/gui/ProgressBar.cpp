#include "ProgressBar.hpp"

nx::gui::ProgressBar::ProgressBar(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, nx::env::MouseEventsContainer const& events,
						 ColorInfo const& colorInfo, TextInfo const& textInfo, bool const displayPercentage) :
	GUIElement(pos, size, identifier, events),
	_backgroundColor(colorInfo.backgroundColor), _borderColor(colorInfo.borderColor), _borderThickness(colorInfo.borderThickness),
	_body(sf::RectangleShape(size)), _filled(sf::RectangleShape()), _percentage(0), _font(rxallocator<sf::Font>())
{
	if (!this->_font->loadFromFile(textInfo.fontPath))
		throw nx::InvalidFontException(textInfo.fontPath);

	this->_label = sf::Text("", *this->_font, textInfo.fontSize);
	this->_label.setFillColor(textInfo.textColor);
	this->_label.setStyle(textInfo.textStyle);
	this->setFilled(0);

	this->_body.setPosition(pos);
	this->_body.setFillColor(colorInfo.backgroundColor);
	this->_body.setOutlineThickness(static_cast<float>(colorInfo.borderThickness));
	this->_body.setOutlineColor(colorInfo.borderColor);

	this->_filled.setPosition(pos);
	this->_filled.setFillColor(sf::Color(0, 255, 0, 255));

	GUIElement::setSize(sf::Vector2f(this->_body.getLocalBounds().width, this->_body.getLocalBounds().height));
}

nx::gui::ProgressBar::~ProgressBar()
{

}


// Display

void nx::gui::ProgressBar::show(std::shared_ptr<sf::RenderWindow> const& win)
{
	if (this->isVisible())
	{
		win->draw(this->_body);
		win->draw(this->_filled);
		win->draw(this->_label);
	}
}


// Setters

void	nx::gui::ProgressBar::setBackgroundColor(sf::Color const& color)
{
	this->_backgroundColor = color;
	this->_body.setFillColor(this->_backgroundColor);
}

void	nx::gui::ProgressBar::setBorderColor(sf::Color const& color)
{
	this->_borderColor = color;
	this->_body.setOutlineColor(this->_borderColor);
}

void	nx::gui::ProgressBar::setBorderThickness(int const thickness)
{
	this->_borderThickness = thickness;
	this->_body.setOutlineThickness(static_cast<float>(this->_borderThickness));
	GUIElement::setSize(sf::Vector2f(this->_body.getLocalBounds().width, this->_body.getLocalBounds().height));
}

void	nx::gui::ProgressBar::setFilled(int const percentage)
{
	if (percentage >= 0 && percentage <= 100)
	{
		this->_percentage = percentage;
		this->_filled.setSize(sf::Vector2f(this->getSize().x * (percentage / 100.0f), this->getSize().y - this->_borderThickness * 2));
		this->_label.setPosition(this->getPos().x + this->getSize().x / 2.0f - this->_label.getLocalBounds().width / 2.0f - this->_borderThickness * 2,
			this->getPos().y + this->getSize().y / 2.0f - this->_label.getLocalBounds().height / 2.0f - this->_borderThickness * 2);
		this->_label.setString(std::to_string(percentage) + "%");
	}
}

void	nx::gui::ProgressBar::setPos(sf::Vector2f const& pos)
{
	GUIElement::setPos(sf::Vector2f(pos.x - this->_borderThickness, pos.y - this->_borderThickness));
	this->_body.setPosition(pos);
	this->_filled.setPosition(pos);
	this->_label.setPosition(pos.x + this->getSize().x / 2.0f - this->_label.getLocalBounds().width / 2.0f - this->_borderThickness * 2,
							 pos.y + this->getSize().y / 2.0f - this->_label.getLocalBounds().height / 2.0f - this->_borderThickness * 2);
}

void	nx::gui::ProgressBar::setSize(sf::Vector2f const& size)
{
	this->_body.setSize(sf::Vector2f(size.x - this->_borderThickness * 2, size.y - this->_borderThickness * 2));
	GUIElement::setSize(sf::Vector2f(this->_body.getLocalBounds().width, this->_body.getLocalBounds().height));
	this->_filled.setSize(sf::Vector2f(this->getSize().x * (this->_percentage / 100.0f), this->getSize().y - this->_borderThickness * 2));
	this->_label.setPosition(this->getPos().x + this->getSize().x / 2.0f - this->_label.getLocalBounds().width / 2.0f - this->_borderThickness * 2,
							 this->getPos().y + this->getSize().y / 2.0f - this->_label.getLocalBounds().height / 2.0f - this->_borderThickness * 2);
}

void	nx::gui::ProgressBar::setFontSize(unsigned int const fontSize)
{
	this->_label.setCharacterSize(fontSize);
}


// Getters

std::string	const	nx::gui::ProgressBar::getType() const
{
	return ("ProgressBar");
}


// Specific getters

sf::Color const	&	nx::gui::ProgressBar::getBackgroundColor() const
{
	return (this->_backgroundColor);
}

sf::Color const	&	nx::gui::ProgressBar::getBorderColor() const
{
	return (this->_borderColor);
}

int const			nx::gui::ProgressBar::getBorderThickness() const
{
	return (this->_borderThickness);
}

int const			nx::gui::ProgressBar::getFilled() const
{
	return (this->_percentage);
}

unsigned int const	nx::gui::ProgressBar::getFontSize() const
{
	return (this->_label.getCharacterSize());
}