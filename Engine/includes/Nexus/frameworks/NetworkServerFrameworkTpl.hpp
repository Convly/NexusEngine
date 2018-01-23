#ifndef NETWORKSERVER_FRAMEWORK_TEMPLATE_HPP_
# define NETWORKSERVER_FRAMEWORK_TEMPLATE_HPP_

#include <iostream>
#include "Nexus/engine.hpp"

namespace nx {

	enum NETPROT {
		UDP,
		TCP
	};

	enum NETCON_STATE {
		UNDEFINED,
		CONNECTED,
		DISCONNECTED
	};

	struct netserv_client_t {
		netserv_client_t() : id_(-1), status_(nx::NETCON_STATE::UNDEFINED), port_(0)
		{
			ip_[0] = '\0';
		}
		netserv_client_t(const int id, const nx::NETCON_STATE status, const std::string& ip, const unsigned short port) : id_(id), status_(status), port_(port)
		{
			ip.copy(ip_, ip.size(), 0);
			ip_[ip.size()] = 0;			
		}
		netserv_client_t(const netserv_client_t& other) : id_(other.id_), status_(other.status_), port_(other.port_)
		{
			std::string buf(other.ip_);
			buf.copy(ip_, buf.size(), 0);
			ip_[buf.size()] = 0;
		}

		int id_;
		nx::NETCON_STATE status_;
		char ip_[15];
		unsigned short port_;

		nx::netserv_client_t& operator=(const nx::netserv_client_t& other)
		{
			if (this != &other) {
				id_ = other.id_;
				status_ = other.status_;
				std::string buf(other.ip_);
				buf.copy(ip_, buf.size(), 0);
				ip_[buf.size()] = '\0';
				port_ = other.port_;
			}

			return *this;
		}

		template <typename Archive>
		void serialize(Archive& ar, unsigned int version)
		{
			ar & id_;
			ar & status_;
			ar & ip_;
			ar & port_;
		}
	};

	struct netserv_udp_t {
		netserv_udp_t(const bool fatal, const nx::Event& event) : fatal_(fatal), event_(event) {}

		bool fatal_;
		nx::Event event_;

		template <typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & fatal_;
			ar & event_;
		}
	};

	struct netserv_send_infos_t {
		netserv_send_infos_t(const uint8_t clientId, const nx::netserv_udp_t& net, const nx::NETPROT prot) : clientId_(clientId), net_(net), prot_(prot) {}

		uint8_t clientId_;
		nx::netserv_udp_t net_;
		nx::NETPROT prot_;

		template <typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & clientId_;
			ar & net_;
			ar & prot_;
		}
	};

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
		virtual void send(const nx::netserv_send_infos_t& netInfos) = 0;
		virtual void sendAll(const nx::netserv_udp_t& net) = 0;
		virtual void disconnect(const uint8_t clientId) = 0;
		virtual void connectClient(const nx::netserv_client_t& clientInfos) = 0;
	};
}

#endif /* NETWORKSERVER_FRAMEWORK_TEMPLATE_HPP_*/