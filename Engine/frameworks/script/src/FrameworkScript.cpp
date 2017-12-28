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
	lua_State* s = this->createThread();
	luaL_dofile(s, scriptPath.c_str());
	this->_scripts[scriptPath] = s;
}

void FrameworkScript::execMethod(const std::string& scriptPath, const std::string& methodName)
{
	if (this->_scripts.find(scriptPath) == this->_scripts.end()) {
		throw nx::ScriptNotLoaded(scriptPath);
	}

	luaL_dofile(this->_scripts[scriptPath], scriptPath.c_str());	
	luabridge::getGlobal(this->_scripts[scriptPath], methodName)();
}

void FrameworkScript::init(const std::string& scriptPath)
{
	this->execMethod(scriptPath, "Init");
}

void FrameworkScript::update(const std::string& scriptPath)
{
	this->execMethod(scriptPath, "Update");	
}