#ifndef NEXUS_ENGINE__SCRIPT_SYSTEM_HPP_
#define NEXUS_ENGINE__SCRIPT_SYSTEM_HPP_

#include <iostream>
#include <memory>

#include "Nexus/systems/SystemTpl.hpp"
#include "Nexus/frameworks/ScriptFrameworkTpl.hpp"

namespace nx {
	template <typename T>
	class FrameworkManager;
}

namespace nx {
	class ScriptSystem : public SystemTpl
	{
		# define __NX_SCRIPT_KEY__ "script"

	private:
		std::shared_ptr<FrameworkManager<nx::ScriptFrameworkTpl>>	_framework_m;

	public:
		ScriptSystem();
		virtual ~ScriptSystem();

	public:
		void update();
		void init();
		bool checkIntegrity() const;
		nx::ScriptFrameworkTpl* getFramework();

	public:
		static void event_ScriptRun(const nx::Event&);
		static void event_ScriptLoad(const nx::Event&);
		static void event_ScriptInit(const nx::Event&);
		static void event_ScriptUpdate(const nx::Event&);
	};
}

#endif
