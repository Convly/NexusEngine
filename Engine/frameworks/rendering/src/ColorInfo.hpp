#ifndef NX_COLORINFO_HPP_
# define NX_COLORINFO_HPP_

# include <string>
# include <SFML/Graphics/Color.hpp>

namespace nx
{
	struct ColorInfo
	{
		sf::Color		backgroundColor;
		sf::Color		borderColor;
		unsigned int	borderThickness;

		ColorInfo(sf::Color const& _backgroundColor, sf::Color const& _borderColor, unsigned int const _borderThickness) :
			backgroundColor(_backgroundColor), borderColor(_borderColor), borderThickness(_borderThickness) {};
		ColorInfo(ColorInfo const& colorInfo) :
			backgroundColor(colorInfo.backgroundColor), borderColor(colorInfo.borderColor), borderThickness(colorInfo.borderThickness) {}
		~ColorInfo() {};
	};
}

#endif /* NX_COLORINFO_HPP_ */