//
// Made by Marco
//

#ifndef SOUND_HANDLER_HPP
# define SOUND_HANDLER_HPP

# include "Sound.hpp"
# include "Music.hpp"
# include <unordered_map>
# include "Nexus/engine.hpp"
# include "../SfxException.hpp"

extern nx::Engine* enginePtr;

namespace nx
{
	namespace sfx
	{
		class SfxHandler
		{
		private:
			std::unordered_map<std::string, Sound>	_soundList;
			std::unordered_map<std::string, Music>	_musicList;

		private:
			std::string _soundPath;
			std::string _musicPath;

		public:
			SfxHandler();
			virtual ~SfxHandler();

			// Sound
		public:
			bool	addSound(const std::string & name);
			void	removeSound(const std::string & name);

		public:
			void	playSound(const std::string & name);
			void	pauseSound(const std::string & name);
			void	stopSound(const std::string & name);

		public:
			void 	setSoundLoop(const std::string & name, const bool loop);
			void 	setSoundPitch(const std::string & name, const float pitch);
			void 	setSoundVolume(const std::string & name, const float volume);
			void 	setSoundAttenuation(const std::string & name, const float attenuation);

		public:
			const bool			soundExist(const std::string & name) const;
			const bool 			getSoundLoop(const std::string & name) const;
			const SFX_STATUS 	getSoundStatus(const std::string & name) const;
			const float 		getSoundVolume(const std::string & name) const;
			const float			getSoundPitch(const std::string & name) const;
			const float 		getSoundAttenuation(const std::string & name) const;

			// Music
		public:
			bool	addMusic(const std::string & name);
			void	removeMusic(const std::string & name);

		public:
			void	playMusic(const std::string & name);
			void	pauseMusic(const std::string & name);
			void	stopMusic(const std::string & name);

		public:
			void 	setMusicLoop(const std::string & name, const bool loop);
			void 	setMusicPitch(const std::string & name, const float pitch);
			void 	setMusicVolume(const std::string & name, const float volume);
			void 	setMusicAttenuation(const std::string & name, const float attenuation);

		public:
			const bool			musicExist(const std::string & name) const;
			const bool			getMusicLoop(const std::string & name) const;
			const SFX_STATUS	getMusicStatus(const std::string & name) const;
			const float 		getMusicVolume(const std::string & name) const;
			const float			getMusicPitch(const std::string & name) const;
			const float 		getMusicAttenuation(const std::string & name) const;
			const unsigned int	getMusicChannelCount(const std::string & name) const;
			const unsigned int 	getMusicSampleRate(const std::string & name) const;
		};
	}
}
#endif // SFX_HANDLER_HPP_
