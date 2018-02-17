//
// Made by Marco
//

# include "SfxHandler.hpp"

nx::sfx::SfxHandler::SfxHandler()
{
	_soundPath = enginePtr->getEnv().getGameInfos().getRootPath() + enginePtr->getGameInfosParser()->getFields()._resources.at("sounds");
	_musicPath = enginePtr->getEnv().getGameInfos().getRootPath() + enginePtr->getGameInfosParser()->getFields()._resources.at("musics");
}

nx::sfx::SfxHandler::~SfxHandler()
{
}

bool	nx::sfx::SfxHandler::addSound(const std::string & name)
{
	Sound	sound(_soundPath + name);

	if (this->soundExist(_soundPath + name))
		return (false);
	
	if (this->_soundList.size() + this->_musicList.size() >= 256)
	{
		std::cerr << "Too much sf, can't load more" << std::endl;
		return (false);
	}
	
	try
	{
		this->_soundList[_soundPath + name] = sound;
	}
	catch (const SoundException & e)
	{
		throw SfxException(e.what() + std::string(" (") + _soundPath + name + std::string (")"));
	}
	return (true);
}

void	nx::sfx::SfxHandler::removeSound(const std::string & name)
{
	if (!this->soundExist(_soundPath + name))
		throw SfxException("Sfx : ressource " + _soundPath + name + " is not loaded.");
	this->_soundList.erase(_soundPath + name);
}

void	nx::sfx::SfxHandler::playSound(const std::string & name)
{
	if (!this->soundExist(_soundPath + name))
		throw SfxException("Sfx : ressource " + _soundPath + name + " is not loaded.");
	this->_soundList[_soundPath + name].play();
}

void	nx::sfx::SfxHandler::pauseSound(const std::string & name)
{
	if (!this->soundExist(_soundPath + name))
		throw SfxException("Sfx : ressource " + _soundPath + name + " is not loaded.");
	this->_soundList[_soundPath + name].pause();
}

void	nx::sfx::SfxHandler::stopSound(const std::string & name)
{
	if (!this->soundExist(_soundPath + name))
		throw SfxException("Sfx : ressource " + _soundPath + name + " is not loaded.");
	this->_soundList[_soundPath + name].stop();
}

// Setters

void 	nx::sfx::SfxHandler::setSoundLoop(const std::string & name, const bool loop)
{
	if (!this->soundExist(_soundPath + name))
		throw SfxException("Sfx : ressource " + _soundPath + name + " is not loaded.");
	this->_soundList[_soundPath + name].setLoop(loop);
}

void 	nx::sfx::SfxHandler::setSoundPitch(const std::string & name, const float pitch)
{
	if (!this->soundExist(_soundPath + name))
		throw SfxException("Sfx : ressource " + _soundPath + name + " is not loaded.");
	this->_soundList[_soundPath + name].setPitch(pitch);
}

void 	nx::sfx::SfxHandler::setSoundVolume(const std::string & name, const float volume)
{
	if (!this->soundExist(_soundPath + name))
		throw SfxException("Sfx : ressource " + _soundPath + name + " is not loaded.");
	this->_soundList[_soundPath + name].setVolume(volume);
}

void 	nx::sfx::SfxHandler::setSoundAttenuation(const std::string & name, const float attenuation)
{
	if (!this->soundExist(_soundPath + name))
		throw SfxException("Sfx : ressource " + _soundPath + name + " is not loaded.");
	this->_soundList[_soundPath + name].setAttenuation(attenuation);
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
	 if (!this->soundExist(_soundPath + name))
		 throw SfxException("Sfx : ressource " + _soundPath + name + " is not loaded.");
	 return (this->_soundList.at(_soundPath + name).getLoop());
}

const nx::sfx::SFX_STATUS 	nx::sfx::SfxHandler::getSoundStatus(const std::string & name) const
{
	if (!this->soundExist(_soundPath + name))
		throw SfxException("Sfx : ressource " + _soundPath + name + " is not loaded.");
	return (this->_soundList.at(_soundPath + name).getStatus());
}

const float 				nx::sfx::SfxHandler::getSoundVolume(const std::string & name) const
{
	if (!this->soundExist(_soundPath + name))
		throw SfxException("Sfx : ressource " + _soundPath + name + " is not loaded.");
	return (this->_soundList.at(_soundPath + name).getVolume());
}

const float					nx::sfx::SfxHandler::getSoundPitch(const std::string & name) const
{
	if (!this->soundExist(_soundPath + name))
		throw SfxException("Sfx : ressource " + _soundPath + name + " is not loaded.");
	return (this->_soundList.at(_soundPath + name).getPitch());
}

const float 				nx::sfx::SfxHandler::getSoundAttenuation(const std::string & name) const
{
	if (!this->soundExist(_soundPath + name))
		throw SfxException("Sfx : ressource " + _soundPath + name + " is not loaded.");
	return (this->_soundList.at(_soundPath + name).getAttenuation());
}

