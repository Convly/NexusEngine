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
	Image(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, nx::rendering::MouseEventsContainer const& events,
		  std::string const& imgPath);
	~Image();

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