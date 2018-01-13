#ifndef TEXT_HPP_
# define TEXT_HPP_

# include <string>
# include "Nexus/log.hpp"
# include "GUIElement.hpp"
# include "TextInfo.hpp"

class Text : public GUIElement
{
	sf::Font			_font;
	sf::Text			_label;

public:
	Text(sf::Vector2f const& pos, std::string const& identifier, TextInfo const& textInfo);
	~Text();

	// Display
	void		show(std::shared_ptr<sf::RenderWindow> const& win);

	// Setters
	void setLabel(sf::Text const& label);
	void setText(std::string const& text);

	void setPos(sf::Vector2f const& pos);
	void setSize(sf::Vector2f const& size);

	// Getters
	virtual std::string const		getType() const;

	// Specific getters
	sf::Text const &	getLabel() const;
	std::string const	getText() const;
};

#endif /* TEXT_HPP_ */