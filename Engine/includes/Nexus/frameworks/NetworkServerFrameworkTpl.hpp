#ifndef NETWORKSERVER_FRAMEWORK_TEMPLATE_HPP_
# define NETWORKSERVER_FRAMEWORK_TEMPLATE_HPP_

#include <iostream>
#include <chrono>
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

	enum NETPACKET_TYPE {
		EVENT_TRIGGER,
		ENV_MODIFIER
	};

	enum NETENV_MODIFIER {
		ADD_GAMEOBJECT,
		REMOVE_GAMEOBJECT,
		UPDATE_GAMEOBJECT,
		CLEAR_SCENE
	};

	struct netserv_client_t {
		netserv_client_t() : id_(-1), status_(nx::NETCON_STATE::UNDEFINED), port_(0), last_ping_(std::chrono::high_resolution_clock::now())
		{
			ip_[0] = '\0';
		}
		netserv_client_t(const int id, const nx::NETCON_STATE status, const std::string& ip, const unsigned short port) : id_(id), status_(status), port_(port), last_ping_(std::chrono::high_resolution_clock::now())
		{
			ip.copy(ip_, ip.size(), 0);
			ip_[ip.size()] = 0;			
		}
		netserv_client_t(const netserv_client_t& other) : id_(other.id_), status_(other.status_), port_(other.port_), last_ping_(other.last_ping_)
		{
			std::string buf(other.ip_);
			buf.copy(ip_, buf.size(), 0);
			ip_[buf.size()] = 0;
		}

		int id_;
		nx::NETCON_STATE status_;
		char ip_[15];
		unsigned short port_;
		std::chrono::high_resolution_clock::time_point last_ping_;

		nx::netserv_client_t& operator=(const nx::netserv_client_t& other)
		{
			if (this != &other) {
				id_ = other.id_;
				status_ = other.status_;
				std::string buf(other.ip_);
				buf.copy(ip_, buf.size(), 0);
				ip_[buf.size()] = '\0';
				port_ = other.port_;
				last_ping_ = other.last_ping_;
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
			ar & last_ping_;
		}
	};

	struct netserv_send_event_t {
		netserv_send_event_t() : clientId_(-1) {}
		netserv_send_event_t(const uint8_t clientId, const nx::Event& event) : clientId_(clientId), event_(event) {}

		uint8_t clientId_;
		nx::Event event_;

		template <typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & clientId_;
			ar & event_;
		}
	};

	template <typename T>
	struct netserv_send_env_t {
		netserv_send_env_t(const uint8_t clientId, const T& object, const nx::NETPROT prot) : clientId_(clientId), object_(object), prot_(prot) {}

		uint8_t clientId_;
		T object_;
		nx::NETPROT prot_;

		template <typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & clientId_;
			ar & object_;
			ar & prot_;
		}	
	};
}

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
		virtual void sendEvent(nx::netserv_send_event_t& netInfos) = 0;
		virtual void sendAll(nx::netserv_send_event_t& net) = 0;
		virtual void disconnect(const uint8_t clientId) = 0;
		virtual void connectClient(const nx::netserv_client_t& clientInfos) = 0;
	};
}

#endif /* NETWORKSERVER_FRAMEWORK_TEMPLATE_HPP_*/