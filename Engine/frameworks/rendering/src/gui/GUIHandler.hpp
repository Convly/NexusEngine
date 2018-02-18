#ifndef NX_GUI_GUIHANDLER_HPP_
# define NX_GUI_GUIHANDLER_HPP_
    
# include <vector>
# include <memory>
# include "GUILayer.hpp"

# include "Button.hpp"
# include "Checkbox.hpp"
# include "ProgressBar.hpp"
# include "ComboBox.hpp"
# include "TextInput.hpp"
# include "Text.hpp"
# include "Image.hpp"
# include "Sprite.hpp"

# include "../LayerNotFoundException.hpp"
# include "../InvalidCastElementException.hpp"

namespace nx
{
	namespace gui
	{
		class GUIHandler
		{
			std::vector<GUILayer>					_guiLayers;
			std::shared_ptr<sf::RenderWindow>		_win;

		public:
			GUIHandler(std::shared_ptr<sf::RenderWindow> const& win);
			~GUIHandler();

			void	addLayer(GUILayer const& elem);
			bool	removeLayer(std::string const& layerId);

			// Events
			void	processEvent(sf::Event const& event);

			// Display
			void	drawLayers();

			// Getters
			std::vector<GUILayer> const &					getLayers() const;
			std::vector<GUILayer> &							getLayers();
			GUILayer  const &								getLayerByName(std::string const& identifier) const;
			GUILayer &										getLayerByName(std::string const& identifier);
			const bool 										layer_exists(const std::string&) const;
		};
	}
}

#endif /* NX_GUI_GUIHANDLER_HPP_ */