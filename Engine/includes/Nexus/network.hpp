#ifndef NEXUS_ENGINE__NETWORK_SYSTEM_HPP_
#define NEXUS_ENGINE__NETWORK_SYSTEM_HPP_

#include <iostream>
#include <memory>
#include <future>

#include "Nexus/systems/SystemTpl.hpp"
#include "Nexus/frameworks/NetworkFrameworkTpl.hpp"

namespace nx {
template<typename T>
class FrameworkManager;
}

namespace nx {
class NetworkSystem : public SystemTpl {
# define __NX_NETWORK_KEY__ "network"

 private:
  std::shared_ptr<FrameworkManager<nx::NetworkFrameworkTpl>> _framework_m;

 public:
  NetworkSystem();
  virtual ~NetworkSystem();

 public:
  struct TcpConnectEvent {
	std::string		_ip;
	unsigned short	_port;
  };

  struct TcpAcceptEvent {
	bool 			_localhost;
	unsigned short	_port;
  };

  struct TcpSendEvent {
	unsigned int		id;
	nx::Event 			&event;
  };

  struct UdpSendEvent {
	  std::string		_ip;
	  unsigned int		_port;
	  nx::Event			&_event;
  };

  struct UdpReceiveEvent {
	  unsigned int		_port;
  };

 public:
  void update();
  void init();
  bool checkIntegrity() const;
  nx::NetworkFrameworkTpl *getFramework();

 public:
  static void event_NetworkTcpAccept(const nx::Event &);
  static void event_NetworkTcpConnect(const nx::Event &);
  static void event_NetworkTcpSend(const nx::Event &);
  static void event_NetworkUdpReceive(const nx::Event &);
  static void event_NetworkUdpSend(const nx::Event &);
};
}

#endif
