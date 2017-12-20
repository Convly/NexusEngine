#ifndef GUIELEMENT_HPP_
# define GUIELEMENT_HPP_

# include <SFML/Graphics.hpp>

class GUIElement
{
	sf::Vector2f	_pos;
	sf::Vector2f	_size;
	std::string		_identifier;
	bool			_isVisible;

public:
	GUIElement(sf::Vector2f pos, sf::Vector2f size, std::string const& identifier);
	~GUIElement();

	// Mouse events
	virtual void onEnter();
	virtual void onLeave();
	virtual void onClick();

	// Display
	virtual void show() = 0;

	// Setters
	void					setVisible(bool const state);

	// Getters
	virtual sf::Vector2f	getPos() const;
	virtual sf::Vector2f	getSize() const;
	virtual std::string		getIdentifier() const;
	virtual bool			isVisible() const;
	virtual std::string		getType() const = 0;
};

#endif /* GUIELEMENT_HPP_ */