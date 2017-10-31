#ifndef NEXUS_ENGINE__GUI_SYSTEM_HPP_
#define NEXUS_ENGINE__GUI_SYSTEM_HPP_

#include <iostream>
#include <memory>

#include "Nexus/systems/SystemTpl.hpp"

namespace nx {
	class GUISystem : public SystemTpl
	{
	public:
		GUISystem();
		virtual ~GUISystem();

	public:
		void update();
		void init();
		bool checkIntegrity() const;

	public:
		static nx::GUISystem* cast(const std::shared_ptr<nx::SystemTpl>&);	
	};
}

#endif
