#ifndef NEXUS_ENGINE__ERROR_SCRIPT_NOT_LOADED
#define NEXUS_ENGINE__ERROR_SCRIPT_NOT_LOADED

#include <exception>
#include <string>

namespace nx {
	class ScriptNotLoaded : public std::exception
	{
		protected:
			std::string _msg;
		public:
			ScriptNotLoaded (const std::string& name):	_msg("Script " + name + " not found.")	{}
	
			virtual ~ScriptNotLoaded () throw () {}

			virtual const char* what() const throw () { return this->_msg.c_str(); }
	};
}

#endif // !NEXUS_ENGINE__ERROR_SCRIPT_NOT_LOADED