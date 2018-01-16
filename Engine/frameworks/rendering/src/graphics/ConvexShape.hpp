#ifndef NX_GRAPHICS_CONVEXSHAPE_HPP_
# define NX_GRAPHICS_CONVEXSHAPE_HPP_

# include <string>
# include <numeric>
# include "Nexus/log.hpp"
# include "GraphicsElement.hpp"
# include "../ColorInfo.hpp"

namespace nx
{
	namespace graphics
	{
		class ConvexShape : public GraphicsElement
		{
			sf::ConvexShape	_body;

		public:
			ConvexShape(sf::Vector2f const & pos, sf::Vector2f const & size, std::string const & identifier,
						nx::rendering::MouseEventsContainer const & events, nx::ColorInfo const& colorInfo);
			~ConvexShape();

			// Display
			void	show(std::shared_ptr<sf::RenderWindow> const& win);

			// Setters
			void	setBackgroundColor(sf::Color const& color);
			void	setBorderColor(sf::Color const& color);
			void	setBorderThickness(int const thickness);
			void	setRotation(float const angle);
			void	setPointCount(size_t const pointCount);
			void	setPoint(size_t const index, sf::Vector2f const& point);
			//TODO: Others functions that can be used as a ConvexShape => https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1ConvexShape.php

			void	setPos(sf::Vector2f const& pos);
			void	setSize(sf::Vector2f const& size);

			// Getters
			virtual std::string const	getType() const;

			// Specific getters
			sf::Color const&	getBackgroundColor() const;
			sf::Color const&	getBorderColor() const;
			int const			getBorderThickness() const;
			float const			getRotation() const;
			size_t const		getPointCount() const;
			sf::Vector2f const	getPoint(size_t const index) const;
		};
	}
}

#endif /* NX_GRAPHICS_CONVEXSHAPE_HPP_ */