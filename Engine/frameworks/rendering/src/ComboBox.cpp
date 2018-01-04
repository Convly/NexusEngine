#include "ComboBox.hpp"

ComboBox::ComboBox(sf::Vector2f pos, sf::Vector2f size, std::string const& identifier, ColorInfo const& colorInfo, TextInfo const& textInfo) :
	GUIElement(pos, size, identifier),
	_backgroundColor(colorInfo.backgroundColor), _borderColor(colorInfo.borderColor), _borderThickness(colorInfo.borderThickness),
	_font(sf::Font()), _colorInfo(ColorInfo(colorInfo)), _textInfo(TextInfo(textInfo)), _body(sf::RectangleShape(size)), _idxSelected(-1), _isScrolled(false)
{
	this->_font.loadFromFile(textInfo.fontPath);
	this->_selected = sf::Text("- Nothing selected -", this->_font, this->_textInfo.fontSize);
	this->_selected.setFillColor(textInfo.textColor);
	this->_selected.setStyle(textInfo.textStyle);
	this->_selected.setPosition(pos.x + this->_body.getSize().x / 2.0f - this->_selected.getLocalBounds().width / 2.0f,
								pos.y + this->_body.getSize().y / 2.0f - this->_selected.getLocalBounds().height / 2.0f - this->_borderThickness);

	this->_body.setPosition(pos);
	this->_body.setFillColor(colorInfo.backgroundColor);
	this->_body.setOutlineThickness(colorInfo.borderThickness);
	this->_body.setOutlineColor(colorInfo.borderColor);
	this->setSize(sf::Vector2f(this->getSize().x + colorInfo.borderThickness, this->getSize().y + colorInfo.borderThickness));

	
}

ComboBox::~ComboBox()
{

}


// GUIElement's mouse event methods overload

void ComboBox::onMoveInside(sf::Vector2i const& pos)
{
	//Will be called when mouse is moving into the element
	nx::Log::inform("Mouse moving inside the ComboBox '" + this->getIdentifier() + "'");
}

void ComboBox::onMoveOutside(sf::Vector2i const& pos)
{
	//Will be called when mouse is moving outside the element
	nx::Log::inform("Mouse moving outside the ComboBox '" + this->getIdentifier() + "'");
}

void ComboBox::onLeftClickPressedInside(sf::Vector2i const& pos)
{
	sf::Rect<float> rectBody(this->_body.getPosition(), this->_body.getSize());

	//Will be called when the element has been left-clicked
	nx::Log::inform("Left-click pressed inside the ComboBox '" + this->getIdentifier() + "'");
	if (!this->_isScrolled && rectBody.contains(pos.x, pos.y))
	{
		this->_isScrolled = true;
		nx::Log::inform("Wasn't scrolled, clicked on body");
	}
	else if (this->_isScrolled && !rectBody.contains(pos.x, pos.y))
	{
		//Clicked on an elem..
		for (int i = 0; i < this->_bgSelections.size(); i++)
		{
			sf::Rect<float> rectElem(this->_bgSelections[i].getPosition(), this->_bgSelections[i].getSize());
			if (rectElem.contains(pos.x, pos.y))
			{
				nx::Log::inform("Clicked on element " + std::to_string(i));
				this->_idxSelected = i;
				this->_selected.setString(this->_selections[i]);
				this->_selected.setPosition(rectBody.left + rectBody.width / 2.0f - this->_selectionTexts[i].getLocalBounds().width / 2.0f,
											rectBody.top + rectBody.height / 2.0f - this->_selectionTexts[i].getLocalBounds().height / 2.0f - this->_borderThickness);
				break;
			}
		}
		this->_isScrolled = false;
		nx::Log::inform("Was scrolled, clicked on an element");
	}
	else
	{
		this->_isScrolled = false;
		nx::Log::inform("Was scrolled, clicked on body");
	}
}

void ComboBox::onLeftClickReleasedInside(sf::Vector2i const& pos)
{
	//Will be called when the element has been left-released
	nx::Log::inform("Left-click released inside the ComboBox '" + this->getIdentifier() + "'");
}

void ComboBox::onRightClickPressedInside(sf::Vector2i const& pos)
{
	//Will be called when the element has been right-clicked
	nx::Log::inform("Right-click pressed inside the ComboBox '" + this->getIdentifier() + "'");
}

void ComboBox::onRightClickReleasedInside(sf::Vector2i const& pos)
{
	//Will be called when the element has been right-released
	nx::Log::inform("Right-click released inside the ComboBox '" + this->getIdentifier() + "'");
}

