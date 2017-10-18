#ifndef NEXUS_ENGINE__GUI_SYSTEM_HPP_
#define NEXUS_ENGINE__GUI_SYSTEM_HPP_

#include <iostream>

#include "Nexus/systems/SystemTpl.hpp"

namespace nx {
	namespace gui {
		class GUISystem : public SystemTpl
		{
		public:
			GUISystem();
			virtual ~GUISystem();

		public:
			void update();
			void init();
			bool checkIntegrity() const;
			const std::string& getName() const;
		};
	}
}

#endif
