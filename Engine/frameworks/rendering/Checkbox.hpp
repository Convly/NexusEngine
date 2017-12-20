#ifndef CHECKBOX_HPP_
# define CHECKBOX_HPP_

# include <string>
# include "GUIElement.hpp"

class Checkbox : public GUIElement
{
	enum State : int
	{
		UNCHECKED = 0,
		PARTIAL = 1,
		CHECKED
	};

	State			_state;
	sf::Color		_backgroundColor;
	sf::Color		_borderColor;
	int				_borderThickness;

public:
	Checkbox(sf::Vector2f pos, sf::Vector2f size, std::string const& identifier);
	~Checkbox();

	// GUIElement's mouse event methods overload
	virtual void onEnter();
	virtual void onLeave();
	virtual void onClick();

	// Specific functions for this element
	virtual void onStateChanged();

	// Display
	void		update();

	// Setters
	void		setState(State const state);
	void		setBackgroundColor(sf::Color const& color);
	void		setBorderColor(sf::Color const& color);
	void		setBorderThickness(int const thickness);

	// Getters
	virtual std::string const	getType() const;

	// Specific getters
	State const			getState() const;
	sf::Color const	&	getBackgroundColor() const;
	sf::Color const	&	getBorderColor() const;
	int const			getBorderThickness() const;
};

#endif /* CHECKBOX_HPP_ */