#ifndef NEXUS_LAUNCHER_ERRORS_BAD_FORMAT_GAME_JSON_EXCEPTION_HPP_
#define NEXUS_LAUNCHER_ERRORS_BAD_FORMAT_GAME_JSON_EXCEPTION_HPP_

#include <exception>
#include <string>

namespace nx {
	class BadFormatGameJSONException : public std::exception
	{
		protected:
			std::string _msg;
		public:
			BadFormatGameJSONException (const std::string& error):	_msg(std::string("Error while parsing the game configuration file: ") + error)	{}
	
			virtual ~BadFormatGameJSONException () throw () {}

			virtual const char* what() const throw () { return this->_msg.c_str(); }
	};
}

#endif // !NEXUS_LAUNCHER_ERRORS_BAD_FORMAT_GAME_JSON_EXCEPTION_HPP_