#ifndef NX_GUI_BUTTON_HPP_
# define NX_GUI_BUTTON_HPP_

# include <string>
# include "Nexus/log.hpp"
# include "GUIElement.hpp"
# include "../ColorInfo.hpp"
# include "../TextInfo.hpp"

namespace nx
{
	namespace gui
	{
		class Button : public GUIElement
		{
			bool				_state;
			bool				_isPushButton;
			sf::Color			_borderColor;
			int					_borderThickness;
			sf::Font			_font;
			sf::Text			_label;
			sf::RectangleShape	_body;

			sf::Color			_colorNotSelected;
			sf::Color			_colorSelected;

			// Specific functions for this element
			void _onStateChanged();
			void _recenteringLabelText();

		public:
			Button(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, nx::rendering::MouseEventsContainer const& events,
				bool const isPushButton, ColorInfo const& colorInfo, TextInfo const& textInfo);
			~Button();

			// GUIElement's mouse event methods overload
			virtual void onLeftClickPressedInside(sf::Vector2i const& pos);
			virtual void onLeftClickReleasedInside(sf::Vector2i const& pos);
			virtual void onLeftClickReleasedOutside(sf::Vector2i const& pos);

			// Display
			void		show(std::shared_ptr<sf::RenderWindow> const& win);

			// Setters
			void setState(bool const state);
			void setText(std::string const& text);
			void setFontSize(unsigned int const fontSize);
			void setColorNotSelected(sf::Color const& color);
			void setColorSelected(sf::Color const& color);
			void setBorderColor(sf::Color const& color);
			void setBorderThickness(int const thickness);

			void setPos(sf::Vector2f const& pos);
			void setSize(sf::Vector2f const& size);

			// Getters
			virtual std::string const		getType() const;

			// Specific getters
			bool const			getState() const;
			std::string const	getText() const;
			unsigned int const	getFontSize() const;
			sf::Color const &	getColorNotSelected() const;
			sf::Color const &	getColorSelected() const;
			sf::Color const &	getBorderColor() const;
			int const			getBorderThickness() const;
		};
	}
}

#endif /* NX_GUI_BUTTON_HPP_ */