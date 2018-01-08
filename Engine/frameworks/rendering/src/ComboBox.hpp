#ifndef COMBOBOX_HPP_
# define COMBOBOX_HPP_

# include <string>
# include "Nexus/log.hpp"
# include "GUIElement.hpp"
# include "ColorInfo.hpp"
# include "TextInfo.hpp"

class ComboBox : public GUIElement
{
	sf::Color						_backgroundColor;
	sf::Color						_borderColor;
	int								_borderThickness;
	sf::Font						_font;
	ColorInfo						_colorInfo;
	TextInfo						_textInfo;

	sf::RectangleShape				_body;

	int								_idxSelected;
	sf::Text						_selected;

	std::vector<std::string>		_selections;
	std::vector<sf::RectangleShape>	_bgSelections;
	std::vector<sf::Text>			_selectionTexts;

	bool							_isScrolled;

public:
	ComboBox(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, ColorInfo const& colorInfo, TextInfo const& textInfo);
	~ComboBox();

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
	void setLabel(sf::Text const& label);
	void setBackgroundColor(sf::Color const& color);
	void setBorderColor(sf::Color const& color);
	void setBorderThickness(int const thickness);
	void addSelection(std::string const& selection);

	void setPos(sf::Vector2f const& pos);
	void setSize(sf::Vector2f const& size);

	// Getters
	virtual std::string const		getType() const;

	// Specific getters
	sf::Text const &	getLabel() const;
	sf::Color const &	getBackgroundColor() const;
	sf::Color const &	getBorderColor() const;
	int const			getBorderThickness() const;
};

#endif /* COMBOBOX_HPP_ */