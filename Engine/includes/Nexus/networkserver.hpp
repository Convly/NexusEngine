#ifndef NEXUS_ENGINE__NETWORKSERVER_SYSTEM_HPP_
#define NEXUS_ENGINE__NETWORKSERVER_SYSTEM_HPP_

#include <iostream>
#include <memory>

#include "Nexus/engine.hpp"
#include "Nexus/systems/SystemTpl.hpp"
#include "Nexus/frameworks/NetworkServerFrameworkTpl.hpp"

namespace nx {
	template <typename T>
	class FrameworkManager;
}

namespace nx {
	class NetworkServerSystem : public SystemTpl
	{
		# define __NX_NETWORKSERVER_KEY__ "networkserver"

	private:
		std::shared_ptr<FrameworkManager<nx::NetworkServerFrameworkTpl>>	_framework_m;

	public:
		NetworkServerSystem();
		virtual ~NetworkServerSystem();

	public:
		void update();
		void init();
		bool checkIntegrity() const;
		nx::NetworkServerFrameworkTpl* getFramework();

	public:
		static void event_Send(const nx::Event& e);
		static void event_SendAll(const nx::Event& e);
		static void event_Disconnect(const nx::Event& e);
		static void event_Connect(const nx::Event&);
	};
}

#endif
