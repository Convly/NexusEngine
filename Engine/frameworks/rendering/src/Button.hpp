#ifndef BUTTON_HPP_
# define BUTTON_HPP_

# include <string>
# include "Nexus/log.hpp"
# include "GUIElement.hpp"
# include "ColorInfo.hpp"
# include "TextInfo.hpp"

class Button : public GUIElement
{
	bool				_state;
	bool				_isPushButton;
	sf::Color			_backgroundColor;
	sf::Color			_borderColor;
	int					_borderThickness;
	sf::Font			_font;
	sf::Text			_label;
	sf::RectangleShape	_body;

public:
	Button(sf::Vector2f pos, sf::Vector2f size, std::string const& identifier, bool const isPushButton, ColorInfo const& colorInfo, TextInfo const& textInfo);
	~Button();

	// GUIElement's mouse event methods overload
	virtual void onEnter();
	virtual void onLeave();
	virtual void onLeftClickPressedInside();
	virtual void onLeftClickReleasedInside();
	virtual void onRightClickPressedInside();
	virtual void onRightClickReleasedInside();
	virtual void onLeftClickPressedOutside();
	virtual void onLeftClickReleasedOutside();
	virtual void onRightClickPressedOutside();
	virtual void onRightClickReleasedOutside();

	// Specific functions for this element
	virtual void onStateChanged();

	// Display
	void		show(std::shared_ptr<sf::RenderWindow> const& win);

	// Setters
	void setState(bool const state);
	void setLabel(sf::Text const& label);
	void setBackgroundColor(sf::Color const& color);
	void setBorderColor(sf::Color const& color);
	void setBorderThickness(int const thickness);

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
};

#endif /* BUTTON_HPP_ */