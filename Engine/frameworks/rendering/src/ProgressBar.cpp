#include "ProgressBar.hpp"

ProgressBar::ProgressBar(sf::Vector2f pos, sf::Vector2f size, std::string const& identifier, ColorInfo const& colorInfo, TextInfo const& textInfo, bool const displayPercentage) :
	GUIElement(pos, size, identifier),
	_backgroundColor(colorInfo.backgroundColor), _borderColor(colorInfo.borderColor), _borderThickness(colorInfo.borderThickness),
	_body(sf::RectangleShape(size)), _filled(sf::RectangleShape()), _percentage(0), _font(sf::Font())
{
	this->setSize(sf::Vector2f(this->getSize().x + colorInfo.borderThickness, this->getSize().y + colorInfo.borderThickness));

	this->_font.loadFromFile(textInfo.fontPath);
	this->_label = sf::Text(std::to_string(this->_percentage) + "%", this->_font, textInfo.fontSize);
	this->_label.setFillColor(textInfo.textColor);
	this->_label.setStyle(textInfo.textStyle);
	this->_label.setPosition(pos.x + size.x / 2 - this->_label.getLocalBounds().width / 2,
							 pos.y + size.y / 2 - this->_label.getLocalBounds().height);

	this->_body.setPosition(pos);
	this->_body.setFillColor(colorInfo.backgroundColor);
	this->_body.setOutlineThickness(colorInfo.borderThickness);
	this->_body.setOutlineColor(colorInfo.borderColor);

	this->_filled.setPosition(pos);
	this->_filled.setFillColor(sf::Color(0, 255, 0, 255));
}

ProgressBar::~ProgressBar()
{

}


// GUIElement's mouse event methods overload

void ProgressBar::onMoveInside()
{
	//Will be called when mouse is moving into the element
	nx::Log::inform("Mouse moving inside the ProgressBar '" + this->getIdentifier() + "'");
}

void ProgressBar::onMoveOutside()
{
	//Will be called when mouse is moving outside the element
	nx::Log::inform("Mouse moving outside the ProgressBar '" + this->getIdentifier() + "'");
}

void ProgressBar::onLeftClickPressedInside()
{
	//Will be called when a left-click is inside the element
	nx::Log::inform("Left-click pressed inside the ProgressBar '" + this->getIdentifier() + "'");
}

void ProgressBar::onLeftClickReleasedInside()
{
	//Will be called when a left-release is inside the element
	nx::Log::inform("Left-click released inside the ProgressBar '" + this->getIdentifier() + "'");
}

void ProgressBar::onRightClickPressedInside()
{
	//Will be called when a right-click is inside the element
	nx::Log::inform("Right-click pressed inside the ProgressBar '" + this->getIdentifier() + "'");
}

void ProgressBar::onRightClickReleasedInside()
{
	//Will be called when a right-release is inside the element
	nx::Log::inform("Right-click released inside the ProgressBar '" + this->getIdentifier() + "'");
}

void ProgressBar::onLeftClickPressedOutside()
{
	//Will be called when a left-click is outside the element
	nx::Log::inform("Left-click pressed outside the ProgressBar '" + this->getIdentifier() + "'");
}

void ProgressBar::onLeftClickReleasedOutside()
{
	//Will be called when a left-release is outside the element
	nx::Log::inform("Left-click released outside the ProgressBar '" + this->getIdentifier() + "'");
}

void ProgressBar::onRightClickPressedOutside()
{
	//Will be called when a right-click is outside the element
	nx::Log::inform("Right-click pressed outside the ProgressBar '" + this->getIdentifier() + "'");
}

void ProgressBar::onRightClickReleasedOutside()
{
	//Will be called when a right-release is outside the element
	nx::Log::inform("Right-click released outside the ProgressBar '" + this->getIdentifier() + "'");
}

// Display

void ProgressBar::show(std::shared_ptr<sf::RenderWindow> const& win)
{
	if (this->isVisible())
	{
		win->draw(this->_body);
		win->draw(this->_filled);
		win->draw(this->_label);
	}
}


// Specific functions for this element

void ProgressBar::onStateChanged()
{
	//Will be called when the button's state has been changed
}


// Setters

void	ProgressBar::setBackgroundColor(sf::Color const& color)
{
	this->_backgroundColor = color;
	this->_body.setFillColor(this->_backgroundColor);
}

void	ProgressBar::setBorderColor(sf::Color const& color)
{
	this->_borderColor = color;
	this->_body.setOutlineColor(this->_borderColor);
}

void	ProgressBar::setBorderThickness(int const thickness)
{
	this->_borderThickness = thickness;
	this->setSize(sf::Vector2f(this->getSize().x + thickness, this->getSize().y + thickness));
	this->_body.setOutlineThickness(this->_borderThickness);
}

void	ProgressBar::setFilled(int const percentage)
{
	this->_percentage = percentage;
	this->_filled.setSize(sf::Vector2f(this->getSize().x * (percentage / 100.0f), this->getSize().y - this->_borderThickness));
	this->_label.setString(std::to_string(percentage) + "%");
}

void	ProgressBar::setPos(sf::Vector2f const& pos)
{
	GUIElement::setPos(pos);
	this->_body.setPosition(pos);
	this->_filled.setPosition(pos);
	this->_label.setPosition(pos.x + this->getSize().x / 2 - this->_label.getLocalBounds().width / 2,
							 pos.y + this->getSize().y / 2 - this->_label.getLocalBounds().height);
}

void	ProgressBar::setSize(sf::Vector2f const& size)
{
	GUIElement::setSize(size);
	this->_body.setSize(sf::Vector2f(this->getSize().x - this->_borderThickness, this->getSize().y));
	this->_filled.setSize(sf::Vector2f(this->getSize().x * (this->_percentage / 100.0f), this->getSize().y - this->_borderThickness));
	this->_label.setPosition(this->getPos().x + size.x / 2 - this->_label.getLocalBounds().width / 2,
							 this->getPos().y + size.y / 2 - this->_label.getLocalBounds().height);
}

void	ProgressBar::setLabel(sf::Text const& label)
{
	this->_label = label;
}

// Getters

std::string	const	ProgressBar::getType() const
{
	return ("ProgressBar");
}


// Specific getters

sf::Color const	&	ProgressBar::getBackgroundColor() const
{
	return (this->_backgroundColor);
}

sf::Color const	&	ProgressBar::getBorderColor() const
{
	return (this->_borderColor);
}

int const			ProgressBar::getBorderThickness() const
{
	return (this->_borderThickness);
}

int const			ProgressBar::getFilled() const
{
	return (this->_percentage);
}

sf::Text const &	ProgressBar::getLabel() const
{
	return (this->_label);
}