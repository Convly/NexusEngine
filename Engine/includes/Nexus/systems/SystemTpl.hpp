#ifndef NEXUS_ENGINE__SYSTEM_TPL_HPP_
# define NEXUS_ENGINE__SYSTEM_TPL_HPP_

#include <string>
#include <vector>
#include <functional>
#include <algorithm>

#include "Nexus/log.hpp"

namespace nx {
	class Engine;
}

namespace nx {

	struct Event
	{
		Event(const std::string& name_, const std::string& data_)
		: name(name_), data(data_) {}

		std::string name;
		std::string data;
	};

	struct EventLink
	{
		EventLink(const uint32_t uid_, const std::string& name_, const std::function<void(const nx::Event&)>& callback_)
		: uid(uid_), name(name_), callback(callback_) {}

		uint32_t uid;
		std::string name;
		std::function<void(const nx::Event&)> callback;
	};

	class SystemTpl
	{
	public:
		SystemTpl(const std::string& name, nx::Engine& engine);
		virtual ~SystemTpl();

	public:
		virtual void				update(void) = 0;
		virtual void				init(void) = 0;
		virtual bool				checkIntegrity(void) const = 0;
		virtual const std::string&	getName(void) const;
		virtual const nx::Engine&	getEngine() const;

	public:
		virtual void emitter(const nx::Event&);
		virtual uint32_t connect(const std::string& eventName, const std::function<void(const nx::Event&)>& callback);
		virtual bool disconnect(const uint32_t uid);


	protected:
		std::vector<nx::EventLink>	_links;
		nx::Engine&					_engine;
		const std::string			_name;
		uint32_t																	_maxConnectID;
	};
}

#endif // NEXUS_ENGINE__SYSTEM_TPL_HPP_
