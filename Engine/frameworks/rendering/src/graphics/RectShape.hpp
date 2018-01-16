#ifndef NX_GRAPHICS_RECTSHAPE_HPP_
# define NX_GRAPHICS_RECTSHAPE_HPP_

# include <string>
# include <numeric>
# include "Nexus/log.hpp"
# include "GraphicsElement.hpp"
# include "../ColorInfo.hpp"

namespace nx
{
	namespace graphics
	{
		class RectShape : public GraphicsElement
		{
			sf::RectangleShape	_body;

		public:
			RectShape(sf::Vector2f const & pos, sf::Vector2f const & size, std::string const & identifier,
					  nx::rendering::MouseEventsContainer const & events, nx::ColorInfo const& colorInfo);
			~RectShape();

			// Display
			void	show(std::shared_ptr<sf::RenderWindow> const& win);

			// Setters
			void	setBackgroundColor(sf::Color const& color);
			void	setBorderColor(sf::Color const& color);
			void	setBorderThickness(int const thickness);
			void	setRotation(float const angle);
			//TODO: Others functions that can be used as a RectangleShape => https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1RectangleShape.php

			void	setPos(sf::Vector2f const& pos);
			void	setSize(sf::Vector2f const& size);

			// Getters
			virtual std::string const	getType() const;

			// Specific getters
			sf::Color const&	getBackgroundColor() const;
			sf::Color const&	getBorderColor() const;
			int const			getBorderThickness() const;
			float const			getRotation() const;
		};
	}
}

#endif /* NX_GRAPHICS_RECTSHAPE_HPP_ */