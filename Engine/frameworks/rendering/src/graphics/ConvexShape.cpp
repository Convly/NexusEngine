#include "ConvexShape.hpp"

nx::graphics::ConvexShape::ConvexShape(sf::Vector2f const & pos, sf::Vector2f const & size, std::string const & identifier,
									   nx::rendering::MouseEventsContainer const & events, nx::ColorInfo const& colorInfo) :
	GraphicsElement(pos, sf::Vector2f(), identifier, events), _body(sf::ConvexShape())
{
	this->_body.setPosition(pos);
	this->_body.setFillColor(colorInfo.backgroundColor);
	this->_body.setOutlineThickness(static_cast<float>(colorInfo.borderThickness));
	this->_body.setOutlineColor(colorInfo.borderColor);
}

nx::graphics::ConvexShape::~ConvexShape()
{

}


// Display

void	nx::graphics::ConvexShape::show(std::shared_ptr<sf::RenderWindow> const & win)
{
	if (this->isVisible())
	{
		win->draw(this->_body);
	}
}


// Setters

void	nx::graphics::ConvexShape::setBackgroundColor(sf::Color const & color)
{
	this->_body.setFillColor(color);
}

void	nx::graphics::ConvexShape::setBorderColor(sf::Color const & color)
{
	this->_body.setOutlineColor(color);
}

void	nx::graphics::ConvexShape::setBorderThickness(int const thickness)
{
	this->_body.setOutlineThickness(static_cast<float>(thickness));
}

void	nx::graphics::ConvexShape::setRotation(float const angle)
{
	this->_body.setRotation(angle);
}

void	nx::graphics::ConvexShape::setPointCount(size_t const pointCount)
{
	sf::FloatRect bounds = this->_body.getLocalBounds();

	this->_body.setPointCount(pointCount);
	GraphicsElement::setSize(sf::Vector2f(bounds.width, bounds.height));
}

void	nx::graphics::ConvexShape::setPoint(size_t const index, sf::Vector2f const& point)
{
	sf::FloatRect bounds = this->_body.getLocalBounds();

	this->_body.setPoint(index, point);
	GraphicsElement::setSize(sf::Vector2f(bounds.width, bounds.height));
}

void	nx::graphics::ConvexShape::setPos(sf::Vector2f const& pos)
{
	float thickness = this->_body.getOutlineThickness();

	GraphicsElement::setPos(sf::Vector2f(pos.x - thickness, pos.y - thickness));
	this->_body.setPosition(pos);
}

void	nx::graphics::ConvexShape::setSize(sf::Vector2f const& size)
{
	//Can't modify the size
}


// Getters

std::string const	nx::graphics::ConvexShape::getType() const
{
	return ("ConvexShape");
}


// Specific getters

sf::Color const&	nx::graphics::ConvexShape::getBackgroundColor() const
{
	return (this->_body.getFillColor());
}

sf::Color const&	nx::graphics::ConvexShape::getBorderColor() const
{
	return (this->_body.getOutlineColor());
}

int const			nx::graphics::ConvexShape::getBorderThickness() const
{
	return (static_cast<int>(this->_body.getOutlineThickness()));
}

float const			nx::graphics::ConvexShape::getRotation() const
{
	return (this->_body.getRotation());
}

size_t const		nx::graphics::ConvexShape::getPointCount() const
{
	return (this->_body.getPointCount());
}

sf::Vector2f const	nx::graphics::ConvexShape::getPoint(size_t const index) const
{
	return (this->_body.getPoint(index));
}