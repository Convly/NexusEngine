#ifndef TEXTINFO_HPP_
# define TEXTINFO_HPP_

# include <string>
# include <SFML/Graphics/Color.hpp>
# include <SFML/Graphics/Text.hpp>

struct TextInfo
{
	std::string		fontPath;
	std::string		textLabel;
	unsigned int	fontSize;
	sf::Color		textColor;
	uint32_t		textStyle;

	TextInfo(std::string const& _fontPath, std::string const& _textLabel = "", unsigned int const _fontSize = 30, sf::Color const& _textColor = sf::Color(255, 255, 255, 255), uint32_t const _textStyle = sf::Text::Style::Regular) :
		fontPath(_fontPath), textLabel(_textLabel), fontSize(_fontSize), textColor(_textColor), textStyle(_textStyle) {};
	TextInfo(TextInfo const& textInfo) :
		fontPath(textInfo.fontPath), textLabel(textInfo.textLabel), fontSize(textInfo.fontSize), textColor(textInfo.textColor), textStyle(textInfo.textStyle) {}
	~TextInfo() {};
};

#endif /* TEXTINFO_HPP_ */