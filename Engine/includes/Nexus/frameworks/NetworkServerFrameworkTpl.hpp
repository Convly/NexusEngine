#ifndef NETWORKSERVER_FRAMEWORK_TEMPLATE_HPP_
# define NETWORKSERVER_FRAMEWORK_TEMPLATE_HPP_

#include "Nexus/engine.hpp"
#include "Nexus/standalone/network/netutils.hpp"

namespace nx {
	class NetworkServerFrameworkTpl
	{
	protected:
		const std::string 		_name;

	public:
		// This method must be implemented this way
		NetworkServerFrameworkTpl(const std::string & name) : _name(name) {};
		// This method must be implemented this way
		virtual ~NetworkServerFrameworkTpl() {};
		// This method must be implemented this way
		const std::string& getName(void) const {return this->_name;}

		// Framework Methods (must be virtual pure)
		virtual void sendEvent(const nx::netserv_send_event_t& netInfos) = 0;
		virtual void sendAll(const nx::netserv_send_event_t& net) = 0;
		virtual void disconnect(const int clientId) = 0;
		virtual void connectClient(const nx::netserv_client_t& clientInfos) = 0;
	};
}

#endif /* NETWORKSERVER_FRAMEWORK_TEMPLATE_HPP_*/