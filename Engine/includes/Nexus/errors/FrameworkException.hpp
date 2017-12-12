//
// Made by Marco
//

#ifndef NEXUS_ENGINE_ERROR_FRAMEWORK_HPP
# define NEXUS_ENGINE_ERROR_FRAMEWORK_HPP

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
				_msg(msg)
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

#endif // !NEXUS_ENGINE_ERROR_FRAMEWORK_HPP