void ComboBox::onLeftClickPressedOutside(sf::Vector2i const& pos)
{
	//Will be called when a left-click is outside the element
	nx::Log::inform("Left-click pressed outside the ComboBox '" + this->getIdentifier() + "'");
	this->_isScrolled = false;
}

void ComboBox::onLeftClickReleasedOutside(sf::Vector2i const& pos)
{
	//Will be called when a left-release is outside the element
	nx::Log::inform("Left-click released outside the ComboBox '" + this->getIdentifier() + "'");
}

void ComboBox::onRightClickPressedOutside(sf::Vector2i const& pos)
{
	//Will be called when a right-click is outside the element
	nx::Log::inform("Right-click pressed outside the ComboBox '" + this->getIdentifier() + "'");
}

void ComboBox::onRightClickReleasedOutside(sf::Vector2i const& pos)
{
	//Will be called when a right-release is outside the element
	nx::Log::inform("Right-click released outside the ComboBox '" + this->getIdentifier() + "'");
}

// Display

void ComboBox::show(std::shared_ptr<sf::RenderWindow> const& win)
{
	if (this->isVisible())
	{
		win->draw(this->_body);
		win->draw(this->_selected);
		if (this->_isScrolled)
		{
			for (auto itBg : this->_bgSelections)
				win->draw(itBg);
			for (auto itText : this->_selectionTexts)
				win->draw(itText);
		}
	}
}


// Specific functions for this element

void ComboBox::onStateChanged()
{
	//Will be called when the ComboBox's state has been changed
}


// Setters

void	ComboBox::setLabel(sf::Text const& label)
{
	this->_selected = label;
}

void	ComboBox::setBackgroundColor(sf::Color const& color)
{
	this->_backgroundColor = color;
	this->_body.setFillColor(this->_backgroundColor);
}

void	ComboBox::setBorderColor(sf::Color const& color)
{
	this->_borderColor = color;
	this->_body.setOutlineColor(this->_borderColor);
}

void	ComboBox::setBorderThickness(int const thickness)
{
	this->_borderThickness = thickness;
	this->setSize(sf::Vector2f(this->getSize().x + thickness, this->getSize().y + thickness));
	this->_body.setOutlineThickness(this->_borderThickness);
}
void	ComboBox::addSelection(std::string const& selection)
{
	sf::Text	text(selection, this->_font, this->_textInfo.fontSize);
	sf::RectangleShape rect(this->_body.getSize());

	this->_selections.push_back(selection);

	text.setFillColor(this->_textInfo.textColor);
	text.setStyle(this->_textInfo.textStyle);
	text.setPosition(this->getPos().x + this->_body.getSize().x / 2.0f - text.getLocalBounds().width / 2.0f,
					 this->getPos().y + this->_body.getSize().y / 2.0f - text.getLocalBounds().height / 2.0f - this->_borderThickness + this->_selections.size() * this->_body.getSize().y);

	rect.setPosition(sf::Vector2f(this->getPos().x, this->getPos().y + this->_borderThickness + this->_selections.size() * this->_body.getSize().y));
	rect.setFillColor(this->_colorInfo.backgroundColor);

	this->_bgSelections.push_back(rect);
	this->_selectionTexts.push_back(text);

	this->setSize(sf::Vector2f(this->getSize().x, this->getSize().y + rect.getSize().y));
}

void	ComboBox::setPos(sf::Vector2f const& pos)
{
	GUIElement::setPos(sf::Vector2f(pos.x - this->_borderThickness, pos.y - this->_borderThickness));
	this->_body.setPosition(pos);
	this->_selected.setPosition(pos.x + this->getSize().x / 2.0f - this->_selected.getLocalBounds().width / 2.0f,
								pos.y + this->getSize().y / 2.0f - this->_selected.getLocalBounds().height / 2.0f - this->_borderThickness);
}

void	ComboBox::setSize(sf::Vector2f const& size)
{
	GUIElement::setSize(size);
}

// Getters

std::string	const	ComboBox::getType() const
{
	return ("ComboBox");
}


// Specific getters

sf::Text const &	ComboBox::getLabel() const
{
	return (this->_selected);
}

sf::Color const &	ComboBox::getBackgroundColor() const
{
	return (this->_backgroundColor);
}

sf::Color const &	ComboBox::getBorderColor() const
{
	return (this->_borderColor);
}

int const			ComboBox::getBorderThickness() const
{
	return (this->_borderThickness);
}