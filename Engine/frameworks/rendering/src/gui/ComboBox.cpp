#include "ComboBox.hpp"

nx::gui::ComboBox::ComboBox(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, nx::rendering::MouseEventsContainer const& events,
				   ColorInfo const& colorInfo, TextInfo const& textInfo) :
	GUIElement(pos, size, identifier, events),
	_backgroundColor(colorInfo.backgroundColor), _borderColor(colorInfo.borderColor), _borderThickness(colorInfo.borderThickness),
	_font(sf::Font()), _colorInfo(ColorInfo(colorInfo)), _textInfo(TextInfo(textInfo)), _body(sf::RectangleShape(size)), _idxSelected(-1), _isScrolled(false)
{
	this->_font.loadFromFile(textInfo.fontPath);
	this->_selected = sf::Text("- Nothing selected -", this->_font, this->_textInfo.fontSize);
	this->_selected.setFillColor(textInfo.textColor);
	this->_selected.setStyle(textInfo.textStyle);

	this->_body.setPosition(pos);
	this->_body.setFillColor(colorInfo.backgroundColor);
	this->_body.setOutlineThickness(static_cast<float>(colorInfo.borderThickness));
	this->_body.setOutlineColor(colorInfo.borderColor);

	GUIElement::setSize(sf::Vector2f(this->_body.getLocalBounds().width, this->_body.getLocalBounds().height));

	this->_recenteringSelectedText();
}

nx::gui::ComboBox::~ComboBox()
{

}


sf::Vector2f nx::gui::ComboBox::_calculateTotalSize()
{
	sf::Vector2f size(this->_body.getLocalBounds().width, this->_body.getLocalBounds().height);

	for (auto shape : this->_bgSelections)
		size.y += shape.getLocalBounds().height;

	return (size);
}

void	nx::gui::ComboBox::_recenteringSelectedText()
{
	this->_selected.setPosition(this->_body.getPosition().x + this->_body.getSize().x / 2.0f - this->_selected.getLocalBounds().width / 2.0f,
								this->_body.getPosition().y + this->_body.getSize().y / 2.0f - this->_selected.getLocalBounds().height / 2.0f - this->_borderThickness);
}

// GUIElement's mouse event methods overload

void nx::gui::ComboBox::onLeftClickPressedInside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onLeftClickPressedInside");

	if (this->_selections.empty())
		return;

	sf::Rect<float> rectBody(this->_body.getPosition(), this->_body.getSize());

	//Will be called when the element has been left-clicked
	if (!this->_isScrolled && rectBody.contains(static_cast<float>(pos.x), static_cast<float>(pos.y)))
	{
		this->_isScrolled = true;
		nx::Log::inform("Wasn't scrolled, clicked on body");
		GUIElement::setSize(this->_calculateTotalSize());
	}
	else if (this->_isScrolled && !rectBody.contains(static_cast<float>(pos.x), static_cast<float>(pos.y)))
	{
		//Clicked on an elem..
		for (int i = 0; i < static_cast<int>(this->_bgSelections.size()); i++)
		{
			sf::Rect<float> rectElem(this->_bgSelections[i].getPosition(), this->_bgSelections[i].getSize());
			if (rectElem.contains(static_cast<float>(pos.x), static_cast<float>(pos.y)))
			{
				this->_idxSelected = i;
				this->_selected.setString(this->_selections[i]);
				this->_recenteringSelectedText();
				break;
			}
		}
		GUIElement::setSize(this->_calculateTotalSize());
		this->_isScrolled = false;
	}
	else
	{
		GUIElement::setSize(this->_calculateTotalSize());
		this->_isScrolled = false;
	}
}

void nx::gui::ComboBox::onLeftClickPressedOutside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onLeftClickPressedOutside");	

	//Will be called when a left-click is outside the element
	if (this->_isScrolled)
	{
		this->_isScrolled = false;
		GUIElement::setSize(this->_calculateTotalSize());
	}
}

// Display

void nx::gui::ComboBox::show(std::shared_ptr<sf::RenderWindow> const& win)
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


// Setters

void	nx::gui::ComboBox::setBackgroundColor(sf::Color const& color)
{
	this->_backgroundColor = color;
	this->_body.setFillColor(this->_backgroundColor);
}

