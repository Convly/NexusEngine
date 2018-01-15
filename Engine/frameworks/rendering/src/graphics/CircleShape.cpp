#include "CircleShape.hpp"

nx::graphics::CircleShape::CircleShape(sf::Vector2f const & pos, sf::Vector2f const & size, std::string const & identifier,
									   nx::rendering::MouseEventsContainer const & events, float const radius, nx::ColorInfo const& colorInfo) :
	GraphicsElement(pos, size, identifier, events), _body(sf::CircleShape(radius))
{
	this->_body.setPosition(pos);
	this->_body.setFillColor(colorInfo.backgroundColor);
	this->_body.setOutlineThickness(static_cast<float>(colorInfo.borderThickness));
	this->_body.setOutlineColor(colorInfo.borderColor);

	this->setRadius(radius);
}

nx::graphics::CircleShape::~CircleShape()
{

}


// Display

void	nx::graphics::CircleShape::show(std::shared_ptr<sf::RenderWindow> const & win)
{
	if (this->isVisible())
	{
		win->draw(this->_body);
	}
}


// Setters

void	nx::graphics::CircleShape::setBackgroundColor(sf::Color const & color)
{
	this->_body.setFillColor(color);
}

void	nx::graphics::CircleShape::setBorderColor(sf::Color const & color)
{
	this->_body.setOutlineColor(color);
}

void	nx::graphics::CircleShape::setBorderThickness(int const thickness)
{
	this->_body.setOutlineThickness(static_cast<float>(thickness));
}

void	nx::graphics::CircleShape::setRotation(float const angle)
{
	this->_body.setRotation(angle);
}

void	nx::graphics::CircleShape::setRadius(float const radius)
{
	float thickness = this->_body.getOutlineThickness();

	this->_body.setRadius(radius);
	GraphicsElement::setSize(sf::Vector2f(this->_body.getLocalBounds().width, this->_body.getLocalBounds().height));
}

void	nx::graphics::CircleShape::setPos(sf::Vector2f const& pos)
{
	float thickness = this->_body.getOutlineThickness();

	GraphicsElement::setPos(sf::Vector2f(pos.x - thickness, pos.y - thickness));
	this->_body.setPosition(pos);
}

void	nx::graphics::CircleShape::setSize(sf::Vector2f const& size)
{
	//Can't modify the size
}


// Getters

std::string const	nx::graphics::CircleShape::getType() const
{
	return ("CircleShape");
}


// Specific getters

sf::Color const&	nx::graphics::CircleShape::getBackgroundColor() const
{
	return (this->_body.getFillColor());
}

sf::Color const&	nx::graphics::CircleShape::getBorderColor() const
{
	return (this->_body.getOutlineColor());
}

int const			nx::graphics::CircleShape::getBorderThickness() const
{
	return (static_cast<int>(this->_body.getOutlineThickness()));
}

float const			nx::graphics::CircleShape::getRotation() const
{
	return (this->_body.getRotation());
}

float const			nx::graphics::CircleShape::getRadius() const
{
	return (this->_body.getRadius());
}