#ifndef FRAMEWORK_NETWORK
# define FRAMEWORK_NETWORK

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <memory>

#include <thread>
#include <atomic>

#include "Nexus/engine.hpp"
#include "Nexus/frameworks/NetworkFrameworkTpl.hpp"

class FrameworkNetwork : public nx::NetworkFrameworkTpl {
 public:
  enum class Transport {
	TCP = 0,
	UDP = 1
  };

 private:
  std::shared_ptr<std::thread>	_thListenData;
  std::atomic<bool>				_stopListen;

 public:
  FrameworkNetwork(nx::Engine *);
  ~FrameworkNetwork();

 public:
  // Server

  /**
   * @attention TCP Only
   */
  void waitClient(unsigned int port);

  void waitData(unsigned int port);

  void addClient();

  // Client

  /**
   * @attention TCP Only
   */
  void connect(std::string ip, unsigned int port);

 protected:
  nx::Engine *_engine;
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