bool	nx::sfx::SfxHandler::addMusic(const std::string & name)
{
	Music	music(_musicPath + name);

	if (musicExist(_musicPath + name))
		return (false);

	if (this->_musicList.size() + this->_musicList.size() >= 256)
	{
		std::cerr << "Too much sf, can't load more" << std::endl;
		return (false);
	}

	try
	{
		this->_musicList[_musicPath + name] = music;
	}
	catch (const MusicException & e)
	{
		throw SfxException(e.what() + std::string (" (") + _musicPath + name + std::string (")"));
	}
	return (true);
}

void	nx::sfx::SfxHandler::removeMusic(const std::string & name)
{
	if (!musicExist(_musicPath + name))
		throw SfxException("Sfx : ressource " + _musicPath + name + " is not loaded.");
	this->_musicList.erase(_musicPath + name);
}

void	nx::sfx::SfxHandler::playMusic(const std::string & name)
{
	if (!this->musicExist(_musicPath + name))
		throw SfxException("Sfx : ressource " + _musicPath + name + " is not loaded.");
	this->_musicList[_musicPath + name].play();
}

void	nx::sfx::SfxHandler::pauseMusic(const std::string & name)
{
	if (!this->musicExist(_musicPath + name))
		throw SfxException("Sfx : ressource " + _musicPath + name + " is not loaded.");
	this->_musicList[_musicPath + name].pause();
}

void	nx::sfx::SfxHandler::stopMusic(const std::string & name)
{
	if (!this->musicExist(_musicPath + name))
		throw SfxException("Sfx : ressource " + _musicPath + name + " is not loaded.");
	this->_musicList[_musicPath + name].stop();
}

// Setters

void 	nx::sfx::SfxHandler::setMusicLoop(const std::string & name, const bool loop)
{
	if (!this->musicExist(_musicPath + name))
		throw SfxException("Sfx : ressource " + _musicPath + name + " is not loaded.");
	this->_musicList[_musicPath + name].setLoop(loop);
}

void 	nx::sfx::SfxHandler::setMusicPitch(const std::string & name, const float pitch)
{
	if (!this->musicExist(_musicPath + name))
		throw SfxException("Sfx : ressource " + _musicPath + name + " is not loaded.");
	this->_musicList[_musicPath + name].setPitch(pitch);
}

void 	nx::sfx::SfxHandler::setMusicVolume(const std::string & name, const float volume)
{
	if (!this->musicExist(_musicPath + name))
		throw SfxException("Sfx : ressource " + _musicPath + name + " is not loaded.");
	this->_musicList[_musicPath + name].setVolume(volume);
}

void 	nx::sfx::SfxHandler::setMusicAttenuation(const std::string & name, const float attenuation)
{
	if (!this->musicExist(_musicPath + name))
		throw SfxException("Sfx : ressource " + _musicPath + name + " is not loaded.");
	this->_musicList[_musicPath + name].setAttenuation(attenuation);
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
	if (!this->musicExist(_musicPath + name))
		throw SfxException("Sfx : ressource " + _musicPath + name + " is not loaded.");
	return (this->_musicList.at(_musicPath + name).getLoop());
}

const nx::sfx::SFX_STATUS 	nx::sfx::SfxHandler::getMusicStatus(const std::string & name) const
{
	if (!this->musicExist(_musicPath + name))
		throw SfxException("Sfx : ressource " + _musicPath + name + " is not loaded.");
	return (this->_musicList.at(_musicPath + name).getStatus());
}

const float 				nx::sfx::SfxHandler::getMusicVolume(const std::string & name) const
{
	if (!this->musicExist(_musicPath + name))
		throw SfxException("Sfx : ressource " + _musicPath + name + " is not loaded.");
	return (this->_musicList.at(_musicPath + name).getVolume());
}

const float					nx::sfx::SfxHandler::getMusicPitch(const std::string & name) const
{
	if (!this->musicExist(_musicPath + name))
		throw SfxException("Sfx : ressource " + _musicPath + name + " is not loaded.");
	return (this->_musicList.at(_musicPath + name).getPitch());
}

const float 				nx::sfx::SfxHandler::getMusicAttenuation(const std::string & name) const
{
	if (!this->musicExist(_musicPath + name))
		throw SfxException("Sfx : ressource " + _musicPath + name + " is not loaded.");
	return (this->_musicList.at(_musicPath + name).getAttenuation());
}

const unsigned int 			nx::sfx::SfxHandler::getMusicChannelCount(const std::string & name) const
{
	if (!this->musicExist(_musicPath + name))
		throw SfxException("Sfx : ressource " + _musicPath + name + " is not loaded.");
	return (this->_musicList.at(_musicPath + name).getChannelCount());
}

const unsigned int 			nx::sfx::SfxHandler::getMusicSampleRate(const std::string & name) const
{
	if (!this->musicExist(_musicPath + name))
		throw SfxException("Sfx : ressource " + _musicPath + name + " is not loaded.");
	return (this->_musicList.at(_musicPath + name).getSampleRate());
}
