//
// Made by Marco
//

#ifndef NEXUS_ENGINE__ERROR_DLLAODER_
# define NEXUS_ENGINE__ERROR_DLLOADER_

#include <exception>
#include <string>

namespace nx
{
	class DLLoaderException : public std::exception
	{
		protected:
			std::string _msg;
		public:
			DLLoaderException (const std::string& msg):
				_msg(msg)
			{
			}

			virtual ~DLLoaderException () throw ()
			{
			}

			virtual const char* what() const throw ()
			{
				return this->_msg.c_str(); 
			}
	};
}

#endif // !NEXUS_ENGINE__ERROR_DLLOADER_
