#ifndef NX_GUI_SPRITE_HPP_
# define NX_GUI_SPRITE_HPP_

# include <string>
# include <numeric>
# include "Nexus/log.hpp"
# include "GUIElement.hpp"
# include "../InvalidImageException.hpp"

namespace nx
{
	namespace gui
	{
		class Sprite : public GUIElement
		{
			std::string				_spritesheetPath;
			sf::Vector2f			_sheetGrid;
			sf::Vector2f			_spriteSize;

			sf::Texture				_texture;
			sf::Sprite				_sprite;

			sf::Vector2f			_originalSize;

			uint16_t				_spriteIdx;
			uint16_t				_slowness;

			bool					_isAnimated;
			std::vector<uint16_t>	_spritesAnimated;
			uint16_t				_animationIdx;

			sf::Clock				_clock;
			sf::Time				_time;


			void _loadSpritesheet();
			void _refreshSprite();
			void _rescaleSprite();

		public:
			Sprite(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, nx::env::MouseEventsContainer const& events,
				std::string const& spritesheetPath, sf::Vector2f const& sheetGrid, sf::Vector2f const& spriteSize);
			~Sprite();

			// Display
			void	show(std::shared_ptr<sf::RenderWindow> const& win);

			// Setters
			void	setSpritesheetPath(std::string const& spritesheetPath);
			void	setSpriteIdx(uint16_t const spriteIdx);
			void	setSlowness(uint16_t const slowness);
			void	setAnimate(bool const animate);
			void	setSpritesAnimated(std::vector<uint16_t> const& spritesAnimated);
			void	setAnimationIdx(uint16_t const animationIdx);

			void	setPos(sf::Vector2f const& pos);
			void	setSize(sf::Vector2f const& size);

			// Getters
			virtual std::string const	getType() const;

			// Specific getters
			std::string const &				getSpritesheetPath() const;
			uint16_t const					getSpriteIdx() const;
			uint16_t const					getSlowness() const;
			bool const						getAnimate() const;
			std::vector<uint16_t> const &	getSpritesAnimated() const;
			uint16_t const					getAnimationIdx() const;
		};
	}
}

#endif /* NX_GUI_SPRITE_HPP_ */