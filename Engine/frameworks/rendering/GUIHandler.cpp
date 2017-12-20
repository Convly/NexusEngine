#include "GUIHandler.hpp"

GUIHandler::GUIHandler()
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
	for (auto it : this->_guiLayers)
	{
		if (it->isVisible())
			it->draw();
	}
}


// Getters

std::vector<std::shared_ptr<GUILayer>>	GUIHandler::getLayers() const
{
	return (this->_guiLayers);
}