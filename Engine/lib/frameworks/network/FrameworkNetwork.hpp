#ifndef FRAMEWORK_NETWORK
# define FRAMEWORK_NETWORK

#include "Nexus/engine.hpp"
#include "Nexus/frameworks/NetworkFrameworkTpl.hpp"

class FrameworkNetwork : public nx::NetworkFrameworkTpl {
 public:
  enum class Transport {
	TCP = 0,
	UDP = 1
  };

 public:
  FrameworkNetwork(nx::Engine *);
  ~FrameworkNetwork();

 public:
  void TriggerNetworkEvent();

  // Server

  /**
   * @attention TCP Only
   */
  void listen(std::string port);

  // Client

  /**
   * @attention TCP Only
   */
  void connect(std::string ip, std::string port);

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
