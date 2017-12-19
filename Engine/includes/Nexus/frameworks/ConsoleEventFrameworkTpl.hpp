#ifndef CONSOLEEVENT_FRAMEWORK_TEMPLATE_HPP_
# define CONSOLEEVENT_FRAMEWORK_TEMPLATE_HPP_

#include <iostream>

namespace nx {
class ConsoleEventFrameworkTpl {
 protected:
  const std::string _name;

 public:
  // This method must be implemented this way
  ConsoleEventFrameworkTpl(const std::string &name) : _name(name) {};
  // This method must be implemented this way
  virtual ~ConsoleEventFrameworkTpl() {};
  // This method must be implemented this way
  const std::string &getName(void) const { return this->_name; }

  // Framework Methods (must be virtual pure)
  virtual void TriggerConsoleEventEvent() = 0;

};
}

#endif /* CONSOLEEVENT_FRAMEWORK_TEMPLATE_HPP_*/