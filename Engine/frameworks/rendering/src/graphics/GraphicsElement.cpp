#include "GraphicsElement.hpp"
#include "Nexus/errors/ScriptNotLoadedException.hpp"

nx::graphics::GraphicsElement::GraphicsElement(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, const nx::env::MouseEventsContainer& events) :
	_pos(pos), _size(size), _identifier(identifier), _isVisible(true), _events(events)
{	
	for (auto it : this->_events) {
		auto data = nx::Event::stringToVector(it.second.file);
		enginePtr->emit(nx::EVENT::SCRIPT_LOAD, data);
		try {
			enginePtr->emit(nx::EVENT::SCRIPT_INIT, data);
		} catch (const nx::ScriptNotLoaded& e) {
			nx::Log::warning(e.what(), "BAD_FILE");
		}
	}
}

nx::graphics::GraphicsElement::GraphicsElement(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier) :
	_pos(pos), _size(size), _identifier(identifier), _isVisible(true)
{

}

nx::graphics::GraphicsElement::~GraphicsElement()
{

}

// Tools

void nx::graphics::GraphicsElement::dispatchMouseEvent(sf::Vector2i const& pos, std::string const& eventName)
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

void	nx::graphics::GraphicsElement::onMoveInside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onMoveInside");
}

void	nx::graphics::GraphicsElement::onMoveOutside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onMoveOutside");
}

void	nx::graphics::GraphicsElement::onLeftClickPressedInside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onLeftClickPressedInside");
}

void	nx::graphics::GraphicsElement::onLeftClickReleasedInside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onLeftClickReleasedInside");
}

void	nx::graphics::GraphicsElement::onRightClickPressedInside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onRightClickPressedInside");
}

void	nx::graphics::GraphicsElement::onRightClickReleasedInside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onRightClickReleasedInside");
}

void	nx::graphics::GraphicsElement::onLeftClickPressedOutside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onLeftClickPressedOutside");
}

void	nx::graphics::GraphicsElement::onLeftClickReleasedOutside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onLeftClickReleasedOutside");
}

void	nx::graphics::GraphicsElement::onRightClickPressedOutside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onRightClickPressedOutside");	
}

void	nx::graphics::GraphicsElement::onRightClickReleasedOutside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onRightClickReleasedOutside");
}

void	nx::graphics::GraphicsElement::keyTextEntered(char const charEntered)
{
	this->dispatchMouseEvent({}, "keyTextEntered");
}

void	nx::graphics::GraphicsElement::keyPressed(sf::Keyboard::Key const& keyPressed)
{
	this->dispatchMouseEvent({}, "keyPressed");
}


// Setters

void	nx::graphics::GraphicsElement::setPos(sf::Vector2f const& pos)
{
	this->_pos = pos;
}

void	nx::graphics::GraphicsElement::setSize(sf::Vector2f const& size)
{
	this->_size = size;
}

void	nx::graphics::GraphicsElement::setVisible(bool const state)
{
	this->_isVisible = state;
}

// Getters

sf::Vector2f const &	nx::graphics::GraphicsElement::getPos() const
{
	return (this->_pos);
}

sf::Vector2f const &	nx::graphics::GraphicsElement::getSize() const
{
	return (this->_size);
}

std::string	const &		nx::graphics::GraphicsElement::getIdentifier() const
{
	return (this->_identifier);
}

bool					nx::graphics::GraphicsElement::isVisible() const
{
	return (this->_isVisible);
}

nx::env::MouseEventsContainer const& nx::graphics::GraphicsElement::getEvents() const
{
	return this->_events;
}