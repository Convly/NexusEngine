//
// Made by Marco
//


# include "SfxHandler.hpp"

nx::sfx::SfxHandler::SfxHandler()
{
}

nx::sfx::SfxHandler::~SfxHandler()
{
}

bool	nx::sfx::SfxHandler::addSound(const std::string & name)
{
	Sound	sound(name);

	if (this->soundExist(name))
		return (false);
	
	if (this->_soundList.size() + this->_musicList.size() >= 256)
	{
		std::cerr << "Too much sf, can't load more" << std::endl;
		return (false);
	}
	
	try
	{
		this->_soundList[name] = sound;
	}
	catch (const SoundException & e)
	{
		throw SfxException(e.what() + std::string(" (") + name + std::string (")"));
	}
	return (true);
}

void	nx::sfx::SfxHandler::removeSound(const std::string & name)
{
	if (!this->soundExist(name))
		throw SfxException("Sfx : ressource " + name + " is not loaded.");
	this->_soundList.erase(name);
}

void	nx::sfx::SfxHandler::playSound(const std::string & name)
{
	if (!this->soundExist(name))
		throw SfxException("Sfx : ressource " + name + " is not loaded.");
	this->_soundList[name].play();
}

void	nx::sfx::SfxHandler::pauseSound(const std::string & name)
{
	if (!this->soundExist(name))
		throw SfxException("Sfx : ressource " + name + " is not loaded.");
	this->_soundList[name].pause();
}

void	nx::sfx::SfxHandler::stopSound(const std::string & name)
{
	if (!this->soundExist(name))
		throw SfxException("Sfx : ressource " + name + " is not loaded.");
	this->_soundList[name].stop();
}

// Setters

void 	nx::sfx::SfxHandler::setSoundLoop(const std::string & name, const bool loop)
{
	if (!this->soundExist(name))
		throw SfxException("Sfx : ressource " + name + " is not loaded.");
	this->_soundList[name].setLoop(loop);
}

void 	nx::sfx::SfxHandler::setSoundPitch(const std::string & name, const float pitch)
{
	if (!this->soundExist(name))
		throw SfxException("Sfx : ressource " + name + " is not loaded.");
	this->_soundList[name].setPitch(pitch);
}

void 	nx::sfx::SfxHandler::setSoundVolume(const std::string & name, const float volume)
{
	if (!this->soundExist(name))
		throw SfxException("Sfx : ressource " + name + " is not loaded.");
	this->_soundList[name].setVolume(volume);
}

void 	nx::sfx::SfxHandler::setSoundAttenuation(const std::string & name, const float attenuation)
{
	if (!this->soundExist(name))
		throw SfxException("Sfx : ressource " + name + " is not loaded.");
	this->_soundList[name].setAttenuation(attenuation);
}

// Getters

const bool					nx::sfx::SfxHandler::soundExist(const std::string & name) const
{
	if (this->_soundList.find(name) == this->_soundList.end())
		return (false);
	return (true);
}

const bool 					nx::sfx::SfxHandler::getSoundLoop(const std::string & name) const
{
	 if (!this->soundExist(name))
		 throw SfxException("Sfx : ressource " + name + " is not loaded.");
	 return (this->_soundList.at(name).getLoop());
}

const nx::sfx::SFX_STATUS 	nx::sfx::SfxHandler::getSoundStatus(const std::string & name) const
{
	if (!this->soundExist(name))
		throw SfxException("Sfx : ressource " + name + " is not loaded.");
	return (this->_soundList.at(name).getStatus());
}

const float 				nx::sfx::SfxHandler::getSoundVolume(const std::string & name) const
{
	if (!this->soundExist(name))
		throw SfxException("Sfx : ressource " + name + " is not loaded.");
	return (this->_soundList.at(name).getVolume());
}

const float					nx::sfx::SfxHandler::getSoundPitch(const std::string & name) const
{
	if (!this->soundExist(name))
		throw SfxException("Sfx : ressource " + name + " is not loaded.");
	return (this->_soundList.at(name).getPitch());
}

const float 				nx::sfx::SfxHandler::getSoundAttenuation(const std::string & name) const
{
	if (!this->soundExist(name))
		throw SfxException("Sfx : ressource " + name + " is not loaded.");
	return (this->_soundList.at(name).getAttenuation());
}

