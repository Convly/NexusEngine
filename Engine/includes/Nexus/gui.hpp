#ifndef NEXUS_ENGINE__GUI_SYSTEM_HPP_
#define NEXUS_ENGINE__GUI_SYSTEM_HPP_

#include <iostream>
#include <memory>

#include "Nexus/systems/SystemTpl.hpp"
#include "Nexus/frameworks/FrameworkManager.hpp"
#include "Nexus/frameworks/guiFrameworkTpl.hpp"

namespace nx {
	class GUISystem : public SystemTpl
	{
	private:
		FrameworkManager<nx::GuiFrameworkTpl>	_framework_m;

	public:
		GUISystem();
		virtual ~GUISystem();

	public:
		void update();
		void init();
		bool checkIntegrity() const;
		nx::GuiFrameworkTpl* getFramework();

	public:
		static nx::GUISystem* cast(const std::shared_ptr<nx::SystemTpl>&);
	};
}

#endif
