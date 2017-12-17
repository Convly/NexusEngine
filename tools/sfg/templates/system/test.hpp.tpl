#ifndef NEXUS_ENGINE__${__NX_UPPER_SYSTEM__}_SYSTEM_HPP_
#define NEXUS_ENGINE__${__NX_UPPER_SYSTEM__}_SYSTEM_HPP_

#include <iostream>
#include <memory>

#include "Nexus/systems/SystemTpl.hpp"
#include "Nexus/frameworks/${__NX_BASE_SYSTEM__}FrameworkTpl.hpp"

namespace nx {
	template <typename T>
	class FrameworkManager;
}

namespace nx {
	class ${__NX_BASE_SYSTEM__}System : public SystemTpl
	{
		# define __NX_${__NX_UPPER_SYSTEM__}_KEY__ "${__NX_LOWER_SYSTEM__}"

	private:
		std::shared_ptr<FrameworkManager<nx::${__NX_BASE_SYSTEM__}FrameworkTpl>>	_framework_m;

	public:
		${__NX_BASE_SYSTEM__}System();
		virtual ~${__NX_BASE_SYSTEM__}System();

	public:
		void update();
		void init();
		bool checkIntegrity() const;
		nx::${__NX_BASE_SYSTEM__}FrameworkTpl* getFramework();

	public:
		static void event_${__NX_BASE_SYSTEM__}EventKey(const nx::Event&);
	};
}

#endif