void	nx::gui::ComboBox::setBorderColor(sf::Color const& color)
{
	this->_borderColor = color;
	this->_body.setOutlineColor(this->_borderColor);
}

void	nx::gui::ComboBox::setBorderThickness(int const thickness)
{
	this->_borderThickness = thickness;
	this->_body.setOutlineThickness(static_cast<float>(this->_borderThickness));
	GUIElement::setSize(this->_calculateTotalSize());
}

void	nx::gui::ComboBox::setFontSize(unsigned int const fontSize)
{
	this->_selected.setCharacterSize(fontSize);

	for (auto text : this->_selectionTexts)
		text.setCharacterSize(fontSize);
}

void	nx::gui::ComboBox::addSelection(std::string const& selection)
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

	GUIElement::setSize(this->_calculateTotalSize());
}

void	nx::gui::ComboBox::removeSelection(std::string const& selection, uint16_t const nbTimes)
{
	uint16_t nb = nbTimes;

	this->_selectionTexts.erase(std::remove_if(this->_selectionTexts.begin(), this->_selectionTexts.end(),
								 [&](sf::Text selectionText) {
									std::string selectionStr = selectionText.getString().toAnsiString();
									if (selectionStr == selection && nb != 0)
									{
										this->_idxSelected = -1;
										this->_selected.setString("- Nothing selected -");
										this->_recenteringSelectedText();
										nb -= 1;
									}
									return (selectionStr == selection && nb != 0);
								 }),
								 this->_selectionTexts.end());
	GUIElement::setSize(this->_calculateTotalSize());
}

void	nx::gui::ComboBox::removeSelection(uint16_t const idx, uint16_t const nbTimes)
{
	if (idx >= this->_selectionTexts.size())
	{
		nx::Log::warning("The starting index given to remove selection(s) is out of range, ignoring..", "OUT_OF_RANGE");
		return;
	}
	this->_selectionTexts.erase(this->_selectionTexts.begin() + idx,
								(idx + nbTimes >= static_cast<uint16_t>(this->_selectionTexts.size())) ? (this->_selectionTexts.end()) : (this->_selectionTexts.begin() + idx + nbTimes));
	if (this->_idxSelected >= idx && this->_idxSelected < idx + nbTimes)
	{
		this->_idxSelected = -1;
		this->_selected.setString("- Nothing selected -");
		this->_recenteringSelectedText();
	}
	GUIElement::setSize(this->_calculateTotalSize());
}

void	nx::gui::ComboBox::clearSelections()
{
	this->_idxSelected = -1;
	this->_selected.setString("- Nothing selected -");
	this->_recenteringSelectedText();

	this->_bgSelections.clear();
	this->_selectionTexts.clear();
	GUIElement::setSize(this->_calculateTotalSize());
}

void	nx::gui::ComboBox::setPos(sf::Vector2f const& pos)
{
	GUIElement::setPos(sf::Vector2f(pos.x - this->_borderThickness, pos.y - this->_borderThickness));
	this->_body.setPosition(pos);
	this->_recenteringSelectedText();
}

void	nx::gui::ComboBox::setSize(sf::Vector2f const& size)
{
	//TODO: Resize the body and selections
	//GUIElement::setSize(this->_calculateTotalSize());
}

// Getters

std::string	const	nx::gui::ComboBox::getType() const
{
	return ("ComboBox");
}


// Specific getters

sf::Color const &	nx::gui::ComboBox::getBackgroundColor() const
{
	return (this->_backgroundColor);
}

sf::Color const &	nx::gui::ComboBox::getBorderColor() const
{
	return (this->_borderColor);
}

int const			nx::gui::ComboBox::getBorderThickness() const
{
	return (this->_borderThickness);
}

unsigned int const	nx::gui::ComboBox::getFontSize() const
{
	return (this->_selected.getCharacterSize());
}

std::string const	nx::gui::ComboBox::getSelected() const
{
	return (this->_selected.getString().toAnsiString());
}

uint16_t const		nx::gui::ComboBox::getIdxSelected() const
{
	return (this->_idxSelected);
}