#ifndef NX_GRAPHICS_CIRCLESHAPE_HPP_
# define NX_GRAPHICS_CIRCLESHAPE_HPP_

# include <string>
# include <numeric>
# include "Nexus/log.hpp"
# include "GraphicsElement.hpp"
# include "../ColorInfo.hpp"

namespace nx
{
	namespace graphics
	{
		class CircleShape : public GraphicsElement
		{
			sf::CircleShape	_body;

		public:
			CircleShape(sf::Vector2f const & pos, sf::Vector2f const & size, std::string const & identifier,
				nx::rendering::MouseEventsContainer const & events, float const radius, nx::ColorInfo const& colorInfo);
			~CircleShape();

			// Display
			void	show(std::shared_ptr<sf::RenderWindow> const& win);

			// Setters
			void	setBackgroundColor(sf::Color const& color);
			void	setBorderColor(sf::Color const& color);
			void	setBorderThickness(int const thickness);
			void	setRotation(float const angle);
			void	setRadius(float const radius);
			//TODO: Others functions that can be used as a CircleShape => https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1CircleShape.php

			void	setPos(sf::Vector2f const& pos);
			void	setSize(sf::Vector2f const& size);

			// Getters
			virtual std::string const	getType() const;

			// Specific getters
			sf::Color const&	getBackgroundColor() const;
			sf::Color const&	getBorderColor() const;
			int const			getBorderThickness() const;
			float const			getRotation() const;
			float const			getRadius() const;
		};
	}
}

#endif /* NX_GRAPHICS_CIRCLESHAPE_HPP_ */