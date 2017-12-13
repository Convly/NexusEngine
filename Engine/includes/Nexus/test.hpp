#ifndef NEXUS_ENGINE__TEST_SYSTEM_HPP_
#define NEXUS_ENGINE__TEST_SYSTEM_HPP_

#include <iostream>
#include <memory>

#include "Nexus/systems/SystemTpl.hpp"
#include "Nexus/frameworks/TestFrameworkTpl.hpp"

# define __SYSTEM_KEY__ "test"

namespace nx {
	template <typename T>
	class FrameworkManager;
}

namespace nx {
	class TestSystem : public SystemTpl
	{
		# define __NX_TEST_KEY__ "test"

	private:
		std::shared_ptr<FrameworkManager<nx::TestFrameworkTpl>>	_framework_m;

	public:
		TestSystem();
		virtual ~TestSystem();

	public:
		void update();
		void init();
		bool checkIntegrity() const;
		nx::TestFrameworkTpl* getFramework();

	public:
		static void event_TestEventKey(const nx::Event&);
	};
}

#endif
