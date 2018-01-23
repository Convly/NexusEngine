#ifndef NEXUS_ENGINE__SYSTEM_TPL_HPP_
# define NEXUS_ENGINE__SYSTEM_TPL_HPP_

#include <string>
#include <vector>
#include <functional>
#include <algorithm>

#include "Nexus/events.hpp"
#include "Nexus/log.hpp"
#include "Nexus/errors/InvalidDeserialization.hpp"

namespace nx {
	class Engine;
}

namespace nx {

	struct Event
	{
		Event(const nx::EVENT type_, const std::vector<char>& data_)
		: type(type_), data(data_) {}

		nx::EVENT			type;
		std::vector<char>	data;

		template <typename T>
		static std::vector<char> serializer(const T& obj) {
			auto const ptr = reinterpret_cast<const char*>(&obj);
			return std::vector<char>(ptr, ptr + sizeof(T));
		}

		template <typename T>
		static T deserializer(const std::vector<char>& data) {
			const T* ist = reinterpret_cast<const T*>(data.data());
			if (!ist)
				throw nx::InvalidDeserializationException(typeid(ist).name());
			return *ist;
		}
		
		template <typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & type;
			ar & data;
		}
	};

	struct EventLink
	{
		EventLink(const uint32_t uid_, const nx::EVENT type_, const std::function<void(const nx::Event&)>& callback_)
		: uid(uid_), type(type_), callback(callback_) {}

		uint32_t uid;
		nx::EVENT type;
		std::function<void(const nx::Event&)> callback;
	};

	class SystemTpl
	{
	public:
		SystemTpl(const std::string& name);
		virtual ~SystemTpl();

	public:
		virtual void				update(void) = 0;
		virtual void				init(void) = 0;
		virtual bool				checkIntegrity(void) const = 0;
		virtual const std::string&	getName(void) const;
		virtual const nx::Engine&	getEngine() const;

	public:
		virtual void emitter(const nx::Event&);
		virtual uint32_t connect(const nx::EVENT eventType, const std::function<void(const nx::Event&)>& callback);
		virtual bool disconnect(const uint32_t uid);


	protected:
		std::vector<nx::EventLink>	_links;
		nx::Engine&					_engine;
		const std::string			_name;
		uint32_t					_maxConnectID;
	};
}

#endif // NEXUS_ENGINE__SYSTEM_TPL_HPP_
