#ifndef NEXUS_ENGINE__RENDERING_SYSTEM_HPP_
#define NEXUS_ENGINE__RENDERING_SYSTEM_HPP_

#include <iostream>
#include <memory>

#include "Nexus/systems/SystemTpl.hpp"
#include "Nexus/frameworks/FrameworkManager.hpp"
#include "Nexus/frameworks/RenderingFrameworkTpl.hpp"

namespace nx {
	class RenderingSystem : public SystemTpl
	{
		# define __NX_RENDERING_KEY__ "rendering"

	private:
		FrameworkManager<nx::RenderingFrameworkTpl>	_framework_m;

	public:
		RenderingSystem();
		virtual ~RenderingSystem();

	public:
		void update();
		void init();
		bool checkIntegrity() const;
		nx::RenderingFrameworkTpl* getFramework();

	public:
		static void event_RenderingEventKey(const nx::Event&);
	};
}

#endif
