#ifndef NEXUS_ENGINE__ERROR_RUN_WITHOUT_SETUP
#define NEXUS_ENGINE__ERROR_RUN_WITHOUT_SETUP

#include <exception>
#include <string>

namespace nx {
	class RunWithoutSetupException : public std::exception
	{
		protected:
			std::string _msg;
		public:
			RunWithoutSetupException ():	_msg("Trying to access the mainloop without giving a valid setup to the engine")	{}
	
			virtual ~RunWithoutSetupException () throw () {}

			virtual const char* what() const throw () { return this->_msg.c_str(); }
	};
}

#endif // !NEXUS_ENGINE__ERROR_RUN_WITHOUT_SETUP