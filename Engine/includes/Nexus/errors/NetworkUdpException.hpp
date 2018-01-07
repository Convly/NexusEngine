//
// Made by Marco
//

#ifndef NEXUS_ENGINE_ERROR_NETWORK_UDP_HPP
# define NEXUS_ENGINE_ERROR_NETWORK_UDP_HPP

#include <exception>
#include <string>

namespace nx
{
	class NetworkUdpException : public std::exception
	{
	protected:
		std::string		_msg;

	public:
		NetworkUdpException(const std::string& msg) :
			_msg(_msg + " (UDP)")
		{
		}

		virtual ~NetworkUdpException() throw ()
		{
		}

		virtual const char* what() const throw ()
		{
			return std::string(_msg).c_str();
		}
	};
}

#endif // !NEXUS_ENGINE_ERROR_NETWORK_UDP_HPP
