#ifndef GUIELEMENT_HPP_
# define GUIELEMENT_HPP_

# include "Nexus/engine.hpp"
# include <SFML/Graphics.hpp>
# include <memory>
# include <vector>

class GUIElement
{
	sf::Vector2f										_pos;
	sf::Vector2f										_size;
	std::string											_identifier;
	bool												_isVisible;
	nx::rendering::MouseEventsContainer					_events;

public:
	GUIElement(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, const nx::rendering::MouseEventsContainer& events);
	GUIElement(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier);
	virtual ~GUIElement();

	// Mouse events
	void onMoveInside(sf::Vector2i const& pos);
	void onMoveOutside(sf::Vector2i const& pos);
	void onLeftClickPressedInside(sf::Vector2i const& pos);
	void onLeftClickReleasedInside(sf::Vector2i const& pos);
	void onRightClickPressedInside(sf::Vector2i const& pos);
	void onRightClickReleasedInside(sf::Vector2i const& pos);
	void onLeftClickPressedOutside(sf::Vector2i const& pos);
	void onLeftClickReleasedOutside(sf::Vector2i const& pos);
	void onRightClickPressedOutside(sf::Vector2i const& pos);
	void onRightClickReleasedOutside(sf::Vector2i const& pos);

private:
	// Tools
	void dispatchMouseEvent(sf::Vector2i const& pos, std::string const& eventName);


public:

	// Display
	virtual void show(std::shared_ptr<sf::RenderWindow> const& win) = 0;

	// Setters
	void				setPos(sf::Vector2f const& pos);
	void				setSize(sf::Vector2f const& size);
	void				setVisible(bool const state);

	// Getters
	sf::Vector2f const &										getPos() const;
	sf::Vector2f const &										getSize() const;
	std::string	const &											getIdentifier() const;
	bool														isVisible() const;
	nx::rendering::MouseEventsContainer const &					getEvents() const;
	virtual std::string	const									getType() const = 0;

};

#endif /* GUIELEMENT_HPP_ */