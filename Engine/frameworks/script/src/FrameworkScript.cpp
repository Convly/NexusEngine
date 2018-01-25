#include "FrameworkScript.hpp"

FrameworkScript::FrameworkScript(nx::Engine* engine)
:
	nx::ScriptFrameworkTpl("FrameworkScript"),
	_engine(engine)
{
	_state = luaL_newstate();
	luaL_openlibs(_state);
    registerEnv();
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

void FrameworkScript::registerEnv() {
    luabridge::getGlobalNamespace(_state)
            .beginClass<nx::env::EntityInfos>("EntityInfos")
            .addConstructor<void(*)(void)>()
            .addConstructor<void(*)(std::string const&)>()
            .addConstructor<void(*)(std::string const &, bool const)>()
            .addConstructor<void(*)(const nx::env::EntityInfos &)>()
            .addFunction("setName", &nx::env::EntityInfos::setName)
            .addFunction("setActive", &nx::env::EntityInfos::setActive)
            .addFunction("getName", &nx::env::EntityInfos::getName)
            .addFunction("getActive", &nx::env::EntityInfos::getActive)
            .endClass()
            .beginClass<nx::env::ScriptComponent>("ScriptComponent")
            .addConstructor<void(*)(std::string const&)>()
            .addConstructor<void(*)(std::string const &, std::string const&)>()
            .addFunction("setScriptPath", &nx::env::ScriptComponent::setScriptPath)
            .addFunction("getScriptPath", &nx::env::ScriptComponent::getScriptPath)
            .endClass()
            .beginClass<std::vector<nx::env::ScriptComponent> > ("SceneVector")
            .addFunction("size", &std::vector<nx::env::ScriptComponent>::size)
            .addFunction<std::vector<nx::env::ScriptComponent>::reference (std::vector<nx::env::ScriptComponent>::*)(std::vector<nx::env::ScriptComponent>::size_type)>("at", &std::vector<nx::env::ScriptComponent>::at)
            .endClass()
            .beginClass<nx::env::RGBa>("RGBa")
            .addConstructor<void(*)(void)>()
            .addConstructor<void(*)(const uint32_t, const uint32_t, const uint32_t, const uint32_t)>()
            .addConstructor<void(*)(const nx::env::RGBa &)>()
            .addFunction("setRed", &nx::env::RGBa::setRed)
            .addFunction("getRed", &nx::env::RGBa::getRed)
            .addFunction("setGreen", &nx::env::RGBa::setGreen)
            .addFunction("setGreen", &nx::env::RGBa::getGreen)
            .addFunction("setBlue", &nx::env::RGBa::setBlue)
            .addFunction("setBlue", &nx::env::RGBa::getBlue)
            .addFunction("setAlpha", &nx::env::RGBa::setAlpha)
            .addFunction("setAlpha", &nx::env::RGBa::getAlpha)
            .endClass()
            .beginClass<nx::env::GameInfos>("GameInfos")
            .addConstructor<void(*)(void)>()
            .endClass()
            .beginClass<std::vector<std::string> > ("StringVector")
            .addFunction("size", &std::vector<std::string>::size)
            .addFunction<std::vector<std::string>::reference (std::vector<std::string>::*)(std::vector<std::string>::size_type)>("at", &std::vector<std::string>::at)
            .endClass()
            .beginClass<nx::env::Ressources>("Ressources")
            .addConstructor<void(*)(void)>()
            .addData("_imagePath", &nx::env::Ressources::_imagePaths)
            .addFunction("addSoundPath", &nx::env::Ressources::addSoundPath)
            .addFunction("addMusicPath", &nx::env::Ressources::addMusicPath)
            .addFunction("addImagePath", &nx::env::Ressources::addImagePath)
            .addFunction("addScriptPath", &nx::env::Ressources::addScriptPath)
            .addFunction("getSoundPathAt", &nx::env::Ressources::getSoundPathAt)
            .addFunction("getMusicPathAt", &nx::env::Ressources::getMusicPathAt)
            .addFunction("getImagePathAt", &nx::env::Ressources::getImagePathAt)
            .addFunction("getScriptPathAt", &nx::env::Ressources::getScriptPathAt)
            .endClass()
            //.beginClass<std::vector<nx::env::Scene> > ("SceneVector")
            //.addFunction("size", &std::vector<nx::env::Scene>::size)
            //.addFunction<std::vector<nx::env::Scene>::reference (std::vector<nx::env::Scene>::*)(std::vector<nx::env::Scene>::size_type)>("at", &std::vector<nx::env::Scene>::at)
            //.endClass()

            // Scene
            //.beginClass<nx::env::Scene>("Scene")
            //.endClass()
            //Environment
            .beginClass<nx::env::Environment>("Environment")
            .addConstructor<void(*)(void)>()
            .addFunction("addScene", &nx::env::Environment::addScene)
            .addFunction("getScenes", &nx::env::Environment::getScenes)
            .addFunction("getRessources", &nx::env::Environment::getRessources)
            .addFunction("getGameInfos", &nx::env::Environment::getGameInfos)
            .endClass();
    luabridge::push(_state, &_engine->getEnv());
    lua_setglobal(_state, "Env");
}

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
	this->execMethod(scriptPath, "Init");
}

void FrameworkScript::update(const std::string& scriptPath)
{
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
