#ifndef NX_GUI_GUILAYER_HPP_
# define NX_GUI_GUILAYER_HPP_

# include <vector>
# include <string>
# include <memory>
# include "GUIElement.hpp"

# include "../ElementNotFoundException.hpp"
# include "../NullElementException.hpp"

namespace nx
{
	namespace gui
	{
		class GUILayer
		{
			std::string									_identifier;
			bool										_isVisible;
			std::vector<std::shared_ptr<GUIElement>>	_guiElements;

		public:
			GUILayer(std::string const& identifier);
			~GUILayer();

			void	add(std::shared_ptr<GUIElement> const& elem);
			bool	remove(std::string const& elemId);

			// Setters
			void											setVisible(bool const state);

			// Getters
			std::string const &								getIdentifier() const;
			bool											isVisible() const;

			std::vector<std::shared_ptr<GUIElement>> const &	getElements() const;
			std::vector<std::shared_ptr<GUIElement>> &			getElements();
			std::shared_ptr<GUIElement> const &					getElementByName(std::string const& identifier) const;
			std::shared_ptr<GUIElement> &						getElementByName(std::string const& identifier);
			bool												object_exists(const std::string& identifier) const;
		};
	}
}

#endif /* NX_GUI_GUILAYER_HPP_ */