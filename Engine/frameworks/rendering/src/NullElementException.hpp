#ifndef NEXUS_ENGINE__ERROR_NULL_ELEMENT
#define NEXUS_ENGINE__ERROR_NULL_ELEMENT

#include <exception>
#include <string>

namespace nx {
	class NullElementException : public std::exception
	{
	protected:
		std::string _msg;
	public:
		NullElementException(std::string const& elementName) : _msg("The element '" + elementName + "' is null.") {}

		virtual ~NullElementException() throw () {}

		virtual const char* what() const throw () { return this->_msg.c_str(); }
	};
}

#endif // !NEXUS_ENGINE__ERROR_NULL_ELEMENT