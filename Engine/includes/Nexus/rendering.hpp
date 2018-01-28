#ifndef NEXUS_ENGINE__RENDERING_SYSTEM_HPP_
#define NEXUS_ENGINE__RENDERING_SYSTEM_HPP_

#include <iostream>
#include <memory>

#include "Nexus/systems/SystemTpl.hpp"
#include "Nexus/frameworks/RenderingFrameworkTpl.hpp"

namespace nx {
	template <typename T>
	class FrameworkManager;
}

namespace nx {
	class RenderingSystem : public SystemTpl
	{
		# define __NX_RENDERING_KEY__ "rendering"

	private:
		std::shared_ptr<FrameworkManager<nx::rendering::RenderingFrameworkTpl>>	_framework_m;

	public:
		RenderingSystem();
		virtual ~RenderingSystem();

	public:
		void update();
		void init();
		bool checkIntegrity() const;
		nx::rendering::RenderingFrameworkTpl* getFramework();

	public:
		static void event_RenderingEventKey(const nx::Event&);
	};
}

#endif
