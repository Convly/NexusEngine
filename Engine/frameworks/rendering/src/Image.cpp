#include "Image.hpp"

Image::Image(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, std::string const& imgPath) :
	GUIElement(pos, size, identifier), _imgPath(imgPath)
{
	this->_loadImage();
	this->_rescaleImage();
}

Image::~Image()
{

}

void Image::_loadImage()
{
	if (!this->_texture.loadFromFile(this->_imgPath))
		throw nx::InvalidImageException(this->_imgPath);
	this->_img.setTexture(this->_texture);
	this->_img.setPosition(this->getPos());
	this->_originalSize = sf::Vector2f(this->_img.getLocalBounds().width, this->_img.getLocalBounds().height);
}

void Image::_rescaleImage()
{
	if (this->getSize().x != 0 && this->getSize().y != 0)
		this->_img.setScale(this->getSize().x / this->_originalSize.x, this->getSize().y / this->_originalSize.y);
}


// Display

void Image::show(std::shared_ptr<sf::RenderWindow> const& win)
{
	if (this->isVisible())
		win->draw(this->_img);
}


// Setters

void	Image::setImagePath(std::string const& imagePath)
{
	this->_imgPath = imagePath;
	this->_loadImage();
	this->_rescaleImage();
}

void	Image::setPos(sf::Vector2f const& pos)
{
	GUIElement::setPos(pos);
	this->_img.setPosition(pos);
}

void	Image::setSize(sf::Vector2f const& size)
{
	GUIElement::setSize(size);
	this->_rescaleImage();
	GUIElement::setSize(sf::Vector2f(this->_img.getLocalBounds().width,
									 this->_img.getLocalBounds().height));
}

// Getters

std::string	const	Image::getType() const
{
	return ("Image");
}


// Specific getters

std::string const & Image::getImagePath() const
{
	return (this->_imgPath);
}