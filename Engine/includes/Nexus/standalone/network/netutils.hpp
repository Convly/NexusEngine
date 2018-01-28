#ifndef ENGINE_STANDALONE_NETWORK_UTILS_HPP_
#define ENGINE_STANDALONE_NETWORK_UTILS_HPP_

#include <string>
#include <chrono>
#include <iostream>
#include <memory>
#include <sstream>

#include "Nexus/standalone/external/any.hpp"

#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include "Nexus/systems/SystemTpl.hpp"

namespace nx {

	class PlaceHolder
    {
    public:
        virtual ~PlaceHolder(){}
        PlaceHolder(){}
    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
        }

    };

    template<typename T>
    class DerivedPlacedHolder:
        public PlaceHolder
    {
        public:
            DerivedPlacedHolder()
            {

            }
            DerivedPlacedHolder(T &value)
            {
                m_value = value;
            }
        T m_value;

    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & boost::serialization::base_object<PlaceHolder>(*this);
            ar & m_value;
        }
    };

    class Any
    {
    public:
        Any()
        {

        }

        template<typename T>
        Any(const T &value)
        {
            m_placeholder.reset(new nx::DerivedPlacedHolder<T>(const_cast<T&>(value)));
        }

        template<typename T>
        void operator=(const T &value)
        {
            m_placeholder.reset(new nx::DerivedPlacedHolder<T>(const_cast<T&>(value)));
        }

    protected:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & m_placeholder;
        }

        template<typename T>
        friend    T Anycast(Any &val);

        std::shared_ptr<PlaceHolder> m_placeholder;
    };

    template<typename T>
    T Anycast(Any &val)
    {
        std::shared_ptr<nx::DerivedPlacedHolder<T>> concrete = std::dynamic_pointer_cast<nx::DerivedPlacedHolder<T> >(val.m_placeholder);
        if (concrete.get()==NULL)
            throw std::invalid_argument("Not convertible");

        return concrete->m_value;
    }

	struct UdpEventPacket {
		UdpEventPacket() {}
		UdpEventPacket(const nx::EVENT type, const nx::Any& object) : type_(type), object_(object) {}
		UdpEventPacket(const UdpEventPacket& other) : type_(other.type_), object_(other.object_) {}
		
		nx::EVENT type_;
		nx::Any object_;

		template <typename Archive>
		void serialize(Archive& ar, unsigned int version)
		{
			ar & type_;
			ar & object_;
		}
	};

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

	struct EnumClassHashNetServ
	{
		template <typename T>
		std::size_t operator()(T t) const
		{
			return static_cast<std::size_t>(t);
		}
	};

	static const std::unordered_map<nx::EVENT, std::function<external::any(nx::Any&)>, EnumClassHashNetServ> nx_any_convert_serialize = {
		{nx::EVENT::SCRIPT_RUN,					[&](nx::Any& object) -> external::any {return nx::Anycast<std::string>(object);}},
		{nx::EVENT::SCRIPT_LOAD,				[&](nx::Any& object) -> external::any {return nx::Anycast<std::string>(object);}},
		{nx::EVENT::SCRIPT_INIT,				[&](nx::Any& object) -> external::any {return nx::Anycast<std::string>(object);}},
		{nx::EVENT::SCRIPT_UPDATE,				[&](nx::Any& object) -> external::any {return nx::Anycast<std::string>(object);}},
		{nx::EVENT::SCRIPT_EXEC_FUNCTION,		[&](nx::Any& object) -> external::any {return nx::Anycast<nx::script::ScriptInfos>(object);}},
		{nx::EVENT::NETCUST_CONNECT,			[&](nx::Any& object) -> external::any {return std::string("");}},
		{nx::EVENT::NETCUST_DISCONNECT,			[&](nx::Any& object) -> external::any {return std::string("");}},
		{nx::EVENT::NETCUST_LISTEN,				[&](nx::Any& object) -> external::any {return nx::Anycast<std::string>(object);}},
		{nx::EVENT::NETCUST_SEND,				[&](nx::Any& object) -> external::any {return nx::Anycast<std::string>(object);}},
		{nx::EVENT::NETSERV_SEND,				[&](nx::Any& object) -> external::any {return nx::Anycast<nx::netserv_send_event_t>(object);}},
		{nx::EVENT::NETSERV_SEND_ALL,			[&](nx::Any& object) -> external::any {return nx::Anycast<nx::netserv_send_event_t>(object);}},
		{nx::EVENT::NETSERV_FORCE_DISCONNECT,	[&](nx::Any& object) -> external::any {return nx::Anycast<uint8_t>(object);}}
	};

	static const std::unordered_map<nx::EVENT, std::function<nx::Any(external::any&)>, EnumClassHashNetServ> std_any_convert_serialize = {
		{nx::EVENT::SCRIPT_RUN,					[&](external::any& object) -> nx::Any {return external::any_cast<std::string>(object);}},
		{nx::EVENT::SCRIPT_LOAD,				[&](external::any& object) -> nx::Any {return external::any_cast<std::string>(object);}},
		{nx::EVENT::SCRIPT_INIT,				[&](external::any& object) -> nx::Any {return external::any_cast<std::string>(object);}},
		{nx::EVENT::SCRIPT_UPDATE,				[&](external::any& object) -> nx::Any {return external::any_cast<std::string>(object);}},
		{nx::EVENT::SCRIPT_EXEC_FUNCTION,		[&](external::any& object) -> nx::Any {return external::any_cast<nx::script::ScriptInfos>(object);}},
		{nx::EVENT::NETCUST_CONNECT,			[&](external::any& object) -> nx::Any {return std::string("");}},
		{nx::EVENT::NETCUST_DISCONNECT,			[&](external::any& object) -> nx::Any {return std::string("");}},
		{nx::EVENT::NETCUST_LISTEN,				[&](external::any& object) -> nx::Any {return external::any_cast<std::string>(object);}},
		{nx::EVENT::NETCUST_SEND,				[&](external::any& object) -> nx::Any {return external::any_cast<std::string>(object);}},
		{nx::EVENT::NETSERV_SEND,				[&](external::any& object) -> nx::Any {return external::any_cast<nx::netserv_send_event_t>(object);}},
		{nx::EVENT::NETSERV_SEND_ALL,			[&](external::any& object) -> nx::Any {return external::any_cast<nx::netserv_send_event_t>(object);}},
		{nx::EVENT::NETSERV_FORCE_DISCONNECT,	[&](external::any& object) -> nx::Any {return external::any_cast<uint8_t>(object);}}
	};
}

#endif