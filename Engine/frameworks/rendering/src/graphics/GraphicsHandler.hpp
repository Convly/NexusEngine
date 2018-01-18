#ifndef NX_GRAPHICS_GRAPHICSHANDLER_HPP_
# define NX_GRAPHICS_GRAPHICSHANDLER_HPP_
    
# include <vector>
# include <memory>

# include "GraphicsElement.hpp"

# include "Sprite.hpp"
# include "RectShape.hpp"
# include "CircleShape.hpp"
# include "ConvexShape.hpp"

# include "../LayerNotFoundException.hpp"
# include "../InvalidCastElementException.hpp"

namespace nx
{
	namespace graphics
	{
		class GraphicsHandler
		{
			std::vector<std::shared_ptr<GraphicsElement>>	_graphicsElements;
			std::shared_ptr<sf::RenderWindow>		_win;

		public:
			GraphicsHandler(std::shared_ptr<sf::RenderWindow> const& win);
			~GraphicsHandler();

			void	addElement(std::shared_ptr<GraphicsElement> elem);

			// Events
			void	processEvent(sf::Event const& event);

			// Display
			void	drawElements();

			// Getters
			std::vector<std::shared_ptr<GraphicsElement>> const &	getElements() const;
			std::vector<std::shared_ptr<GraphicsElement>>&			getElements();
			std::shared_ptr<GraphicsElement> const &				getElementByName(std::string const& identifier) const;
			std::shared_ptr<GraphicsElement>&						getElementByName(std::string const& identifier);
			const bool 												object_exists(const std::string&) const;
		};
	}
}

#endif /* NX_GRAPHICS_GRAPHICSHANDLER_HPP_ */