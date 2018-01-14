#ifndef TEXTINPUT_HPP_
# define TEXTINPUT_HPP_

# include <string>
# include "Nexus/log.hpp"
# include "GUIElement.hpp"
# include "ColorInfo.hpp"
# include "TextInfo.hpp"

class TextInput : public GUIElement
{
	bool				_state;
	sf::Color			_backgroundColor;
	sf::Color			_borderColor;
	int					_borderThickness;
	sf::Font			_font;
	sf::Text			_label;
	sf::RectangleShape	_body;
	std::string			_textData;

	sf::VertexArray		_cursor;
	unsigned int		_cursorIdx;

	sf::Clock			_clock;
	sf::Time			_time;

	// Specific functions for this element
	void _repositioningCursor();
	void _updateWrittenText();
	void _updateTextFromEnd();

public:
	TextInput(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier,
			  nx::rendering::MouseEventsContainer const& events, ColorInfo const& colorInfo, TextInfo const& textInfo);
	~TextInput();

	// GUIElement's mouse event methods overload
	virtual void onLeftClickPressedInside(sf::Vector2i const& pos);
	virtual void onLeftClickPressedOutside(sf::Vector2i const& pos);
	virtual void keyTextEntered(char const charEntered);
	virtual void keyPressed(sf::Keyboard::Key const& keyPressed);

	// Display
	void		show(std::shared_ptr<sf::RenderWindow> const& win);

	// Setters
	void setState(bool const state);
	void setLabel(sf::Text const& label);
	void setBackgroundColor(sf::Color const& color);
	void setBorderColor(sf::Color const& color);
	void setBorderThickness(int const thickness);
	void setText(std::string const& text);
	void setCursorIdx(unsigned int idx);

	void setPos(sf::Vector2f const& pos);
	void setSize(sf::Vector2f const& size);

	// Getters
	virtual std::string const		getType() const;

	// Specific getters
	bool const			getState() const;
	sf::Text const &	getLabel() const;
	sf::Color const &	getBackgroundColor() const;
	sf::Color const &	getBorderColor() const;
	int const			getBorderThickness() const;
	std::string const & getText() const;
	unsigned int const	getCursorIdx() const;
};

#endif /* TEXTINPUT_HPP_ */