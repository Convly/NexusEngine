#ifndef FRAMEWORK_NETWORKSERVER
# define FRAMEWORK_NETWORKSERVER

#include "Nexus/engine.hpp"
#include "Nexus/log.hpp"
#include "Nexus/frameworks/NetworkServerFrameworkTpl.hpp"

class FrameworkNetworkServer : public nx::NetworkServerFrameworkTpl
{
public:
	FrameworkNetworkServer(nx::Engine*);
	~FrameworkNetworkServer();

public:
	void pingNetworkServerFramework();

	
protected:
	nx::Engine* _engine;
};

#if  defined(_MSC_VER)

extern "C"
{
	__declspec(dllexport) FrameworkNetworkServer* CObject(nx::Engine* engine)
	{
		return (new FrameworkNetworkServer(engine));
	}

	__declspec(dllexport) void DObject(FrameworkNetworkServer* obj)
	{
		delete obj;
	}
}

#elif defined(__GNUC__) || defined(__GNUG__)

extern "C"
{
	FrameworkNetworkServer* CObject(nx::Engine* engine)
	{
		return (new FrameworkNetworkServer(engine));
	}

	void DObject(FrameworkNetworkServer* obj)
	{
		delete obj;
	}
}

#endif

#endif
