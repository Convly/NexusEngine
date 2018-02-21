#ifndef NX_GUI_IMAGE_HPP_
# define NX_GUI_IMAGE_HPP_

# include <string>
# include "Nexus/log.hpp"
# include "GUIElement.hpp"
# include "../InvalidImageException.hpp"
# include "../../frameworks/rendering/src/GraphicResources.hpp"

namespace nx
{
	namespace gui
	{
		class Image : public GUIElement
		{
			std::string		_imgPath;

			sf::Sprite		_img;

			sf::Vector2f	_originalSize;

			void _loadImage();
			void _rescaleImage();

		public:
			Image(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, nx::env::MouseEventsContainer const& events,
				std::string const& imgPath);
			~Image();

			// Display
			void	show(std::shared_ptr<sf::RenderWindow> const& win);

			// Setters
			void	setImagePath(std::string const& spritePath);

			void	setPos(sf::Vector2f const& pos);
			void	setSize(sf::Vector2f const& size);

			// Getters
			virtual std::string const	getType() const;

			// Specific getters
			std::string const &		getImagePath() const;
		};
	}
}

#endif /* NX_GUI_IMAGE_HPP_ */