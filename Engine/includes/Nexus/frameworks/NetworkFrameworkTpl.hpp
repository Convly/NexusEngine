#ifndef NETWORK_FRAMEWORK_TEMPLATE_HPP_
# define NETWORK_FRAMEWORK_TEMPLATE_HPP_

#include <iostream>

namespace nx {
class NetworkFrameworkTpl {
 protected:
  const std::string _name;

 public:
  // This method must be implemented this way
  NetworkFrameworkTpl(const std::string &name) : _name(name) {};
  // This method must be implemented this way
  virtual ~NetworkFrameworkTpl() {};
  // This method must be implemented this way
  const std::string &getName(void) const { return this->_name; }

  // Framework Methods (must be virtual pure)
  virtual void waitClient(unsigned int port) = 0;

  virtual void connect(std::string ip, unsigned int port) = 0;
};
}

#endif /* NETWORK_FRAMEWORK_TEMPLATE_HPP_*/