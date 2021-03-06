#include "Sprite.hpp"

extern GraphicResources resources;

nx::gui::Sprite::Sprite(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, nx::env::MouseEventsContainer const& events,
			   std::string const& spritesheetPath, sf::Vector2f const& sheetGrid, sf::Vector2f const& spriteSize) :
	GUIElement(pos, spriteSize, identifier), _spritesheetPath(spritesheetPath), _sheetGrid(sheetGrid), _spriteSize(spriteSize),
	_originalSize(spriteSize), _spriteIdx(0), _slowness(40), _isAnimated(false), _animationIdx(0)
{
	this->_spritesAnimated.clear();
	for (int i = 0; i < sheetGrid.x * sheetGrid.y; ++i)
		this->_spritesAnimated.push_back(i);
	this->_loadSpritesheet();
	this->_rescaleSprite();

	this->_time = this->_clock.restart();
}

nx::gui::Sprite::~Sprite()
{

}

void nx::gui::Sprite::_loadSpritesheet()
{
	std::string realPath(enginePtr->getEnv().getGameInfos().getRootPath() + enginePtr->getGameInfosParser()->getFields()._resources.at("images") + this->_spritesheetPath);

	if (resources.textures.find(realPath) == resources.textures.end())
	{
		resources.textures[realPath] = sf::Texture();
		if (!resources.textures[realPath].loadFromFile(realPath))
			throw nx::InvalidImageException(realPath);
	}
	this->_sprite.setTexture(resources.textures[realPath]);
	this->_sprite.setPosition(this->getPos());
	this->_originalSize = this->_spriteSize;
	this->_refreshSprite();
}

void nx::gui::Sprite::_refreshSprite()
{
	if (this->_spriteIdx == 0)
		this->_sprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(this->_spriteSize.x), static_cast<int>(this->_spriteSize.y)));
	else
	{
		this->_sprite.setTextureRect(sf::IntRect(static_cast<int>(this->_spriteSize.x * (this->_spriteIdx % static_cast<int>(this->_sheetGrid.x))),
												 static_cast<int>(this->_spriteSize.y * (this->_spriteIdx / static_cast<int>(this->_sheetGrid.x))),
												 static_cast<int>(this->_spriteSize.x), static_cast<int>(this->_spriteSize.y)));
	}
}

void nx::gui::Sprite::_rescaleSprite()
{
	if (this->getSize().x != 0 && this->getSize().y != 0)
		this->_sprite.setScale(this->getSize().x / this->_originalSize.x, this->getSize().y / this->_originalSize.y);
	GUIElement::setSize(sf::Vector2f(this->_sprite.getLocalBounds().width, this->_sprite.getLocalBounds().height));
}


// Display

void nx::gui::Sprite::show(std::shared_ptr<sf::RenderWindow> const& win)
{
	if (this->isVisible())
	{
		win->draw(this->_sprite);
		if (this->_isAnimated)
		{
			this->_time = this->_clock.getElapsedTime();
			if (this->_time.asMilliseconds() >= this->_slowness)
			{
				this->_animationIdx += 1;
				if (this->_animationIdx >= this->_spritesAnimated.size())
					this->_animationIdx = 0;
				this->_spriteIdx = this->_spritesAnimated[this->_animationIdx];
				this->_refreshSprite();
				this->_time = this->_clock.restart();
			}
		}
	}
}


// Setters

void	nx::gui::Sprite::setSpritesheetPath(std::string const& spritePath)
{
	this->_spritesheetPath = spritePath;
	this->_loadSpritesheet();
	this->_rescaleSprite();
}

void	nx::gui::Sprite::setAnimate(bool const isAnimated)
{
	if (this->_isAnimated != isAnimated)
	{
		this->_isAnimated = isAnimated;
		if (std::find(this->_spritesAnimated.begin(), this->_spritesAnimated.end(), this->_spriteIdx) == this->_spritesAnimated.end() &&
			this->_isAnimated)
		{
			nx::Log::warning("The sprite index is out of the sprites animated list, now set at the first sprites animated list value", "OUT_OF_RANGE");
			this->_spriteIdx = this->_spritesAnimated[0];
		}
		this->_time = this->_clock.restart();
	}
}

void	nx::gui::Sprite::setSpriteIdx(uint16_t const spriteIdx)
{
	if (spriteIdx >= this->_sheetGrid.x * this->_sheetGrid.y)
	{
		nx::Log::warning("The sprite index is out of the grid assignated, now set at 0..", "OUT_OF_RANGE");
		this->_spriteIdx = 0;
	}
	else
		this->_spriteIdx = spriteIdx;
}

void	nx::gui::Sprite::setSlowness(uint16_t const slowness)
{
	this->_slowness = slowness;
	this->_time = this->_clock.restart();
}

void	nx::gui::Sprite::setSpritesAnimated(std::vector<uint16_t> const& spritesAnimated)
{
	if (spritesAnimated.empty())
	{
		nx::Log::warning("The animated sprite vector given was empty, ignoring..", "EMPTY_VECTOR");
		return;
	}
	else if (std::find(spritesAnimated.begin(), spritesAnimated.end(), this->_spritesAnimated[this->_spriteIdx]) == spritesAnimated.end())
	{
		this->_spriteIdx = 0;
		this->_refreshSprite();
	}
	this->_spritesAnimated = spritesAnimated;
	this->_spritesAnimated.erase(std::remove_if(this->_spritesAnimated.begin(), this->_spritesAnimated.end(),
								 [&](uint16_t const spriteIdx) {
									if (spriteIdx >= this->_sheetGrid.x * this->_sheetGrid.y)
										nx::Log::warning("A sprite index is out of the grid assignated, removing it..", "OUT_OF_RANGE");
									return (spriteIdx >= this->_sheetGrid.x * this->_sheetGrid.y);
								 }),
								 this->_spritesAnimated.end());
}


void	nx::gui::Sprite::setAnimationIdx(uint16_t const animationIdx)
{
	if (animationIdx >= this->_spritesAnimated.size())
	{
		nx::Log::warning("The animation index is out of the sprites animated list, now set at 0..", "OUT_OF_RANGE");
		this->_animationIdx = 0;
	}
	else
		this->_animationIdx = animationIdx;
}

void	nx::gui::Sprite::setPos(sf::Vector2f const& pos)
{
	GUIElement::setPos(pos);
	this->_sprite.setPosition(pos);
}

void	nx::gui::Sprite::setSize(sf::Vector2f const& size)
{
	GUIElement::setSize(size);
	this->_rescaleSprite();
	GUIElement::setSize(sf::Vector2f(this->_sprite.getLocalBounds().width, this->_sprite.getLocalBounds().height));
}

// Getters

std::string	const	nx::gui::Sprite::getType() const
{
	return ("Sprite");
}


// Specific getters

std::string const &				nx::gui::Sprite::getSpritesheetPath() const
{
	return (this->_spritesheetPath);
}

uint16_t const					nx::gui::Sprite::getSpriteIdx() const
{
	return (this->_spriteIdx);
}

uint16_t const					nx::gui::Sprite::getSlowness() const
{
	return (this->_slowness);
}

bool const						nx::gui::Sprite::getAnimate() const
{
	return (this->_isAnimated);
}

std::vector<uint16_t> const &	nx::gui::Sprite::getSpritesAnimated() const
{
	return (this->_spritesAnimated);
}

uint16_t const					nx::gui::Sprite::getAnimationIdx() const
{
	return (this->_animationIdx);
}
