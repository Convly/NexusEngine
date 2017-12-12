//
// made by marco
//

#ifndef FRAMEWORK_UI
# define FRAMEWORK_UI

#include "Nexus/engine.hpp"
#include "Nexus/frameworks/TestFrameworkTpl.hpp"

class FrameworkTest : public nx::TestFrameworkTpl
{
public:
	FrameworkTest(nx::Engine*);
	~FrameworkTest();

public:
	void TriggerTestEvent();

	
protected:
	nx::Engine* _engine;
};

#if  defined(_MSC_VER)

extern "C"
{
	__declspec(dllexport) FrameworkTest* CObject(nx::Engine* engine)
	{
		return (new FrameworkTest(engine));
	}

	__declspec(dllexport) void DObject(FrameworkTest* obj)
	{
		delete obj;
	}
}

#elif defined(__GNUC__) || defined(__GNUG__)

extern "C"
{
	FrameworkTest* CObject(nx::Engine* engine)
	{
		return (new FrameworkTest(engine));
	}

	void DObject(FrameworkTest* obj)
	{
		delete obj;
	}
}

#endif

#endif
