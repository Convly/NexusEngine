#include "Sprite.hpp"

Sprite::Sprite(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, std::string const& spritesheetPath,
			   sf::Vector2f const& sheetGrid, sf::Vector2f const& spriteSize, uint16_t const spriteIdx, uint16_t const slowness) :
	GUIElement(pos, spriteSize, identifier), _spritesheetPath(spritesheetPath), _sheetGrid(sheetGrid), _spriteSize(spriteSize),
	_originalSize(spriteSize), _spriteIdx(spriteIdx), _slowness(slowness), _slownessLap(slowness), _isAnimated(false)
{
	this->_loadSpritesheet();
	this->_rescaleSprite();
}

Sprite::~Sprite()
{

}

void Sprite::_loadSpritesheet()
{
	if (!this->_texture.loadFromFile(this->_spritesheetPath))
		throw nx::InvalidImageException(this->_spritesheetPath);
	this->_sprite.setTexture(this->_texture);
	this->_sprite.setPosition(this->getPos());
	this->_refreshSprite();
	this->_originalSize = this->_spriteSize;
}

void Sprite::_refreshSprite()
{
	if (this->_spriteIdx == 0)
		this->_sprite.setTextureRect(sf::IntRect(0, 0, this->_spriteSize.x, this->_spriteSize.y));
	else
	{
		this->_sprite.setTextureRect(sf::IntRect(this->_spriteSize.x * (this->_spriteIdx % static_cast<int>(this->_sheetGrid.x)),
												 this->_spriteSize.y * (this->_spriteIdx / static_cast<int>(this->_sheetGrid.x)),
												 this->_spriteSize.x, this->_spriteSize.y));
	}
}

void Sprite::_rescaleSprite()
{
	if (this->getSize().x != 0 && this->getSize().y != 0)
		this->_sprite.setScale(this->getSize().x / this->_originalSize.x, this->getSize().y / this->_originalSize.y);
}

// GUIElement's mouse event methods overload

void Sprite::onMoveInside(sf::Vector2i const& pos)
{
	//Will be called when mouse is moving into the element
	//nx::Log::inform("Mouse moving inside the Sprite '" + this->getIdentifier() + "'");
}

void Sprite::onMoveOutside(sf::Vector2i const& pos)
{
	//Will be called when mouse is moving outside the element
	//nx::Log::inform("Mouse moving outside the Sprite '" + this->getIdentifier() + "'");
}

void Sprite::onLeftClickPressedInside(sf::Vector2i const& pos)
{
	//Will be called when the element has been left-clicked
	//nx::Log::inform("Left-click pressed inside the Sprite '" + this->getIdentifier() + "'");
}

void Sprite::onLeftClickReleasedInside(sf::Vector2i const& pos)
{
	//Will be called when the element has been left-released
	//nx::Log::inform("Left-click released inside the Sprite '" + this->getIdentifier() + "'");
}

void Sprite::onRightClickPressedInside(sf::Vector2i const& pos)
{
	//Will be called when the element has been right-clicked
	//nx::Log::inform("Right-click pressed inside the Sprite '" + this->getIdentifier() + "'");
}

void Sprite::onRightClickReleasedInside(sf::Vector2i const& pos)
{
	//Will be called when the element has been right-released
	//nx::Log::inform("Right-click released inside the Sprite '" + this->getIdentifier() + "'");
}

void Sprite::onLeftClickPressedOutside(sf::Vector2i const& pos)
{
	//Will be called when a left-click is outside the element
	//nx::Log::inform("Left-click pressed outside the Sprite '" + this->getIdentifier() + "'");
}

void Sprite::onLeftClickReleasedOutside(sf::Vector2i const& pos)
{
	//Will be called when a left-release is outside the element
	//nx::Log::inform("Left-click released outside the Sprite '" + this->getIdentifier() + "'");
}

void Sprite::onRightClickPressedOutside(sf::Vector2i const& pos)
{
	//Will be called when a right-click is outside the element
	//nx::Log::inform("Right-click pressed outside the Sprite '" + this->getIdentifier() + "'");
}

void Sprite::onRightClickReleasedOutside(sf::Vector2i const& pos)
{
	//Will be called when a right-release is outside the element
	//nx::Log::inform("Right-click released outside the Sprite '" + this->getIdentifier() + "'");
}

void Sprite::keyTextEntered(char const charEntered)
{
	//Will be called when Sprite in entered
	//nx::Log::inform("Char pressed for the Sprite '" + this->getIdentifier() + "' is " + charEntered);
}

void Sprite::keyPressed(sf::Keyboard::Key const& keyPressed)
{
	//Will be called when a key is pressed
	//nx::Log::inform("Key pressed for the Sprite '" + this->getIdentifier());
}

// Display

void Sprite::show(std::shared_ptr<sf::RenderWindow> const& win)
{
	if (this->isVisible())
	{
		win->draw(this->_sprite);
		if (this->_isAnimated)
		{
			if (this->_slownessLap == 0)
			{
				this->_spriteIdx = ((this->_spriteIdx + 1 >= this->_sheetGrid.x * this->_sheetGrid.y) ? (0) : (this->_spriteIdx + 1));
				this->_refreshSprite();
				this->_slownessLap = this->_slowness;
			}
			this->_slownessLap -= 1;
		}
	}
}


// Setters

void	Sprite::setSpritesheetPath(std::string const& spritePath)
{
	this->_spritesheetPath = spritePath;
	this->_loadSpritesheet();
	this->_rescaleSprite();
}

void	Sprite::setAnimate(bool const isAnimated)
{
	if (this->_isAnimated != isAnimated)
	{
		this->_slownessLap = this->_slowness;
		this->_isAnimated = isAnimated;
	}
}

void	Sprite::setPos(sf::Vector2f const& pos)
{
	GUIElement::setPos(pos);
}

void	Sprite::setSize(sf::Vector2f const& size)
{
	GUIElement::setSize(size);
	this->_rescaleSprite();
	GUIElement::setSize(sf::Vector2f(this->_sprite.getLocalBounds().width,
									 this->_sprite.getLocalBounds().height));
}

// Getters

std::string	const	Sprite::getType() const
{
	return ("Sprite");
}


// Specific getters

std::string const & Sprite::getSpritesheetPath() const
{
	return (this->_spritesheetPath);
}

bool const			Sprite::getAnimate() const
{
	return (this->_isAnimated);
}