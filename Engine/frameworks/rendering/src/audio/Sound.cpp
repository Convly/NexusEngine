//
// Made by Marco
//


# include "Sound.hpp"

nx::sfx::Sound::Sound(const std::string & name)
{
	if (name.empty())
		throw SoundException("Sound : Initialization : name is empty.");
	this->_name = name;
	if (!this->_buffer.loadFromFile(name))
		throw SoundException("Sound : Initialization : can't load file " + name + " in buffer.");
	this->_sound.setBuffer(this->_buffer);
	if (this->_sound.getBuffer() == nullptr)
		throw SoundException("Sound : Initialization : can't load buffer.");
}

nx::sfx::Sound::Sound(const Sound & other)
{
	if (other.getName().empty())
		throw SoundException("Sound : Initialization : name is empty.");
	this->_name = other.getName();
	if (!this->_buffer.loadFromFile(this->_name))
		throw SoundException("Sound : Initialization : can't load file " + other.getName() + " in buffer.");
	this->_sound.setBuffer(this->_buffer);
	if (this->_sound.getBuffer() == nullptr)
		throw SoundException("Sound : Initialization : can't load buffer.");
}

nx::sfx::Sound::~Sound()
{
	this->stop();
}

void	nx::sfx::Sound::play()
{
	this->_sound.play();
}

void 	nx::sfx::Sound::pause()
{
	this->_sound.pause();
}

void 	nx::sfx::Sound::stop()
{
	this->_sound.stop();
}

// Setters

void 	nx::sfx::Sound::setLoop(bool loop)
{
	this->_sound.setLoop(loop);
}

void 	nx::sfx::Sound::setPitch(float pitch)
{
	this->_sound.setPitch(pitch);
}

void 	nx::sfx::Sound::setVolume(float volume)
{
	this->_sound.setVolume(volume);
}

void 	nx::sfx::Sound::setAttenuation(float attenuation)
{
	this->_sound.setAttenuation(attenuation);
}

// Getters

const std::string &	nx::sfx::Sound::getName() const
{
	return (this->_name);
}

const bool 			nx::sfx::Sound::getLoop() const
{
	return (this->_sound.getLoop());
}

const nx::sfx::SFX_STATUS	nx::sfx::Sound::getStatus() const
{
	auto status = this->_sound.getStatus();
	
	if (status == sf::SoundSource::Status::Stopped)
		return (SFX_STATUS::STOP);
	else if (status == sf::SoundSource::Status::Paused)
		return (SFX_STATUS::PAUSE);
	else if (status == sf::SoundSource::Status::Playing)
		return (SFX_STATUS::PLAY);
	else
		return (SFX_STATUS::UNKNOWN);
}

const float 				nx::sfx::Sound::getVolume() const
{
	return (this->_sound.getVolume());
}

const float					nx::sfx::Sound::getPitch() const
{
	return (this->_sound.getPitch());
}

const float 				nx::sfx::Sound::getAttenuation() const
{
	return (this->_sound.getAttenuation());
}

nx::sfx::Sound &			nx::sfx::Sound::operator=(const nx::sfx::Sound & other)
{
	if (this != &other)
	{
		if (other.getName().empty())
			throw SoundException("Sound : Copy constructor : name is empty.");
		this->_name = other.getName();
		this->_sound.resetBuffer();
		if (!this->_buffer.loadFromFile(this->_name))
			throw SoundException("Sound : Copy constructor : can't load file " + other.getName() + " in buffer.");
		this->_sound.setBuffer(this->_buffer);
		if (this->_sound.getBuffer() == nullptr)
			throw SoundException("Sound : Copy constructor : can't load buffer.");

		this->_sound.setLoop(other.getLoop());
		this->_sound.setPitch(other.getPitch());
		this->_sound.setVolume(other.getVolume());
		this->_sound.setAttenuation(other.getAttenuation());
	}
	return (*this);
}
