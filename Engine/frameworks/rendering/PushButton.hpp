#ifndef PUSHBUTTON_HPP_
# define PUSHBUTTON_HPP_

# include <string>
# include "GUIElement.hpp"

class PushButton : public GUIElement
{
	bool			_state;
	std::string		_label;

public:
	PushButton(sf::Vector2f pos, sf::Vector2f size, std::string const& identifier, std::string const& label);
	~PushButton();

	// GUIElement's mouse event methods overload
	virtual void onEnter();
	virtual void onLeave();
	virtual void onClick();

	// Specific functions for this element
	void		onStateChanged();

	// Getters
	bool		getState() const;
	std::string	getLabel() const;
};

#endif /* PUSHBUTTON_HPP_ */