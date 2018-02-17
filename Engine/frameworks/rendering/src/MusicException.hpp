//
// Made by Marco
//

#ifndef NEXUS_ENGINE__ERROR_MUSIC
#define NEXUS_ENGINE__ERROR_MUSIC

#include <exception>
#include <string>

namespace nx {
	class MusicException : public std::exception
	{
	protected:
		std::string _msg;
	public:
		MusicException(std::string const& msg) : _msg(msg) {}

		virtual ~MusicException() throw () {}

		virtual const char* what() const throw () { return this->_msg.c_str(); }
	};
}

#endif // !NEXUS_ENGINE__ERROR_MUSIC
