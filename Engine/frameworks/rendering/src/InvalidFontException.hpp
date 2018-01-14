#ifndef NEXUS_ENGINE__ERROR_INVALID_FONT
#define NEXUS_ENGINE__ERROR_INVALID_FONT

#include <exception>
#include <string>

namespace nx {
	class InvalidFontException : public std::exception
	{
	protected:
		std::string _msg;
	public:
		InvalidFontException(std::string const& fontPath) : _msg("Couldn't open'" + fontPath + "' or the font wasn't found.") {}

		virtual ~InvalidFontException() throw () {}

		virtual const char* what() const throw () { return this->_msg.c_str(); }
	};
}

#endif // !NEXUS_ENGINE__ERROR_INVALID_FONT