bool	nx::sfx::SfxHandler::addMusic(const std::string & name)
{
	Music	music(name);

	if (musicExist(name))
		return (false);

	if (this->_musicList.size() + this->_musicList.size() >= 256)
	{
		std::cerr << "Too much sf, can't load more" << std::endl;
		return (false);
	}

	try
	{
		this->_musicList[name] = music;
	}
	catch (const MusicException & e)
	{
		throw SfxException(e.what() + std::string (" (") + name + std::string (")"));
	}
	return (true);
}

void	nx::sfx::SfxHandler::removeMusic(const std::string & name)
{
	if (!musicExist(name))
		throw SfxException("Sfx : ressource " + name + " is not loaded.");
	this->_musicList.erase(name);
}

void	nx::sfx::SfxHandler::playMusic(const std::string & name)
{
	if (!this->musicExist(name))
		throw SfxException("Sfx : ressource " + name + " is not loaded.");
	this->_musicList[name].play();
}

void	nx::sfx::SfxHandler::pauseMusic(const std::string & name)
{
	if (!this->musicExist(name))
		throw SfxException("Sfx : ressource " + name + " is not loaded.");
	this->_musicList[name].pause();
}

void	nx::sfx::SfxHandler::stopMusic(const std::string & name)
{
	if (!this->musicExist(name))
		throw SfxException("Sfx : ressource " + name + " is not loaded.");
	this->_musicList[name].stop();
}

// Setters

void 	nx::sfx::SfxHandler::setMusicLoop(const std::string & name, const bool loop)
{
	if (!this->musicExist(name))
		throw SfxException("Sfx : ressource " + name + " is not loaded.");
	this->_musicList[name].setLoop(loop);
}

void 	nx::sfx::SfxHandler::setMusicPitch(const std::string & name, const float pitch)
{
	if (!this->musicExist(name))
		throw SfxException("Sfx : ressource " + name + " is not loaded.");
	this->_musicList[name].setPitch(pitch);
}

void 	nx::sfx::SfxHandler::setMusicVolume(const std::string & name, const float volume)
{
	if (!this->musicExist(name))
		throw SfxException("Sfx : ressource " + name + " is not loaded.");
	this->_musicList[name].setVolume(volume);
}

void 	nx::sfx::SfxHandler::setMusicAttenuation(const std::string & name, const float attenuation)
{
	if (!this->musicExist(name))
		throw SfxException("Sfx : ressource " + name + " is not loaded.");
	this->_musicList[name].setAttenuation(attenuation);
}

// Getters

const bool					nx::sfx::SfxHandler::musicExist(const std::string & name) const
{
	if (this->_musicList.find(name) == this->_musicList.end())
		return (false);
	return (true);
}

const bool 					nx::sfx::SfxHandler::getMusicLoop(const std::string & name) const
{
	if (!this->musicExist(name))
		throw SfxException("Sfx : ressource " + name + " is not loaded.");
	return (this->_musicList.at(name).getLoop());
}

const nx::sfx::SFX_STATUS 	nx::sfx::SfxHandler::getMusicStatus(const std::string & name) const
{
	if (!this->musicExist(name))
		throw SfxException("Sfx : ressource " + name + " is not loaded.");
	return (this->_musicList.at(name).getStatus());
}

const float 				nx::sfx::SfxHandler::getMusicVolume(const std::string & name) const
{
	if (!this->musicExist(name))
		throw SfxException("Sfx : ressource " + name + " is not loaded.");
	return (this->_musicList.at(name).getVolume());
}

const float					nx::sfx::SfxHandler::getMusicPitch(const std::string & name) const
{
	if (!this->musicExist(name))
		throw SfxException("Sfx : ressource " + name + " is not loaded.");
	return (this->_musicList.at(name).getPitch());
}

const float 				nx::sfx::SfxHandler::getMusicAttenuation(const std::string & name) const
{
	if (!this->musicExist(name))
		throw SfxException("Sfx : ressource " + name + " is not loaded.");
	return (this->_musicList.at(name).getAttenuation());
}

const unsigned int 			nx::sfx::SfxHandler::getMusicChannelCount(const std::string & name) const
{
	if (!this->musicExist(name))
		throw SfxException("Sfx : ressource " + name + " is not loaded.");
	return (this->_musicList.at(name).getChannelCount());
}

const unsigned int 			nx::sfx::SfxHandler::getMusicSampleRate(const std::string & name) const
{
	if (!this->musicExist(name))
		throw SfxException("Sfx : ressource " + name + " is not loaded.");
	return (this->_musicList.at(name).getSampleRate());
}
