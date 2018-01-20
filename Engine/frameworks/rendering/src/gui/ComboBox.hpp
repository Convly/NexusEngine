#ifndef NX_GUI_COMBOBOX_HPP_
# define NX_GUI_COMBOBOX_HPP_

# include <string>
# include "Nexus/log.hpp"
# include "GUIElement.hpp"
# include "../ColorInfo.hpp"
# include "../TextInfo.hpp"

namespace nx
{
	namespace gui
	{
		class ComboBox : public GUIElement
		{
			sf::Color						_backgroundColor;
			sf::Color						_borderColor;
			int								_borderThickness;
			sf::Font						_font;
			ColorInfo						_colorInfo;
			TextInfo						_textInfo;

			sf::RectangleShape				_body;

			uint16_t						_idxSelected;
			sf::Text						_selected;

			std::vector<std::string>		_selections;
			std::vector<sf::RectangleShape>	_bgSelections;
			std::vector<sf::Text>			_selectionTexts;

			bool							_isScrolled;

			void			_recenteringSelectedText();
			sf::Vector2f	_calculateTotalSize();

		public:
			ComboBox(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, nx::rendering::MouseEventsContainer const& events,
				ColorInfo const& colorInfo, TextInfo const& textInfo);
			~ComboBox();

			// GUIElement's mouse event methods overload
			virtual void onLeftClickPressedInside(sf::Vector2i const& pos);
			virtual void onLeftClickPressedOutside(sf::Vector2i const& pos);

			// Display
			void		show(std::shared_ptr<sf::RenderWindow> const& win);

			// Setters
			void setBackgroundColor(sf::Color const& color);
			void setBorderColor(sf::Color const& color);
			void setBorderThickness(int const thickness);
			void setFontSize(unsigned int const fontSize);

			void addSelection(std::string const& selection);
			void removeSelection(std::string const& selection, uint16_t const nbTimes);
			void removeSelection(uint16_t const idx, uint16_t const nbTimes);
			void clearSelections();

			void setPos(sf::Vector2f const& pos);
			void setSize(sf::Vector2f const& size);

			// Getters
			virtual std::string const		getType() const;

			// Specific getters
			sf::Color const &	getBackgroundColor() const;
			sf::Color const &	getBorderColor() const;
			int const			getBorderThickness() const;
			unsigned int const	getFontSize() const;
			std::string const	getSelected() const;
			uint16_t const		getIdxSelected() const;
		};
	}
}

#endif /* NX_GUI_COMBOBOX_HPP_ */