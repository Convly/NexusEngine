//
// Made by Marco
//

#ifndef NEXUS_ENGINE__ERROR_FRAMEWORK_
# define NEXUS_ENGINE__ERROR_FRAMEWORK_

#include <exception>
#include <string>

namespace nx
{
	class FrameworkException : public std::exception
	{
		protected:
			std::string _msg;
		public:
			FrameworkException (const std::string& msg):
				_msg("FrameworkException: " + msg)
			{
			}

			virtual ~FrameworkException () throw ()
			{
			}

			virtual const char* what() const throw ()
			{
				return this->_msg.c_str(); 
			}
	};
}

#endif // !NEXUS_ENGINE__ERROR_FRAMEWORK_
