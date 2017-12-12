//
// Made by Marco
//

#ifndef NEXUS_ENGINE__ERROR_CRAWLER_INVALID_PATH_
# define NEXUS_ENGINE__ERROR_CRAWLER_INVALID_PATH_

#include <exception>
#include <string>

namespace nx
{
	class CrawlerInvalidPath : public std::exception
	{
		protected:
			std::string _msg;
		public:
			CrawlerInvalidPath (const std::string& msg):
				_msg(msg)
			{
			}

			virtual ~CrawlerInvalidPath () throw ()
			{
			}

			virtual const char* what() const throw ()
			{
				return this->_msg.c_str(); 
			}
	};
}

#endif // !NEXUS_ENGINE__ERROR_CRAWLER_INVALID_PATH_
