#ifndef NEXUS_ENGINE__SYSTEM_TPL_HPP_
# define NEXUS_ENGINE__SYSTEM_TPL_HPP_

#include <string>
#include <vector>
#include <functional>
#include <algorithm>

#include "Nexus/events.hpp"
#include "Nexus/log.hpp"
#include "Nexus/errors/InvalidDeserialization.hpp"
#include "Nexus/standalone/external/any.hpp"

namespace nx {
	class Engine;
}

namespace nx {

	struct Event
	{
		Event() : type(nx::EVENT::DEFAULT) {}
		Event(const nx::EVENT type_, const external::any& data_)
		: type(type_), data(data_) {}

		nx::EVENT				type;
		external::any	data;
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
