#ifndef NEXUS_ENGINE_ERROR_NETWORK_TCP_HPP
# define NEXUS_ENGINE_ERROR_NETWORK_TCP_HPP

#include <exception>
#include <string>

namespace nx
{
	class NetworkTcpException : public std::exception
	{
	protected:
		std::string		_msg;

	public:
		NetworkTcpException(const std::string& msg) :
			_msg("[Network] [TCP] " + _msg)
		{
		}

		virtual ~NetworkTcpException() throw ()
		{
		}

		virtual const char* what() const throw ()
		{
			return std::string(_msg).c_str();
		}
	};
}

#endif // !NEXUS_ENGINE_ERROR_NETWORK_TCP_HPP
