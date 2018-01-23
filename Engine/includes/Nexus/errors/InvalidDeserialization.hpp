#ifndef NEXUS_ENGINE_ERRORS_INVALID_DESERIALIZATION_HPP_
#define NEXUS_ENGINE_ERRORS_INVALID_DESERIALIZATION_HPP_

#include <exception>
#include <string>

namespace nx {
	class InvalidDeserializationException : public std::exception
	{
		protected:
			std::string _msg;
		public:
			InvalidDeserializationException (const std::string& type):	_msg(std::string("Invalid deserialization from raw data to : ") + type)	{}
	
			virtual ~InvalidDeserializationException () throw () {}

			virtual const char* what() const throw () { return this->_msg.c_str(); }
	};
}

#endif // !NEXUS_ENGINE_ERRORS_INVALID_DESERIALIZATION_HPP_