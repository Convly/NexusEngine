//
// Made by Marco
//

# include "Music.hpp"

nx::sfx::Music::~Music()
{
	this->stop();
}

nx::sfx::Music::Music(const std::string & name)
{
	if (name.empty())
		throw MusicException("Music : Initialization : empty Name.");
	this->_name = name;
	if (!this->_music.openFromFile(name))
		throw MusicException("Music : Initialization : can't load file " + name + ".");
}

nx::sfx::Music::Music(const Music & other)
{
	if (other.getName().empty())
		throw MusicException("Music : Initialization : empty Name.");
	this->_name = other.getName();
	if (!this->_music.openFromFile(this->_name))
		throw MusicException("Music : Initialization : can't load file " + other.getName() + ".");
}



void	nx::sfx::Music::play()
{
	this->_music.play();
}

void 	nx::sfx::Music::pause()
{
	this->_music.pause();
}

void 	nx::sfx::Music::stop()
{
	this->_music.stop();
}

// Setters

void 	nx::sfx::Music::setLoop(const bool loop)
{
	this->_music.setLoop(loop);
}

void 	nx::sfx::Music::setPitch(const float pitch)
{
	this->_music.setPitch(pitch);
}

void 	nx::sfx::Music::setVolume(const float volume)
{
	this->_music.setVolume(volume);
}

void 	nx::sfx::Music::setAttenuation(const float attenuation)
{
	this->_music.setAttenuation(attenuation);
}

// Getters

const std::string &	nx::sfx::Music::getName() const
{
	return (this->_name);
}

const bool 			nx::sfx::Music::getLoop() const
{
	return (this->_music.getLoop());
}

const nx::sfx::SFX_STATUS	nx::sfx::Music::getStatus() const
{
	auto status = this->_music.getStatus();

	if (status == sf::SoundSource::Status::Stopped)
		return (SFX_STATUS::STOP);
	else if (status == sf::SoundSource::Status::Paused)
		return (SFX_STATUS::PAUSE);
	else if (status == sf::SoundSource::Status::Playing)
		return (SFX_STATUS::PLAY);
	else
		return (SFX_STATUS::UNKNOWN);
}

const float 				nx::sfx::Music::getVolume() const
{
	return (this->_music.getVolume());
}

const float					nx::sfx::Music::getPitch() const
{
	return (this->_music.getPitch());
}

const float 				nx::sfx::Music::getAttenuation() const
{
	return (this->_music.getAttenuation());
}

const unsigned int 			nx::sfx::Music::getChannelCount() const
{
	return (this->_music.getChannelCount());
}

const unsigned int 			nx::sfx::Music::getSampleRate() const
{
	return (this->_music.getSampleRate());
}

nx::sfx::Music &			nx::sfx::Music::operator=(const nx::sfx::Music & other)
{
	if (this != &other)
	{
		if (other.getName().empty())
			throw MusicException("Music : Copy constructor : can't load file " + other.getName() + ".");
		this->_name = other.getName();
		if (!this->_music.openFromFile(other.getName()))
			throw MusicException("Music : Copy constructor : can't load file " + other.getName() + ".");

		this->_music.setLoop(other.getLoop());
		this->_music.setPitch(other.getPitch());
		this->_music.setVolume(other.getVolume());
		this->_music.setAttenuation(other.getAttenuation());
	}
	return (*this);
}
