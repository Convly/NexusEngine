#ifndef BUTTON_HPP_
# define BUTTON_HPP_

# include <string>
# include "GUIElement.hpp"

class Button : public GUIElement
{
	bool			_state;
	bool			_isPushButton;
	sf::Text		_label;
	sf::Color		_backgroundColor;
	sf::Color		_borderColor;
	int				_borderThickness;

public:
	Button(sf::Vector2f pos, sf::Vector2f size, std::string const& identifier, bool const isPushButton = true, sf::Text const& label = sf::Text());
	~Button();

	// GUIElement's mouse event methods overload
	virtual void onEnter();
	virtual void onLeave();
	virtual void onClick();

	// Specific functions for this element
	virtual void onStateChanged();

	// Display
	void		update();

	// Setters
	void setState(bool const state);
	void setLabel(sf::Text const& label);
	void setBackgroundColor(sf::Color const& color);
	void setBorderColor(sf::Color const& color);
	void setBorderThickness(int const thickness);

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