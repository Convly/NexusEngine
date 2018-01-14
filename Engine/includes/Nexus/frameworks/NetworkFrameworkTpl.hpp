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
  virtual void tcpStartAccept(unsigned short port) = 0;

  virtual void tcpStartConnect(std::string ip, unsigned short port) = 0;

  virtual void tcpSend(unsigned int id, Event event) = 0;
  
  virtual void udpReceive(unsigned short port) = 0;
  
  virtual void udpSend(const std::string &ip, unsigned short port, Event event) = 0;
};
}

#endif /* NETWORK_FRAMEWORK_TEMPLATE_HPP_*/