#ifndef NX_GRAPHICS_GRAPHICSELEMENT_HPP_
# define NX_GRAPHICS_GRAPHICSELEMENT_HPP_

# include <SFML/Graphics.hpp>
# include <memory>
# include <vector>
# include "Nexus/engine.hpp"

extern nx::Engine* enginePtr;

namespace nx
{
	namespace graphics
	{
		class GraphicsElement
		{
			sf::Vector2f										_pos;
			sf::Vector2f										_size;
			std::string											_identifier;
			bool												_isVisible;
			nx::env::MouseEventsContainer					_events;

		public:
			GraphicsElement(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, const nx::env::MouseEventsContainer& events);
			GraphicsElement(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier);
			virtual ~GraphicsElement();

			// Mouse events
			virtual void onMoveInside(sf::Vector2i const& pos);
			virtual void onMoveOutside(sf::Vector2i const& pos);
			virtual void onLeftClickPressedInside(sf::Vector2i const& pos);
			virtual void onLeftClickReleasedInside(sf::Vector2i const& pos);
			virtual void onRightClickPressedInside(sf::Vector2i const& pos);
			virtual void onRightClickReleasedInside(sf::Vector2i const& pos);
			virtual void onLeftClickPressedOutside(sf::Vector2i const& pos);
			virtual void onLeftClickReleasedOutside(sf::Vector2i const& pos);
			virtual void onRightClickPressedOutside(sf::Vector2i const& pos);
			virtual void onRightClickReleasedOutside(sf::Vector2i const& pos);
			virtual void keyTextEntered(char const charEntered);
			virtual void keyPressed(sf::Keyboard::Key const& keyPressed);

		protected:
			// Tools
			void dispatchMouseEvent(sf::Vector2i const& pos, std::string const& eventName);

		public:
			// Display
			virtual void show(std::shared_ptr<sf::RenderWindow> const& win) = 0;

			// Setters
			void				setPos(sf::Vector2f const& pos);
			void				setSize(sf::Vector2f const& size);
			void				setVisible(bool const state);

			// Getters
			sf::Vector2f const &										getPos() const;
			sf::Vector2f const &										getSize() const;
			std::string	const &											getIdentifier() const;
			bool														isVisible() const;
			nx::env::MouseEventsContainer const &					getEvents() const;
			virtual std::string	const									getType() const = 0;

		};
	}
}

#endif /* NX_GRAPHICS_GRAPHICSELEMENT_HPP_ */