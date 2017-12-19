#ifndef FRAMEWORK_CONSOLEEVENT
# define FRAMEWORK_CONSOLEEVENT

#include <thread>

#include "Nexus/engine.hpp"
#include "Nexus/frameworks/ConsoleEventFrameworkTpl.hpp"

class FrameworkConsoleEvent : public nx::ConsoleEventFrameworkTpl {
 public:
  FrameworkConsoleEvent(nx::Engine *);
  ~FrameworkConsoleEvent();

 private:
  std::thread _thread;

 public:
  void start();
  void runEvent(std::string event);

 protected:
  nx::Engine *_engine;
};

#if  defined(_MSC_VER)

extern "C"
{
	__declspec(dllexport) FrameworkConsoleEvent* CObject(nx::Engine* engine)
	{
		return (new FrameworkConsoleEvent(engine));
	}

	__declspec(dllexport) void DObject(FrameworkConsoleEvent* obj)
	{
		delete obj;
	}
}

#elif defined(__GNUC__) || defined(__GNUG__)

extern "C"
{
FrameworkConsoleEvent *CObject(nx::Engine *engine) {
  return (new FrameworkConsoleEvent(engine));
}

void DObject(FrameworkConsoleEvent *obj) {
  delete obj;
}
}

#endif

#endif
