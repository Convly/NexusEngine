#include "GUILayer.hpp"

nx::gui::GUILayer::GUILayer(std::string const & identifier) :
	_identifier(identifier), _isVisible(true)
{

}

nx::gui::GUILayer::~GUILayer()
{

}

void nx::gui::GUILayer::add(std::shared_ptr<GUIElement> elem)
{
	this->_guiElements.push_back(elem);
}


bool	nx::gui::GUILayer::remove(std::string const& elemId)
{
	bool found = false;
	this->_guiElements.erase(std::remove_if(this->_guiElements.begin(), this->_guiElements.end(),
		[&](std::shared_ptr<nx::gui::GUIElement> elem)
	{
		if (elem->getIdentifier() == elemId)
			found = true;
		return (elem->getIdentifier() == elemId);
	}), this->_guiElements.end());
	return (found);
}

// Setters

void										nx::gui::GUILayer::setVisible(bool const state)
{
	this->_isVisible = state;
}


// Getters

std::string const &							nx::gui::GUILayer::getIdentifier() const
{
	return (this->_identifier);
}

bool	nx::gui::GUILayer::isVisible() const
{
	return (this->_isVisible);
}

std::vector<std::shared_ptr<nx::gui::GUIElement>> const & nx::gui::GUILayer::getElements() const
{
	return (this->_guiElements);
}

std::vector<std::shared_ptr<nx::gui::GUIElement>>&		 nx::gui::GUILayer::getElements()
{
	return (this->_guiElements);
}


std::shared_ptr<nx::gui::GUIElement> const &	nx::gui::GUILayer::getElementByName(std::string const& identifier) const
{
	auto it = std::find_if(
		this->_guiElements.begin(),
		this->_guiElements.end(),
		[&](auto &element){
			return element->getIdentifier() == identifier;
		}
	);

	if (it == this->_guiElements.end()) {
		throw nx::ElementNotFoundException(identifier);
	}

	return *it;
}

std::shared_ptr<nx::gui::GUIElement>&		nx::gui::GUILayer::getElementByName(std::string const& identifier)
{
	auto it = std::find_if(
		this->_guiElements.begin(),
		this->_guiElements.end(),
		[&](auto &element){
			return element->getIdentifier() == identifier;
		}
	);

	if (it == this->_guiElements.end()) {
		throw nx::ElementNotFoundException(identifier);
	}

	return *it;
}

bool nx::gui::GUILayer::object_exists(const std::string& identifier) const
{
	auto it = std::find_if(
		this->_guiElements.begin(),
		this->_guiElements.end(),
		[&](auto &element){
			return element->getIdentifier() == identifier;
		}
	);

	return it != this->_guiElements.end();
}
