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


// Events

void GUIHandler::processEvent(sf::Event const& event)
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
					sf::Rect<float> rect(itElem->getPos(), itElem->getSize());

					if (event.mouseButton.button == sf::Mouse::Left)
					{
						if (event.type == sf::Event::MouseButtonPressed)
						{
							if (rect.contains(event.mouseButton.x, event.mouseButton.y))
								itElem->onLeftClickPressedInside();
							else
								itElem->onLeftClickPressedOutside();
						}
						else if (event.type == sf::Event::MouseButtonReleased)
						{
							if (rect.contains(event.mouseButton.x, event.mouseButton.y))
								itElem->onLeftClickReleasedInside();
							else
								itElem->onLeftClickReleasedOutside();
						}
					}
					else if (event.mouseButton.button == sf::Mouse::Right)
					{
						if (event.type == sf::Event::MouseButtonPressed)
						{
							if (rect.contains(event.mouseButton.x, event.mouseButton.y))
								itElem->onRightClickPressedInside();
							else
								itElem->onRightClickPressedOutside();
						}
						else if (event.type == sf::Event::MouseButtonReleased)
						{
							if (rect.contains(event.mouseButton.x, event.mouseButton.y))
								itElem->onRightClickReleasedInside();
							else
								itElem->onRightClickReleasedOutside();
						}
					}
					//TODO: Calling onEnter & onLeave
				}
			}
		}
	}
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
				itElem->show(this->_win);
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