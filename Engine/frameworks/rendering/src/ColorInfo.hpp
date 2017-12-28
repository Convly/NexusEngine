#ifndef COLORINFO_HPP_
# define COLORINFO_HPP_

# include <string>
# include <SFML/Graphics/Color.hpp>

struct ColorInfo
{
	sf::Color		backgroundColor;
	sf::Color		borderColor;
	unsigned int	borderThickness;

	ColorInfo(sf::Color const& _backgroundColor, sf::Color const& _borderColor, unsigned int const _borderThickness) :
		backgroundColor(_backgroundColor), borderColor(_borderColor), borderThickness(_borderThickness) {};
	~ColorInfo() {};
};

#endif /* COLORINFO_HPP_ */