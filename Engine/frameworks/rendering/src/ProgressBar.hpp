#ifndef PROGRESSBAR_HPP_
# define PROGRESSBAR_HPP_

# include <string>
# include "GUIElement.hpp"
# include "Nexus/log.hpp"
# include "ColorInfo.hpp"
# include "TextInfo.hpp"

class ProgressBar : public GUIElement
{
	sf::Color						_backgroundColor;
	sf::Color						_borderColor;
	int								_borderThickness;
	sf::RectangleShape				_body;
	sf::RectangleShape				_filled;
	int								_percentage;
	sf::Font						_font;
	sf::Text						_label;

public:
	ProgressBar(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, ColorInfo const& colorInfo, TextInfo const& textInfo, bool const displayPercentage = true);
	~ProgressBar();

	// GUIElement's mouse event methods overload
	virtual void onMoveInside(sf::Vector2i const& pos);
	virtual void onMoveOutside(sf::Vector2i const& pos);
	virtual void onLeftClickPressedInside(sf::Vector2i const& pos);
	virtual void onLeftClickReleasedInside(sf::Vector2i const& pos);
	virtual void onRightClickPressedInside(sf::Vector2i const& pos);
	virtual void onRightClickReleasedInside(sf::Vector2i const& pos);
	virtual void onLeftClickPressedOutside(sf::Vector2i const& pos);
	virtual void onLeftClickReleasedOutside(sf::Vector2i const& pos);
	virtual void onRightClickPressedOutside(sf::Vector2i const& pos);
	virtual void onRightClickReleasedOutside(sf::Vector2i const& pos);

	// Specific functions for this element
	virtual void onStateChanged();

	// Display
	void		show(std::shared_ptr<sf::RenderWindow> const& win);

	// Setters
	void		setBackgroundColor(sf::Color const& color);
	void		setBorderColor(sf::Color const& color);
	void		setBorderThickness(int const thickness);
	void		setFilled(int const percentage);
	void		setLabel(sf::Text const& label);

	void		setPos(sf::Vector2f const& pos);
	void		setSize(sf::Vector2f const& size);

	// Getters
	virtual std::string const	getType() const;

	// Specific getters
	sf::Color const	&	getBackgroundColor() const;
	sf::Color const	&	getBorderColor() const;
	int const			getBorderThickness() const;
	int const			getFilled() const;
	sf::Text const &	getLabel() const;
};

#endif /* PROGRESSBAR_HPP_ */