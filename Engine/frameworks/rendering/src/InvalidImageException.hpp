#ifndef NEXUS_ENGINE__ERROR_INVALID_IMAGE
#define NEXUS_ENGINE__ERROR_INVALID_IMAGE

#include <exception>
#include <string>

namespace nx {
	class InvalidImageException : public std::exception
	{
	protected:
		std::string _msg;
	public:
		InvalidImageException(std::string const& imgPath) : _msg("Couldn't open'" + imgPath + "' or the image wasn't found.") {}

		virtual ~InvalidImageException() throw () {}

		virtual const char* what() const throw () { return this->_msg.c_str(); }
	};
}

#endif // !NEXUS_ENGINE__ERROR_INVALID_IMAGE