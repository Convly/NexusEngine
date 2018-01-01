#include "Checkbox.hpp"

Checkbox::Checkbox(sf::Vector2f pos, sf::Vector2f size, std::string const& identifier, ColorInfo const& colorInfo) :
	GUIElement(pos, size, identifier), _state(State::UNCHECKED),
	_backgroundColor(colorInfo.backgroundColor), _borderColor(colorInfo.borderColor), _borderThickness(colorInfo.borderThickness),
	_body(sf::RectangleShape(size))
{
	this->setSize(sf::Vector2f(this->getSize().x + colorInfo.borderThickness, this->getSize().y + colorInfo.borderThickness));

	this->_body.setPosition(pos);
	this->_body.setFillColor(colorInfo.backgroundColor);
	this->_body.setOutlineThickness(colorInfo.borderThickness);
	this->_body.setOutlineColor(colorInfo.borderColor);

	sf::VertexArray half1(sf::LinesStrip, 2);
	sf::VertexArray half2(sf::LinesStrip, 2);
	sf::VertexArray partial(sf::LinesStrip, 2);

	half1[0].position = pos;
	half1[0].color = this->_borderColor;
	half1[1].position = pos + size;
	half1[1].color = this->_borderColor;

	half2[0].position = sf::Vector2f(pos.x + size.x, pos.y);
	half2[0].color = this->_borderColor;
	half2[1].position = sf::Vector2f(pos.x, pos.y + size.y);
	half2[1].color = this->_borderColor;

	partial[0].position = sf::Vector2f(pos.x + size.x * 0.1f, pos.y + size.y / 2.0f);
	partial[0].color = this->_borderColor;
	partial[1].position = sf::Vector2f(pos.x + size.x * 0.9f, pos.y + size.y / 2.0f);
	partial[1].color = this->_borderColor;

	this->_lines.push_back(half1);
	this->_lines.push_back(half2);
	this->_lines.push_back(partial);
}

Checkbox::~Checkbox()
{

}


// GUIElement's mouse event methods overload

void Checkbox::onMoveInside()
{
	//Will be called when mouse is moving into the element
	nx::Log::inform("Mouse moving inside the checkbox '" + this->getIdentifier() + "'");
}

void Checkbox::onMoveOutside()
{
	//Will be called when mouse is moving outside the element
	nx::Log::inform("Mouse moving outside the checkbox '" + this->getIdentifier() + "'");
}

void Checkbox::onLeftClickPressedInside()
{
	//Will be called when a left-click is inside the element
	nx::Log::inform("Left-click pressed inside the checkbox '" + this->getIdentifier() + "'");
	if (this->_state != State::UNCHECKED)
		this->_state = State::UNCHECKED;
	else
		this->_state = State::CHECKED;
}

void Checkbox::onLeftClickReleasedInside()
{
	//Will be called when a left-release is inside the element
	nx::Log::inform("Left-click released inside the checkbox '" + this->getIdentifier() + "'");
}

void Checkbox::onRightClickPressedInside()
{
	//Will be called when a right-click is inside the element
	nx::Log::inform("Right-click pressed inside the checkbox '" + this->getIdentifier() + "'");
}

void Checkbox::onRightClickReleasedInside()
{
	//Will be called when a right-release is inside the element
	nx::Log::inform("Right-click released inside the checkbox '" + this->getIdentifier() + "'");
}

void Checkbox::onLeftClickPressedOutside()
{
	//Will be called when a left-click is outside the element
	nx::Log::inform("Left-click pressed outside the checkbox '" + this->getIdentifier() + "'");
}

void Checkbox::onLeftClickReleasedOutside()
{
	//Will be called when a left-release is outside the element
	nx::Log::inform("Left-click released outside the checkbox '" + this->getIdentifier() + "'");
}

void Checkbox::onRightClickPressedOutside()
{
	//Will be called when a right-click is outside the element
	nx::Log::inform("Right-click pressed outside the checkbox '" + this->getIdentifier() + "'");
}

void Checkbox::onRightClickReleasedOutside()
{
	//Will be called when a right-release is outside the element
	nx::Log::inform("Right-click released outside the checkbox '" + this->getIdentifier() + "'");
}

// Display

void Checkbox::show(std::shared_ptr<sf::RenderWindow> const& win)
{
	if (this->isVisible())
	{
		win->draw(this->_body);
		if (this->_state == State::CHECKED)
		{
			win->draw(this->_lines[0]);
			win->draw(this->_lines[1]);
		}
		else if (this->_state == State::PARTIAL)
			win->draw(this->_lines[2]);
	}
}


// Specific functions for this element

void Checkbox::onStateChanged()
{
	//Will be called when the button's state has been changed
}


// Setters
void	Checkbox::setState(State const state)
{
	this->_state = state;
}

void	Checkbox::setBackgroundColor(sf::Color const& color)
{
	this->_backgroundColor = color;
	this->_body.setFillColor(this->_backgroundColor);
}

void	Checkbox::setBorderColor(sf::Color const& color)
{
	this->_borderColor = color;
	this->_body.setOutlineColor(this->_borderColor);
	for (auto it : this->_lines)
	{
		it[0].color = this->_borderColor;
		it[1].color = this->_borderColor;
	}
}

void	Checkbox::setBorderThickness(int const thickness)
{
	this->_borderThickness = thickness;
	this->setSize(sf::Vector2f(this->getSize().x + thickness, this->getSize().y + thickness));
	this->_body.setOutlineThickness(this->_borderThickness);
}

void	Checkbox::setPos(sf::Vector2f const& pos)
{
	GUIElement::setPos(pos);
	this->_body.setPosition(this->getPos());

	this->_lines[0][0].position = pos;
	this->_lines[0][1].position = pos + this->getSize();

	this->_lines[1][0].position = sf::Vector2f(pos.x + this->getSize().x, pos.y);
	this->_lines[1][1].position = sf::Vector2f(pos.x, pos.y + this->getSize().y);

	this->_lines[2][0].position = sf::Vector2f(pos.x + this->getSize().x * 0.1f, pos.y + this->getSize().y / 2.0f);
	this->_lines[2][1].position = sf::Vector2f(pos.x + this->getSize().x * 0.9f, pos.y + this->getSize().y / 2.0f);
}

void	Checkbox::setSize(sf::Vector2f const& size)
{
	GUIElement::setSize(size);
	this->_body.setSize(sf::Vector2f(this->getSize().x - this->_borderThickness, this->getSize().y - this->_borderThickness));

	if (!this->_lines.empty())
	{
		this->_lines[0][1].position = this->getPos() + size;
		this->_lines[1][1].position = sf::Vector2f(this->getPos().x, this->getPos().y + size.y);
		this->_lines[2][1].position = sf::Vector2f(this->getPos().x + size.x * 0.9f, this->getPos().y + size.y / 2.0f);
	}
}

// Getters

std::string	const	Checkbox::getType() const
{
	return ("Checkbox");
}


// Specific getters

Checkbox::State const Checkbox::getState() const
{
	return (this->_state);
}

sf::Color const	&	Checkbox::getBackgroundColor() const
{
	return (this->_backgroundColor);
}

sf::Color const	&	Checkbox::getBorderColor() const
{
	return (this->_borderColor);
}

int const			Checkbox::getBorderThickness() const
{
	return (this->_borderThickness);
}