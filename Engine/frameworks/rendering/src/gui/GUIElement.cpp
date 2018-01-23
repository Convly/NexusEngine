#include "GUIElement.hpp"
#include "Nexus/errors/ScriptNotLoadedException.hpp"

nx::gui::GUIElement::GUIElement(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, const nx::rendering::MouseEventsContainer& events) :
	_pos(pos), _size(size), _identifier(identifier), _isVisible(true), _events(events)
{	
	for (auto it : this->_events) {
		auto data = nx::Event::serializer<std::string>(it.second.file);
		enginePtr->emit(nx::EVENT::SCRIPT_LOAD, data);
		try {
			enginePtr->emit(nx::EVENT::SCRIPT_INIT, data);
		} catch (const nx::ScriptNotLoaded& e) {
			nx::Log::warning(e.what(), "BAD_FILE");
		}
	}
}

nx::gui::GUIElement::GUIElement(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier) :
	_pos(pos), _size(size), _identifier(identifier), _isVisible(true)
{

}

nx::gui::GUIElement::~GUIElement()
{

}

// Tools

void nx::gui::GUIElement::dispatchMouseEvent(sf::Vector2i const& pos, std::string const& eventName)
{
	std::for_each(
		this->_events.begin(),
		this->_events.end(),
		[&](auto& item) {
			if (item.first == eventName) {
				auto const ptr = reinterpret_cast<char*>(&item.second);
				enginePtr->emit(nx::EVENT::SCRIPT_EXEC_FUNCTION, std::vector<char>(ptr, ptr + sizeof item.second));
			}
		}
	);
}

// Mouse events

void	nx::gui::GUIElement::onMoveInside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onMoveInside");
}

void	nx::gui::GUIElement::onMoveOutside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onMoveOutside");
}

void	nx::gui::GUIElement::onLeftClickPressedInside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onLeftClickPressedInside");
}

void	nx::gui::GUIElement::onLeftClickReleasedInside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onLeftClickReleasedInside");
}

void	nx::gui::GUIElement::onRightClickPressedInside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onRightClickPressedInside");
}

void	nx::gui::GUIElement::onRightClickReleasedInside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onRightClickReleasedInside");
}

void	nx::gui::GUIElement::onLeftClickPressedOutside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onLeftClickPressedOutside");
}

void	nx::gui::GUIElement::onLeftClickReleasedOutside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onLeftClickReleasedOutside");
}

void	nx::gui::GUIElement::onRightClickPressedOutside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onRightClickPressedOutside");	
}

void	nx::gui::GUIElement::onRightClickReleasedOutside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onRightClickReleasedOutside");
}

void	nx::gui::GUIElement::keyTextEntered(char const charEntered)
{
	this->dispatchMouseEvent({}, "keyTextEntered");
}

void	nx::gui::GUIElement::keyPressed(sf::Keyboard::Key const& keyPressed)
{
	this->dispatchMouseEvent({}, "keyPressed");
}


// Setters

void	nx::gui::GUIElement::setPos(sf::Vector2f const& pos)
{
	this->_pos = pos;
}

void	nx::gui::GUIElement::setSize(sf::Vector2f const& size)
{
	this->_size = size;
}

void	nx::gui::GUIElement::setVisible(bool const state)
{
	this->_isVisible = state;
}

// Getters

sf::Vector2f const &	nx::gui::GUIElement::getPos() const
{
	return (this->_pos);
}

sf::Vector2f const &	nx::gui::GUIElement::getSize() const
{
	return (this->_size);
}

std::string	const &		nx::gui::GUIElement::getIdentifier() const
{
	return (this->_identifier);
}

bool					nx::gui::GUIElement::isVisible() const
{
	return (this->_isVisible);
}

nx::rendering::MouseEventsContainer const& nx::gui::GUIElement::getEvents() const
{
	return this->_events;
}