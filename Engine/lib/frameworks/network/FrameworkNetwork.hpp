#ifndef FRAMEWORK_NETWORK
# define FRAMEWORK_NETWORK

#include <stdio.h>
#include <string.h>

#include "Nexus/engine.hpp"
#include "Nexus/frameworks/NetworkFrameworkTpl.hpp"

#include "NetworkTcp.hpp"

class FrameworkNetwork : public nx::NetworkFrameworkTpl {
 public:
  enum class Transport {
	TCP = 0,
	UDP = 1
  };

 protected:
  NetworkTcp	_tcp;


 public:
  FrameworkNetwork(nx::Engine *);
  ~FrameworkNetwork();

 protected:
  nx::Engine *_engine;

 public:
  void tcpStartAccept(unsigned short port);
  void tcpStartConnect(std::string ip, unsigned short port);
  void tcpSend(unsigned int id, nx::Event event);
};

#if  defined(_MSC_VER)

extern "C"
{
	__declspec(dllexport) FrameworkNetwork* CObject(nx::Engine* engine)
	{
		return (new FrameworkNetwork(engine));
	}

	__declspec(dllexport) void DObject(FrameworkNetwork* obj)
	{
		delete obj;
	}
}

#elif defined(__GNUC__) || defined(__GNUG__)

extern "C"
{
FrameworkNetwork *CObject(nx::Engine *engine) {
  return (new FrameworkNetwork(engine));
}

void DObject(FrameworkNetwork *obj) {
  delete obj;
}
}

#endif

#endif
