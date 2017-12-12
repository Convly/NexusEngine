#ifndef NEXUS_ENGINE__ERROR_SYSTEM_NOT_FOUND
#define NEXUS_ENGINE__ERROR_SYSTEM_NOT_FOUND

#include <exception>
#include <string>

namespace nx {
	class SystemNotFoundException : public std::exception
	{
		protected:
			std::string _msg;
		public:
			SystemNotFoundException (const std::string& name):	_msg("System " + name + " not found.")	{}
	
			virtual ~SystemNotFoundException () throw () {}

			virtual const char* what() const throw () { return this->_msg.c_str(); }
	};
}

#endif // !NEXUS_ENGINE__ERROR_SYSTEM_NOT_FOUND