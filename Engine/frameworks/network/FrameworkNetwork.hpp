#ifndef FRAMEWORK_NETWORK
# define FRAMEWORK_NETWORK

#include "Nexus/engine.hpp"
#include "Nexus/log.hpp"
#include "Nexus/frameworks/NetworkFrameworkTpl.hpp"

class FrameworkNetwork : public nx::NetworkFrameworkTpl
{
public:
	FrameworkNetwork(nx::Engine*);
	~FrameworkNetwork();

public:
	void pingNetworkFramework();

	
protected:
	nx::Engine* _engine;
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
	FrameworkNetwork* CObject(nx::Engine* engine)
	{
		return (new FrameworkNetwork(engine));
	}

	void DObject(FrameworkNetwork* obj)
	{
		delete obj;
	}
}

#endif

#endif
