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

// GUIElement's mouse event methods overload

void Image::onMoveInside(sf::Vector2i const& pos)
{
	//Will be called when mouse is moving into the element
	//nx::Log::inform("Mouse moving inside the Image '" + this->getIdentifier() + "'");
}

void Image::onMoveOutside(sf::Vector2i const& pos)
{
	//Will be called when mouse is moving outside the element
	//nx::Log::inform("Mouse moving outside the Image '" + this->getIdentifier() + "'");
}

void Image::onLeftClickPressedInside(sf::Vector2i const& pos)
{
	//Will be called when the element has been left-clicked
	//nx::Log::inform("Left-click pressed inside the Image '" + this->getIdentifier() + "'");
}

void Image::onLeftClickReleasedInside(sf::Vector2i const& pos)
{
	//Will be called when the element has been left-released
	//nx::Log::inform("Left-click released inside the Image '" + this->getIdentifier() + "'");
}

void Image::onRightClickPressedInside(sf::Vector2i const& pos)
{
	//Will be called when the element has been right-clicked
	//nx::Log::inform("Right-click pressed inside the Image '" + this->getIdentifier() + "'");
}

void Image::onRightClickReleasedInside(sf::Vector2i const& pos)
{
	//Will be called when the element has been right-released
	//nx::Log::inform("Right-click released inside the Image '" + this->getIdentifier() + "'");
}

void Image::onLeftClickPressedOutside(sf::Vector2i const& pos)
{
	//Will be called when a left-click is outside the element
	//nx::Log::inform("Left-click pressed outside the Image '" + this->getIdentifier() + "'");
}

void Image::onLeftClickReleasedOutside(sf::Vector2i const& pos)
{
	//Will be called when a left-release is outside the element
	//nx::Log::inform("Left-click released outside the Image '" + this->getIdentifier() + "'");
}

void Image::onRightClickPressedOutside(sf::Vector2i const& pos)
{
	//Will be called when a right-click is outside the element
	//nx::Log::inform("Right-click pressed outside the Image '" + this->getIdentifier() + "'");
}

void Image::onRightClickReleasedOutside(sf::Vector2i const& pos)
{
	//Will be called when a right-release is outside the element
	//nx::Log::inform("Right-click released outside the Image '" + this->getIdentifier() + "'");
}

void Image::keyTextEntered(char const charEntered)
{
	//Will be called when Image in entered
	//nx::Log::inform("Char pressed for the Image '" + this->getIdentifier() + "' is " + charEntered);
}

void Image::keyPressed(sf::Keyboard::Key const& keyPressed)
{
	//Will be called when a key is pressed
	//nx::Log::inform("Key pressed for the Image '" + this->getIdentifier());
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