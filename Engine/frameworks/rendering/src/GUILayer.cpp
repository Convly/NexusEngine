#include "GUILayer.hpp"

GUILayer::GUILayer(std::string const & identifier) :
	_identifier(identifier), _isVisible(true)
{

}

GUILayer::~GUILayer()
{

}

void GUILayer::add(std::shared_ptr<GUIElement> elem)
{
	this->_guiElements.push_back(elem);
}


// Setters

void										GUILayer::setVisible(bool const state)
{
	this->_isVisible = state;
}


// Getters

std::string const &							GUILayer::getIdentifier() const
{
	return (this->_identifier);
}

bool	GUILayer::isVisible() const
{
	return (this->_isVisible);
}

std::vector<std::shared_ptr<GUIElement>> const & GUILayer::getElements() const
{
	return (this->_guiElements);
}


std::shared_ptr<GUIElement> const &	GUILayer::getElementByName(std::string const& identifier) const
{
	for (auto &it : this->_guiElements)
	{
		if (it->getIdentifier() == identifier)
			return (it);
	}
	throw (nx::ElementNotFoundException(identifier));
}