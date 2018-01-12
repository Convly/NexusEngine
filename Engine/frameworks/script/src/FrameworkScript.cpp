#include "FrameworkScript.hpp"

FrameworkScript::FrameworkScript(nx::Engine* engine)
:
	nx::ScriptFrameworkTpl("FrameworkScript"),
	_engine(engine)
{
	_state = luaL_newstate();
	luaL_openlibs(_state);
}

FrameworkScript::~FrameworkScript() {}

lua_State* FrameworkScript::createThread()
{
    lua_State *thread = lua_newthread(_state);

	lua_newtable(thread);
    lua_newtable(thread);
    lua_pushliteral(thread, "__index");
    lua_pushvalue(thread, LUA_GLOBALSINDEX);
    lua_settable(thread, -3);
    lua_setmetatable(thread, -2);
    lua_replace(thread, LUA_GLOBALSINDEX);
     
    return thread;
};

void FrameworkScript::runFile(const std::string& scriptPath)
{
	lua_State* s = this->createThread();
	luaL_dofile(s, scriptPath.c_str());
}

void FrameworkScript::loadFile(const std::string& scriptPath)
{
	if (this->_scripts.find(scriptPath) != this->_scripts.end())
	{
		nx::Log::inform("Script '" + scriptPath + "' already loaded");
		return;
	}

	lua_State* s = this->createThread();
	if (luaL_dofile(s, scriptPath.c_str())) {
		nx::Log::error(scriptPath + " doesn't exists in you env", "BAD_FILE", 549);		
		return;
	}
	this->_scripts[scriptPath] = s;
}

void FrameworkScript::execMethod(const std::string& scriptPath, const std::string& methodName)
{
	if (this->_scripts.find(scriptPath) == this->_scripts.end()) {
		throw nx::ScriptNotLoaded(scriptPath);
	}

	if (!luaL_dofile(this->_scripts[scriptPath], scriptPath.c_str())) {
		try {
			luabridge::getGlobal(this->_scripts[scriptPath], methodName.c_str())();
		} catch (const luabridge::LuaException& e) {
			nx::Log::error(e.what(), "BAD_LUA", 550);
		}
	} else {
		nx::Log::error(scriptPath + " doesn't exists in you env", "BAD_FILE", 549);
	}
}

void FrameworkScript::init(const std::string& scriptPath)
{
	if (this->_scripts.find(scriptPath) == this->_scripts.end()) {
		throw nx::ScriptNotLoaded(scriptPath);
	}

	this->execMethod(scriptPath, "Init");
}

void FrameworkScript::update(const std::string& scriptPath)
{
	if (this->_scripts.find(scriptPath) == this->_scripts.end()) {
		throw nx::ScriptNotLoaded(scriptPath);
	}

	this->execMethod(scriptPath, "Update");	
}

void FrameworkScript::execFunction(const std::string& scriptPath, const std::string& funcName)
{
	try {
		this->execMethod(scriptPath, funcName);
	} catch (const nx::ScriptNotLoaded& e) {
		nx::Log::error(e.what(), "SCRIPT_NOT_LOADED", 404);
	}
}
