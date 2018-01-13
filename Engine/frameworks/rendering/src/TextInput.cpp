#include "TextInput.hpp"

TextInput::TextInput(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, ColorInfo const& colorInfo, TextInfo const& textInfo) :
	GUIElement(pos, size, identifier), _state(false),
	_backgroundColor(colorInfo.backgroundColor), _borderColor(colorInfo.borderColor), _borderThickness(colorInfo.borderThickness),
	_font(sf::Font()), _body(sf::RectangleShape(size)), _textData(textInfo.textLabel),
	_cursor(sf::VertexArray(sf::LinesStrip, 2)), _cursorIdx(textInfo.textLabel.length())
{
	this->_font.loadFromFile(textInfo.fontPath);
	this->_label = sf::Text(textInfo.textLabel, this->_font, textInfo.fontSize);
	this->_label.setFillColor(textInfo.textColor);
	this->_label.setStyle(textInfo.textStyle);
	this->_label.setPosition(pos.x + 3,
							 pos.y + this->getSize().y / 2.0f - this->_label.getLocalBounds().height / 2.0f - this->_borderThickness * 2);

	this->_body.setPosition(pos);
	this->_body.setFillColor(colorInfo.backgroundColor);
	this->_body.setOutlineThickness(colorInfo.borderThickness);
	this->_body.setOutlineColor(colorInfo.borderColor);

	this->_cursor[0].color = textInfo.textColor;
	this->_cursor[1].color = textInfo.textColor;
	this->_repositioningCursor();

	this->setSize(sf::Vector2f(this->getSize().x + colorInfo.borderThickness, this->getSize().y + colorInfo.borderThickness));
}

TextInput::~TextInput()
{

}


// GUIElement's mouse event methods overload

void TextInput::onLeftClickPressedInside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onLeftClickPressedInside");	
	
	//Will be called when the element has been left-clicked
	if (!this->_state)
	{
		this->_time = this->_clock.restart();
		this->_state = true;
	}
}

void TextInput::onLeftClickPressedOutside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onLeftClickPressedOutside");	
	
	//Will be called when a left-click is outside the element
	if (this->_state)
	{
		this->_state = false;
	}
}

void TextInput::keyTextEntered(char const charEntered)
{
	this->dispatchMouseEvent({}, "keyTextEntered");	
	
	//Will be called when text in entered
	if (!this->_state)
		return;
	if (charEntered != '\b' && charEntered != '\r' && charEntered != '\n')
	{
		this->_textData.insert(this->_cursorIdx, 1, charEntered);
		this->_label.setString(this->_textData);
		this->_cursorIdx += 1;

		this->_updateWrittenText();
		this->_repositioningCursor();
	}
}

void TextInput::keyPressed(sf::Keyboard::Key const& keyPressed)
{
	this->dispatchMouseEvent({}, "keyPressed");	
	
	//Will be called when a key is pressed
	if (!this->_state)
		return;
	if (keyPressed == sf::Keyboard::BackSpace && !this->_textData.empty() && this->_cursorIdx > 0)
	{
		this->_cursorIdx -= 1;
		this->_textData.erase(this->_cursorIdx, 1);
		this->_label.setString(this->_textData);
		this->_updateWrittenText();
		this->_repositioningCursor();
	}
	else if (keyPressed == sf::Keyboard::Delete && !this->_textData.empty())
	{
		this->_textData.erase(this->_cursorIdx, 1);
		this->_label.setString(this->_textData);
		this->_updateWrittenText();
		this->_repositioningCursor();
	}
	else if (keyPressed == sf::Keyboard::Left && this->_cursorIdx > 0)
	{
		this->_cursorIdx -= 1;
		this->_updateWrittenText();
		this->_repositioningCursor();
	}
	else if (keyPressed == sf::Keyboard::Right && this->_cursorIdx < this->_textData.length())
	{
		this->_cursorIdx += 1;
		this->_updateWrittenText();
		this->_repositioningCursor();
	}
}

// Display

void TextInput::show(std::shared_ptr<sf::RenderWindow> const& win)
{
	if (this->isVisible())
	{
		win->draw(this->_body);
		win->draw(this->_label);
		if (this->_state)
		{
			this->_time = this->_clock.getElapsedTime();
			if ((this->_time.asMilliseconds() / 500) % 2 == 0)
				win->draw(this->_cursor);
		}
	}
}


