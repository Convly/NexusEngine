#ifndef NEXUS_ENGINE__ERROR_INVALID_CAST_ELEMENT
#define NEXUS_ENGINE__ERROR_INVALID_CAST_ELEMENT

#include <exception>
#include <string>

namespace nx {
	class InvalidCastElementException : public std::exception
	{
	protected:
		std::string _msg;
	public:
		InvalidCastElementException(std::string const& elementName, std::string const& type) : _msg("The element '" + elementName + "' couldn't be casted into a '" + type + "'") {}

		virtual ~InvalidCastElementException() throw () {}

		virtual const char* what() const throw () { return this->_msg.c_str(); }
	};
}

#endif // !NEXUS_ENGINE__ERROR_INVALID_CAST_ELEMENT