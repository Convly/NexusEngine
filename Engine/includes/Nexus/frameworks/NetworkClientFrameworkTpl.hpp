#ifndef NETWORKCLIENT_FRAMEWORK_TEMPLATE_HPP_
# define NETWORKCLIENT_FRAMEWORK_TEMPLATE_HPP_

#include <iostream>
#include "Nexus/standalone/network/netutils.hpp"

namespace nx {
	class NetworkClientFrameworkTpl
	{
	protected:
		const std::string 		_name;

	public:
		// This method must be implemented this way
		NetworkClientFrameworkTpl(const std::string & name) : _name(name) {};
		// This method must be implemented this way
		virtual ~NetworkClientFrameworkTpl() {};
		// This method must be implemented this way
		const std::string& getName(void) const {return this->_name;}

		virtual void connect(const nx::netcust_host_t&) = 0;
		virtual void disconnect() = 0;
		virtual void send(const nx::netserv_send_event_t&) = 0;
		virtual int getClientId() = 0;
		virtual void setClientId(const int) = 0;
	};	
}

#endif /* NETWORKCLIENT_FRAMEWORK_TEMPLATE_HPP_*/