void TextInput::_repositioningCursor()
{
	// Repositioning the cursor
	sf::Text text("", this->_font, this->_label.getCharacterSize());

	for (int i = this->_cursorIdx; i < this->_textData.length() && text.getLocalBounds().width + 13 <= this->_body.getSize().x; ++i)
		text.setString(text.getString() + this->_textData[i]);

	this->_cursor[0].position = sf::Vector2f(this->_label.getPosition().x + this->_label.getLocalBounds().width - text.getLocalBounds().width,	
											 this->_body.getPosition().y + 7);
	this->_cursor[1].position = sf::Vector2f(this->_label.getPosition().x + this->_label.getLocalBounds().width - text.getLocalBounds().width,
											 this->_body.getPosition().y + this->_body.getSize().y - 7);
	if (this->_label.getPosition().x + this->_label.getLocalBounds().width - text.getLocalBounds().width < this->_label.getPosition().x)
	{
		this->_cursor[0].position = sf::Vector2f(this->_label.getPosition().x,	
												 this->_body.getPosition().y + 7);
		this->_cursor[1].position = sf::Vector2f(this->_label.getPosition().x,
												 this->_body.getPosition().y + this->_body.getSize().y - 7);
	}
}

void TextInput::_updateWrittenText()
{
	// Setting the scrolling text if needed
	this->_label.setString("");
	for (int i = this->_cursorIdx; i < this->_textData.length(); ++i)
	{
		this->_label.setString(this->_label.getString() + this->_textData[i]);
		if (i + 1 == this->_textData.length())
		{
			if (this->_label.getLocalBounds().width + 13 >= this->_body.getSize().x)
				break;
			else
				this->_updateTextFromEnd();
		}
		else if (this->_label.getLocalBounds().width + 13 >= this->_body.getSize().x)
			break;
	}
	if (this->_cursorIdx == this->_textData.length())
		this->_updateTextFromEnd();
}

void TextInput::_updateTextFromEnd()
{
	std::string rTextDataCpy(this->_textData);
	std::reverse(rTextDataCpy.begin(), rTextDataCpy.end());

	this->_label.setString("");
	for (auto it : rTextDataCpy)
	{
		this->_label.setString(it + this->_label.getString());
		if (this->_label.getLocalBounds().width + 13 > this->_body.getSize().x)
		{
			std::string final(this->_label.getString());
			final.erase(0, 1);
			this->_label.setString(final);
		}
	}
}

// Setters
void	TextInput::setState(bool const state)
{
	this->_state = state;
}

void	TextInput::setLabel(sf::Text const& label)
{
	this->_label = label;
}

void	TextInput::setBackgroundColor(sf::Color const& color)
{
	this->_backgroundColor = color;
	this->_body.setFillColor(this->_backgroundColor);
}

void	TextInput::setBorderColor(sf::Color const& color)
{
	this->_borderColor = color;
	this->_body.setOutlineColor(this->_borderColor);
}

void	TextInput::setBorderThickness(int const thickness)
{
	this->_borderThickness = thickness;
	this->setSize(sf::Vector2f(this->getSize().x + thickness, this->getSize().y + thickness));
	this->_body.setOutlineThickness(this->_borderThickness);
}

void	TextInput::setText(std::string const& text)
{
	this->_cursorIdx = 0;
	this->_textData = text;
	this->_updateWrittenText();
	this->_repositioningCursor();
}

void	TextInput::setCursorIdx(unsigned int const idx)
{
	this->_cursorIdx = idx;
	this->_updateWrittenText();
	this->_repositioningCursor();
}

void	TextInput::setPos(sf::Vector2f const& pos)
{
	GUIElement::setPos(sf::Vector2f(pos.x - this->_borderThickness, pos.y - this->_borderThickness));
	this->_body.setPosition(pos);
	this->_label.setPosition(pos.x + 3,
							 pos.y + this->getSize().y / 2.0f - this->_label.getLocalBounds().height / 2.0f - this->_borderThickness * 2);
	this->_updateWrittenText();
	this->_repositioningCursor();
}

void	TextInput::setSize(sf::Vector2f const& size)
{
	GUIElement::setSize(size);
	this->_body.setSize(sf::Vector2f(size.x - this->_borderThickness * 2, size.y - this->_borderThickness * 2));
	this->_label.setPosition(this->getPos().x + 3,
							 this->getPos().y + this->getSize().y / 2.0f - this->_label.getLocalBounds().height / 2.0f - this->_borderThickness * 2);
	this->_updateWrittenText();
	this->_repositioningCursor();
}

// Getters

std::string	const	TextInput::getType() const
{
	return ("TextInput");
}


// Specific getters

bool const			TextInput::getState() const
{
	return (this->_state);
}

sf::Text const &	TextInput::getLabel() const
{
	return (this->_label);
}

sf::Color const &	TextInput::getBackgroundColor() const
{
	return (this->_backgroundColor);
}

sf::Color const &	TextInput::getBorderColor() const
{
	return (this->_borderColor);
}

int const			TextInput::getBorderThickness() const
{
	return (this->_borderThickness);
}

std::string const & TextInput::getText() const
{
	return (this->_textData);
}

unsigned int const	TextInput::getCursorIdx() const
{
	return (this->_cursorIdx);
}