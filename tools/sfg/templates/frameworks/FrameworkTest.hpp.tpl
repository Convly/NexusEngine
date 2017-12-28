#ifndef FRAMEWORK_${__NX_UPPER_SYSTEM__}
# define FRAMEWORK_${__NX_UPPER_SYSTEM__}

#include "Nexus/engine.hpp"
#include "Nexus/log.hpp"
#include "Nexus/frameworks/${__NX_BASE_SYSTEM__}FrameworkTpl.hpp"

class Framework${__NX_BASE_SYSTEM__} : public nx::${__NX_BASE_SYSTEM__}FrameworkTpl
{
public:
	Framework${__NX_BASE_SYSTEM__}(nx::Engine*);
	~Framework${__NX_BASE_SYSTEM__}();

public:
	void ping${__NX_BASE_SYSTEM__}Framework();

	
protected:
	nx::Engine* _engine;
};

#if  defined(_MSC_VER)

extern "C"
{
	__declspec(dllexport) Framework${__NX_BASE_SYSTEM__}* CObject(nx::Engine* engine)
	{
		return (new Framework${__NX_BASE_SYSTEM__}(engine));
	}

	__declspec(dllexport) void DObject(Framework${__NX_BASE_SYSTEM__}* obj)
	{
		delete obj;
	}
}

#elif defined(__GNUC__) || defined(__GNUG__)

extern "C"
{
	Framework${__NX_BASE_SYSTEM__}* CObject(nx::Engine* engine)
	{
		return (new Framework${__NX_BASE_SYSTEM__}(engine));
	}

	void DObject(Framework${__NX_BASE_SYSTEM__}* obj)
	{
		delete obj;
	}
}

#endif

#endif
