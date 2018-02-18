#ifndef NX_GUI_TEXT_HPP_
# define NX_GUI_TEXT_HPP_

# include <string>
# include "Nexus/log.hpp"
# include "GUIElement.hpp"
# include "../TextInfo.hpp"
# include "../InvalidFontException.hpp"
# include "../../frameworks/rendering/src/GraphicResources.hpp"

namespace nx
{
	namespace gui
	{
		class Text : public GUIElement
		{
			sf::Text			_label;

		public:
			Text(sf::Vector2f const& pos, std::string const& identifier, nx::env::MouseEventsContainer const& events, TextInfo const& textInfo);
			~Text();

			// Display
			void		show(std::shared_ptr<sf::RenderWindow> const& win);

			// Setters
			void setText(std::string const& text);
			void setFontSize(unsigned int const fontSize);

			void setPos(sf::Vector2f const& pos);
			void setSize(sf::Vector2f const& size);

			// Getters
			virtual std::string const		getType() const;

			// Specific getters
			std::string const	getText() const;
			unsigned int const	getFontSize() const;
		};
	}
}

#endif /* NX_GUI_TEXT_HPP_ */