#ifndef FRAMEWORK_NETWORKCLIENT
# define FRAMEWORK_NETWORKCLIENT

#include "Nexus/engine.hpp"
#include "Nexus/log.hpp"
#include "Nexus/frameworks/NetworkClientFrameworkTpl.hpp"

class FrameworkNetworkClient : public nx::NetworkClientFrameworkTpl
{
public:
	FrameworkNetworkClient(nx::Engine*);
	~FrameworkNetworkClient();
	
protected:
	nx::Engine* _engine;
};

#if  defined(_MSC_VER)

extern "C"
{
	__declspec(dllexport) FrameworkNetworkClient* CObject(nx::Engine* engine)
	{
		return (new FrameworkNetworkClient(engine));
	}

	__declspec(dllexport) void DObject(FrameworkNetworkClient* obj)
	{
		delete obj;
	}
}

#elif defined(__GNUC__) || defined(__GNUG__)

extern "C"
{
	FrameworkNetworkClient* CObject(nx::Engine* engine)
	{
		return (new FrameworkNetworkClient(engine));
	}

	void DObject(FrameworkNetworkClient* obj)
	{
		delete obj;
	}
}

#endif

#endif
