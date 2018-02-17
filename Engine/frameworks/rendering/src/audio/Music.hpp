//
// Made by Marco
//

#ifndef MUSIC_HPP_
# define MUSIC_HPP_

# include <memory>
# include <iostream>
# include <SFML/Audio.hpp>
# include "../MusicException.hpp"
# include "Nexus/modules/maths/maths.hpp"
# include "Nexus/frameworks/RenderingFrameworkTpl.hpp"

namespace nx
{
	namespace sfx
	{
		class Music
		{
		private:
			sf::Music	_music;
			std::string	_name;

		public:
			Music() {};
			Music(const std::string & name);
			Music(const Music & other);
			virtual ~Music();

		public:
			void	play();
			void 	pause();
			void 	stop();

		public:
			void 	setLoop(const bool loop);
			void 	setPitch(const float pitch);
			void 	setVolume(const float volume);
			void 	setAttenuation(const float attenuation);

		public:
			const std::string &		getName() const;
			const bool 				getLoop() const;
			const SFX_STATUS 		getStatus() const;
			const float 			getVolume() const;
			const float				getPitch() const;
			const float 			getAttenuation() const;
			const unsigned int 		getChannelCount() const;
			const unsigned int 		getSampleRate() const;

		public:
			Music & operator=(const Music & other);
		};
	}
}
#endif //MUSIC_HPP_

