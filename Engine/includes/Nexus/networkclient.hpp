#ifndef NEXUS_ENGINE__NETWORKCLIENT_SYSTEM_HPP_
#define NEXUS_ENGINE__NETWORKCLIENT_SYSTEM_HPP_

#include <iostream>
#include <memory>

#include "Nexus/systems/SystemTpl.hpp"
#include "Nexus/frameworks/NetworkClientFrameworkTpl.hpp"

namespace nx {
	template <typename T>
	class FrameworkManager;
}

namespace nx {
	class NetworkClientSystem : public SystemTpl
	{
		# define __NX_NETWORKCLIENT_KEY__ "networkclient"

	private:
		std::shared_ptr<FrameworkManager<nx::NetworkClientFrameworkTpl>>	_framework_m;

	public:
		NetworkClientSystem();
		virtual ~NetworkClientSystem();

	public:
		void update();
		void init();
		bool checkIntegrity() const;
		nx::NetworkClientFrameworkTpl* getFramework();
	};
}

#endif
