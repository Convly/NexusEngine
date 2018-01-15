#include "GUIHandler.hpp"
#include "Nexus/log.hpp"

nx::gui::GUIHandler::GUIHandler(std::shared_ptr<sf::RenderWindow> const& win):
	_win(win)
{

}
nx::gui::GUIHandler::~GUIHandler()
{

}

void	nx::gui::GUIHandler::addLayer(std::shared_ptr<GUILayer> layer)
{
	this->_guiLayers.push_back(layer);
}


// Events

void nx::gui::GUIHandler::processEvent(sf::Event const& event)
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
							if (rect.contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
								itElem->onLeftClickPressedInside(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
							else
								itElem->onLeftClickPressedOutside(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
						}
						else if (event.type == sf::Event::MouseButtonReleased)
						{
							if (rect.contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
								itElem->onLeftClickReleasedInside(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
							else
								itElem->onLeftClickReleasedOutside(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
						}
					}
					else if (event.mouseButton.button == sf::Mouse::Right)
					{
						if (event.type == sf::Event::MouseButtonPressed)
						{
							if (rect.contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
								itElem->onRightClickPressedInside(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
							else
								itElem->onRightClickPressedOutside(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
						}
						else if (event.type == sf::Event::MouseButtonReleased)
						{
							if (rect.contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
								itElem->onRightClickReleasedInside(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
							else
								itElem->onRightClickReleasedOutside(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
						}
					}
					if (event.type == sf::Event::MouseMoved)
					{
						if (rect.contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
							itElem->onMoveInside(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
						else
							itElem->onMoveOutside(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
					}
					if (event.type == sf::Event::TextEntered)
					{
						if (event.text.unicode < 128)
							itElem->keyTextEntered(static_cast<char>(event.text.unicode));
					}
					if (event.type == sf::Event::KeyPressed)
						itElem->keyPressed(event.key.code);
				}
			}
		}
	}
}


// Display

void nx::gui::GUIHandler::drawLayers()
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

std::vector<std::shared_ptr<nx::gui::GUILayer>>	const &	nx::gui::GUIHandler::getLayers() const
{
	return (this->_guiLayers);
}

std::vector<std::shared_ptr<nx::gui::GUILayer>>&	nx::gui::GUIHandler::getLayers()
{
	return this->_guiLayers;
}

std::shared_ptr<nx::gui::GUILayer> const &				nx::gui::GUIHandler::getLayerByName(std::string const& identifier) const
{
	for (auto &it : this->_guiLayers)
	{
		if (it->getIdentifier() == identifier)
			return (it);
	}
	throw (nx::LayerNotFoundException(identifier));
}

std::shared_ptr<nx::gui::GUILayer>&						nx::gui::GUIHandler::getLayerByName(std::string const& identifier)
{
	for (auto &it : this->_guiLayers)
	{
		if (it->getIdentifier() == identifier)
			return (it);
	}
	throw (nx::LayerNotFoundException(identifier));
}

const bool			nx::gui::GUIHandler::layer_exists(const std::string& identifier) const
{
	for (auto &it : this->_guiLayers)
	{
		if (it->getIdentifier() == identifier)
			return true;
	}

	return false;
}