#include "RectShape.hpp"

nx::graphics::RectShape::RectShape(sf::Vector2f const & pos, sf::Vector2f const & size, std::string const & identifier,
								   nx::rendering::MouseEventsContainer const & events, nx::ColorInfo const& colorInfo) :
	GraphicsElement(pos, size, identifier, events), _body(sf::RectangleShape(size))
{
	this->_body.setPosition(pos);
	this->_body.setFillColor(colorInfo.backgroundColor);
	this->_body.setOutlineThickness(static_cast<float>(colorInfo.borderThickness));
	this->_body.setOutlineColor(colorInfo.borderColor);

	this->setSize(sf::Vector2f(this->getSize().x + colorInfo.borderThickness, this->getSize().y + colorInfo.borderThickness));
}

nx::graphics::RectShape::~RectShape()
{

}


// Display

void	nx::graphics::RectShape::show(std::shared_ptr<sf::RenderWindow> const & win)
{
	if (this->isVisible())
	{
		win->draw(this->_body);
	}
}


// Setters

void	nx::graphics::RectShape::setBackgroundColor(sf::Color const & color)
{
	this->_body.setFillColor(color);
}

void	nx::graphics::RectShape::setBorderColor(sf::Color const & color)
{
	this->_body.setOutlineColor(color);
}

void	nx::graphics::RectShape::setBorderThickness(int const thickness)
{
	this->_body.setOutlineThickness(static_cast<float>(thickness));
}

void	nx::graphics::RectShape::setRotation(float const angle)
{
	this->_body.setRotation(angle);
}

void	nx::graphics::RectShape::setPos(sf::Vector2f const& pos)
{
	float thickness = this->_body.getOutlineThickness();

	GraphicsElement::setPos(sf::Vector2f(pos.x - thickness, pos.y - thickness));
	this->_body.setPosition(pos);
}

void	nx::graphics::RectShape::setSize(sf::Vector2f const& size)
{
	float thickness = this->_body.getOutlineThickness();

	GraphicsElement::setSize(size);
	this->_body.setSize(sf::Vector2f(size.x - thickness * 2, size.y - thickness * 2));
}


// Getters

std::string const	nx::graphics::RectShape::getType() const
{
	return ("RectShape");
}


// Specific getters

sf::Color const&	nx::graphics::RectShape::getBackgroundColor() const
{
	return (this->_body.getFillColor());
}

sf::Color const&	nx::graphics::RectShape::getBorderColor() const
{
	return (this->_body.getOutlineColor());
}

int const			nx::graphics::RectShape::getBorderThickness() const
{
	return (static_cast<int>(this->_body.getOutlineThickness()));
}

float const			nx::graphics::RectShape::getRotation() const
{
	return (this->_body.getRotation());
}