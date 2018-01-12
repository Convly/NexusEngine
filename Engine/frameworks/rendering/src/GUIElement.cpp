#include "GUIElement.hpp"
#include "Nexus/errors/ScriptNotLoadedException.hpp"

GUIElement::GUIElement(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, const nx::rendering::MouseEventsContainer& events) :
	_pos(pos), _size(size), _identifier(identifier), _isVisible(true), _events(events)
{	
	for (auto it : this->_events) {
		auto data = nx::Event::stringToVector(it.second.file);
		nx::Engine::Instance().emit(nx::EVENT::SCRIPT_LOAD, data);
		try {
			nx::Engine::Instance().emit(nx::EVENT::SCRIPT_INIT, data);
		} catch (const nx::ScriptNotLoaded& e) {
			nx::Log::warning(e.what(), "BAD_FILE");
		}
	}
}

GUIElement::GUIElement(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier) :
	_pos(pos), _size(size), _identifier(identifier), _isVisible(true)
{

}

GUIElement::~GUIElement()
{

}

// Tools

void GUIElement::dispatchMouseEvent(sf::Vector2i const& pos, std::string const& eventName)
{
	std::for_each(
		this->_events.begin(),
		this->_events.end(),
		[&](auto& item) {
			if (item.first == eventName) {
				auto const ptr = reinterpret_cast<char*>(&item.second);
				nx::Engine::Instance().emit(nx::EVENT::SCRIPT_EXEC_FUNCTION, std::vector<char>(ptr, ptr + sizeof item.second));
			}
		}
	);
}

// Mouse events

void	GUIElement::onMoveInside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onMoveInside");
}

void	GUIElement::onMoveOutside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onMoveOutside");
}

void	GUIElement::onLeftClickPressedInside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onLeftClickPressedInside");
}

void	GUIElement::onLeftClickReleasedInside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onLeftClickReleasedInside");
}

void	GUIElement::onRightClickPressedInside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onRightClickPressedInside");
}

void	GUIElement::onRightClickReleasedInside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onRightClickReleasedInside");
}

void	GUIElement::onLeftClickPressedOutside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onLeftClickPressedOutside");
}

void	GUIElement::onLeftClickReleasedOutside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onLeftClickReleasedOutside");
}

void	GUIElement::onRightClickPressedOutside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onRightClickPressedOutside");	
}

void	GUIElement::onRightClickReleasedOutside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onRightClickReleasedOutside");
}

void	GUIElement::keyTextEntered(char const charEntered)
{
	this->dispatchMouseEvent(pos, "keyTextEntered");
}

void	GUIElement::keyPressed(sf::Keyboard::Key const& keyPressed)
{
	this->dispatchMouseEvent(pos, "keyPressed");
}


// Setters

void	GUIElement::setPos(sf::Vector2f const& pos)
{
	this->_pos = pos;
}

void	GUIElement::setSize(sf::Vector2f const& size)
{
	this->_size = size;
}

void	GUIElement::setVisible(bool const state)
{
	this->_isVisible = state;
}

// Getters

sf::Vector2f const &	GUIElement::getPos() const
{
	return (this->_pos);
}

sf::Vector2f const &	GUIElement::getSize() const
{
	return (this->_size);
}

std::string	const &		GUIElement::getIdentifier() const
{
	return (this->_identifier);
}

bool					GUIElement::isVisible() const
{
	return (this->_isVisible);
}

nx::rendering::MouseEventsContainer const& GUIElement::getEvents() const
{
	return this->_events;
}