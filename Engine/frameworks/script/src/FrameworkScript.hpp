#ifndef FRAMEWORK_SCRIPT
# define FRAMEWORK_SCRIPT

#include <unordered_map>
#include <string>

extern "C"
{
	#include <lua5.1/lua.h>
	#include <lua5.1/lauxlib.h>
	#include <lua5.1/lualib.h>
}

#include "LuaBridge/LuaBridge.h"

#include "Nexus/engine.hpp"
#include "Nexus/log.hpp"
#include "Nexus/frameworks/ScriptFrameworkTpl.hpp"
#include "Nexus/errors/ScriptNotLoadedException.hpp"

class FrameworkScript : public nx::ScriptFrameworkTpl
{
public:
	FrameworkScript(nx::Engine*);
	~FrameworkScript();

private:
	lua_State *createThread();
	void execMethod(const std::string&, const std::string&);

public:
	void runFile(const std::string& scriptPath);
	void loadFile(const std::string& scriptPath);
	void update(const std::string& scriptPath);
	void init(const std::string& scriptPath);
	

private:
	lua_State*										_state;
	std::unordered_map<std::string, lua_State*>		_scripts;
	
protected:
	nx::Engine* _engine;
};

#if  defined(_MSC_VER)

extern "C"
{
	__declspec(dllexport) FrameworkScript* CObject(nx::Engine* engine)
	{
		return (new FrameworkScript(engine));
	}

	__declspec(dllexport) void DObject(FrameworkScript* obj)
	{
		delete obj;
	}
}

#elif defined(__GNUC__) || defined(__GNUG__)

extern "C"
{
	FrameworkScript* CObject(nx::Engine* engine)
	{
		return (new FrameworkScript(engine));
	}

	void DObject(FrameworkScript* obj)
	{
		delete obj;
	}
}

#endif

#endif
