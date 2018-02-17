//
// Made by Marco
//


#ifndef NEXUS_ENGINE__ERROR_SFX
#define NEXUS_ENGINE__ERROR_SFX

#include <exception>
#include <string>

namespace nx {
	class SfxException : public std::exception
	{
	protected:
		std::string _msg;
	public:
		SfxException(std::string const& msg) : _msg(msg) {}

		virtual ~SfxException() throw () {}

		virtual const char* what() const throw () { return this->_msg.c_str(); }
	};
}

#endif // !NEXUS_ENGINE__ERROR_SFX
