#ifndef NEXUS_ENGINE__CONSOLEEVENT_SYSTEM_HPP_
#define NEXUS_ENGINE__CONSOLEEVENT_SYSTEM_HPP_

#include <iostream>
#include <memory>

#include "Nexus/systems/SystemTpl.hpp"
#include "Nexus/frameworks/ConsoleEventFrameworkTpl.hpp"

namespace nx {
template<typename T>
class FrameworkManager;
}

namespace nx {
class ConsoleEventSystem : public SystemTpl {
# define __NX_CONSOLEEVENT_KEY__ "consoleevent"

 private:
  std::shared_ptr<FrameworkManager<nx::ConsoleEventFrameworkTpl>> _framework_m;

 public:
  ConsoleEventSystem();
  virtual ~ConsoleEventSystem();

 public:
  void update();
  void init();
  bool checkIntegrity() const;
  nx::ConsoleEventFrameworkTpl *getFramework();

 public:
  static void event_ConsoleEventEventKey(const nx::Event &);
};
}

#endif
