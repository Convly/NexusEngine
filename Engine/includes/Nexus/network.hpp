#ifndef NEXUS_ENGINE__NETWORK_SYSTEM_HPP_
#define NEXUS_ENGINE__NETWORK_SYSTEM_HPP_

#include <iostream>
#include <memory>

#include "Nexus/systems/SystemTpl.hpp"
#include "Nexus/frameworks/NetworkFrameworkTpl.hpp"

namespace nx {
	template <typename T>
	class FrameworkManager;
}

namespace nx {
	class NetworkSystem : public SystemTpl
	{
		# define __NX_NETWORK_KEY__ "network"

	private:
		std::shared_ptr<FrameworkManager<nx::NetworkFrameworkTpl>>	_framework_m;

	public:
		NetworkSystem();
		virtual ~NetworkSystem();

	public:
		void update();
		void init();
		bool checkIntegrity() const;
		nx::NetworkFrameworkTpl* getFramework();
	};
}

#endif
