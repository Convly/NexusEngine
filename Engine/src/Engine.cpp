#include "Nexus/engine.hpp"
#include "Nexus/log.hpp"
#include "Nexus/rendering.hpp"

nx::Engine nx::Engine::_instance = nx::Engine();

nx::Engine&  				nx::Engine::Instance()
{
	return nx::Engine::_instance;
}

nx::Engine::Engine(const bool debug)
:
	_run(false),
	_debug(debug)
{

}

nx::Engine::~Engine()
{
}

/* GETTERS */

bool nx::Engine::isSetup(void) const
{
	return this->_run;
}

bool nx::Engine::debug() const
{
	return this->_debug;
}

const std::vector<std::shared_ptr<nx::SystemTpl>>& nx::Engine::getSystems() const
{
	return this->_systems;
}

const std::shared_ptr<nx::SystemTpl>& nx::Engine::getSystemByName(const std::string& name) const
{
	auto it = std::find_if(
		this->_systems.begin(),
		this->_systems.end(),
		[&](const auto system){
			return system->getName() == name;
		}
	);
	if (it == this->_systems.end()) {
		throw nx::SystemNotFoundException(name);
	}
	return *it;
}

/* SETTERS */

void nx::Engine::setDebugFlag(const bool debugFlag)
{
	this->_debug = debugFlag;
}

/* TOOLS */

bool nx::Engine::ping() const
{
	bool ret = this->checkEngineIntegrity();

	if (ret) nx::Log::inform("Pong, the engine is valid");
	else nx::Log::warning("The engine may be compromised", "INTEGRITY_CHECK");

	return ret;
}

bool nx::Engine::checkEngineIntegrity() const
{
	bool systemState, ret = true;

	for (auto system : this->_systems) {
		ret = ret && (systemState = system->checkIntegrity());
		if (this->_debug)
			nx::Log::debug("State for " + system->getName() + " system is: " + std::to_string(systemState));
	}

	return ret;
}

/* MAIN */

void nx::Engine::setup(const std::string& confPath, bool serverOnly)
{
	 this->_systems = 
	 {
	 	std::make_shared<nx::ScriptSystem>()
	 };
	 if (!serverOnly)
	 	this->_systems.push_back(std::make_shared<nx::RenderingSystem>());

	 for (auto system : this->_systems) {
	 	system->init();
	 }

	 this->_run = this->checkEngineIntegrity();

	nx::GameInfosParser confParser(confPath);

	confParser.dump();
	std::string error;
	if (!nx::xml::Parser::fillEnvironment(this->_env, confParser)){
		std::cerr << "Error: xmlParser please look at the logs" << std::endl;
		// Stop the program
		return;
	}
	this->loadResources();
}

void nx::Engine::loadResources(){
	for (auto scene : this->_env.getScenes()){
		for (auto script : scene.getScriptComponents()){
			// this->emit(nx::EVENT::SCRIPT_LOAD, this->_env.getGameInfos().getRootPath() + script.getScriptPath());
		}
		for (auto gameObject : scene.getGameObjects()){
			// this->emit(nx::EVENT::SCRIPT_LOAD, this->_env.getGameInfos().getRootPath() + gameObject.getScriptComponent().getScriptPath());
		}
	}
}

void nx::Engine::stop() {
	this->_run = false;
}

int nx::Engine::run(const std::function<void(void)>& userCallback) {
	if (!(this->_run)) {
		throw nx::RunWithoutSetupException();
	}

	while (this->_run) {
		for (auto system : this->_systems) {
			system->update();
		}
		userCallback();
	}
	return (0);
}

nx::env::Environment &nx::Engine::getEnv() {
    return _env;
}

const nx::env::Environment &nx::Engine::getEnv() const {
	return _env;
}

