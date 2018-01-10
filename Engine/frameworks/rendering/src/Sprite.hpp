#ifndef SPRITE_HPP_
# define SPRITE_HPP_

# include <string>
# include "Nexus/log.hpp"
# include "GUIElement.hpp"
# include "InvalidImageException.hpp"

class Sprite : public GUIElement
{
	std::string		_spritesheetPath;
	sf::Vector2f	_sheetGrid;
	sf::Vector2f	_spriteSize;

	sf::Texture		_texture;
	sf::Sprite		_sprite;

	sf::Vector2f	_originalSize;

	uint16_t		_spriteIdx;
	uint16_t		_slowness;
	uint16_t		_slownessLap;

	bool			_isAnimated;


	void _loadSpritesheet();
	void _refreshSprite();
	void _rescaleSprite();

public:
	Sprite(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, std::string const& spritesheetPath,
		   sf::Vector2f const& sheetGrid, sf::Vector2f const& spriteSize, uint16_t const spriteIdx, uint16_t const slowness);
	~Sprite();

	// GUIElement's mouse event methods overload
	virtual void onMoveInside(sf::Vector2i const& pos);
	virtual void onMoveOutside(sf::Vector2i const& pos);
	virtual void onLeftClickPressedInside(sf::Vector2i const& pos);
	virtual void onLeftClickReleasedInside(sf::Vector2i const& pos);
	virtual void onRightClickPressedInside(sf::Vector2i const& pos);
	virtual void onRightClickReleasedInside(sf::Vector2i const& pos);
	virtual void onLeftClickPressedOutside(sf::Vector2i const& pos);
	virtual void onLeftClickReleasedOutside(sf::Vector2i const& pos);
	virtual void onRightClickPressedOutside(sf::Vector2i const& pos);
	virtual void onRightClickReleasedOutside(sf::Vector2i const& pos);
	virtual void keyTextEntered(char const charEntered);
	virtual void keyPressed(sf::Keyboard::Key const& keyPressed);

	// Display
	void	show(std::shared_ptr<sf::RenderWindow> const& win);

	// Setters
	void	setSpritesheetPath(std::string const& spritesheetPath);
	void	setAnimate(bool const animate);

	void	setPos(sf::Vector2f const& pos);
	void	setSize(sf::Vector2f const& size);

	// Getters
	virtual std::string const	getType() const;

	// Specific getters
	std::string const &		getSpritesheetPath() const;
	bool const				getAnimate() const;
};

#endif /* SPRITE_HPP_ */