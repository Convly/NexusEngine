//
// Made by Marco
//


#ifndef SOUND_HPP_
# define SOUND_HPP_

# include <iostream>
# include "SfxStatus.hpp"
# include <SFML/Audio.hpp>
# include "../SoundException.hpp"
# include "Nexus/modules/maths/maths.hpp"

namespace nx
{
	namespace sfx
	{
		class Sound
		{
		private:
			sf::Sound		_sound;
			sf::SoundBuffer	_buffer;
			std::string		_name;

		public:
			Sound() {};
			Sound(const std::string & name);
			Sound(const Sound & other);
			virtual ~Sound();

		public:
			void	play();
			void 	pause();
			void 	stop();

		public:
			void 	setLoop(bool loop);
			void 	setPitch(float pitch);
			void 	setVolume(float volume);
			void 	setAttenuation(float attenuation);

		public:
			const std::string &		getName() const;
			const bool 				getLoop() const;
			const SFX_STATUS 		getStatus() const;
			const float 			getVolume() const;
			const float				getPitch() const;
			const float 			getAttenuation() const;

		public:
			Sound & operator=(const Sound & other);
		};
	}
}

#endif //SOUND_HPP_
