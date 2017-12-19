#ifndef GUIELEMENT_HPP_
# define GUIELEMENT_HPP_

# include <SFML/Graphics.hpp>

class GUIElement
{
	sf::Vector2f	_pos;
	sf::Vector2f	_size;
	std::string		_identifier;

public:
	GUIElement(sf::Vector2f pos, sf::Vector2f size, std::string const& identifier);
	~GUIElement();

	// Mouse events
	virtual void onEnter();
	virtual void onLeave();
	virtual void onClick();

	// Display
	virtual void show();

	// Getters
	virtual sf::Vector2f	getPos() const;
	virtual sf::Vector2f	getSize() const;
	virtual std::string		getIdentifier() const;
};

#endif /* GUIELEMENT_HPP_ */