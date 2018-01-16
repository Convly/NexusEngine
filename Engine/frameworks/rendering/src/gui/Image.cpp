#include "Image.hpp"

nx::gui::Image::Image(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, nx::rendering::MouseEventsContainer const& events,
			 std::string const& imgPath) :
	GUIElement(pos, size, identifier, events), _imgPath(imgPath)
{
	this->_loadImage();
	this->_rescaleImage();
}

nx::gui::Image::~Image()
{

}

void nx::gui::Image::_loadImage()
{
	if (!this->_texture.loadFromFile(this->_imgPath))
		throw nx::InvalidImageException(this->_imgPath);
	this->_img.setTexture(this->_texture);
	this->_img.setPosition(this->getPos());
	this->_originalSize = sf::Vector2f(this->_img.getLocalBounds().width, this->_img.getLocalBounds().height);
}

void nx::gui::Image::_rescaleImage()
{
	if (this->getSize().x != 0 && this->getSize().y != 0)
		this->_img.setScale(this->getSize().x / this->_originalSize.x, this->getSize().y / this->_originalSize.y);
}


// Display

void nx::gui::Image::show(std::shared_ptr<sf::RenderWindow> const& win)
{
	if (this->isVisible())
		win->draw(this->_img);
}


// Setters

void	nx::gui::Image::setImagePath(std::string const& imagePath)
{
	this->_imgPath = imagePath;
	this->_loadImage();
	this->_rescaleImage();
}

void	nx::gui::Image::setPos(sf::Vector2f const& pos)
{
	GUIElement::setPos(pos);
	this->_img.setPosition(pos);
}

void	nx::gui::Image::setSize(sf::Vector2f const& size)
{
	GUIElement::setSize(size);
	this->_rescaleImage();
	GUIElement::setSize(sf::Vector2f(this->_img.getLocalBounds().width,
									 this->_img.getLocalBounds().height));
}

// Getters

std::string	const	nx::gui::Image::getType() const
{
	return ("Image");
}


// Specific getters

std::string const & nx::gui::Image::getImagePath() const
{
	return (this->_imgPath);
}