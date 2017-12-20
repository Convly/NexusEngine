#ifndef NEXUS_ENGINE__ERROR_ELEMENT_NOT_FOUND
#define NEXUS_ENGINE__ERROR_ELEMENT_NOT_FOUND

#include <exception>
#include <string>

namespace nx {
	class ElementNotFoundException : public std::exception
	{
	protected:
		std::string _msg;
	public:
		ElementNotFoundException(std::string const& elementName) : _msg("The element '" + elementName + "' wasn't found.") {}

		virtual ~ElementNotFoundException() throw () {}

		virtual const char* what() const throw () { return this->_msg.c_str(); }
	};
}

#endif // !NEXUS_ENGINE__ERROR_ELEMENT_NOT_FOUND