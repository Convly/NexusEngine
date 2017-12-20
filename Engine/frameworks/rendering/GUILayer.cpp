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


// Display

void GUILayer::draw()
{
	for (auto it : this->_guiElements)
	{
		if (it->isVisible())
			it->show();
	}
}


// Setters

void										GUILayer::setVisible(bool const state)
{
	this->_isVisible = state;
}


// Getters

bool	GUILayer::isVisible() const
{
	return (this->_isVisible);
}

std::vector<std::shared_ptr<GUIElement>> GUILayer::getElements() const
{
	return (std::vector<std::shared_ptr<GUIElement>>());
}
