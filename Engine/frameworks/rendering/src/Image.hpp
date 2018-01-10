#ifndef IMAGE_HPP_
# define IMAGE_HPP_

# include <string>
# include "Nexus/log.hpp"
# include "GUIElement.hpp"
# include "InvalidImageException.hpp"

class Image : public GUIElement
{
	std::string		_imgPath;

	sf::Texture		_texture;
	sf::Sprite		_img;

	sf::Vector2f	_originalSize;

	void _loadImage();
	void _rescaleImage();

public:
	Image(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, std::string const& imgPath);
	~Image();

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
	void	setImagePath(std::string const& spritePath);

	void	setPos(sf::Vector2f const& pos);
	void	setSize(sf::Vector2f const& size);

	// Getters
	virtual std::string const	getType() const;

	// Specific getters
	std::string const &		getImagePath() const;
};

#endif /* IMAGE_HPP_ */