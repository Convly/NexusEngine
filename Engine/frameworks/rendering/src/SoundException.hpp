//
// Made by Marco
//

#ifndef NEXUS_ENGINE__ERROR_SOUND
#define NEXUS_ENGINE__ERROR_SOUND

#include <exception>
#include <string>

namespace nx {
	class SoundException : public std::exception
	{
	protected:
		std::string _msg;
	public:
		SoundException(std::string const& msg) : _msg(msg) {}

		virtual ~SoundException() throw () {}

		virtual const char* what() const throw () { return this->_msg.c_str(); }
	};
}

#endif // !NEXUS_ENGINE__ERROR_SOUND
