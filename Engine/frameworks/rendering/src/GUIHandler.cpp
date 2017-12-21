#include "GUIHandler.hpp"
#include "Nexus/log.hpp"

GUIHandler::GUIHandler(std::shared_ptr<sf::RenderWindow> const& win):
	_win(win)
{

}
GUIHandler::~GUIHandler()
{

}

void	GUIHandler::addLayer(std::shared_ptr<GUILayer> layer)
{
	this->_guiLayers.push_back(layer);
}


// Display

void GUIHandler::drawLayers()
{
	for (auto itLayer : this->_guiLayers)
	{
		if (itLayer->isVisible())
		{
			auto elems = itLayer->getElements();
			for (auto itElem : elems)
			{
				if (itElem->isVisible())
				{
					itElem->show(this->_win);
				}
			}
		}
	}
}


// Getters

std::vector<std::shared_ptr<GUILayer>>	const &	GUIHandler::getLayers() const
{
	return (this->_guiLayers);
}

std::shared_ptr<GUILayer> const &				GUIHandler::getLayerByName(std::string const& identifier) const
{
	for (auto &it : this->_guiLayers)
	{
		if (it->getIdentifier() == identifier)
			return (it);
	}
	throw (nx::LayerNotFoundException(identifier));
}