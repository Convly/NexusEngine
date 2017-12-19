#include "GUIHandler.hpp"

GUIHandler::GUIHandler()
{

}
GUIHandler::~GUIHandler()
{

}

void	GUIHandler::addGUIElement(std::shared_ptr<GUIElement> elem)
{
	this->_guiElements.push_back(elem);
}


// Display

void GUIHandler::drawGUIElements()
{
	// TODO: Draw GUI Elements contained in the _guiElements vector
}


// Getters

std::vector<std::shared_ptr<GUIElement>>	GUIHandler::getGUIElements() const
{
	return (this->_guiElements);
}