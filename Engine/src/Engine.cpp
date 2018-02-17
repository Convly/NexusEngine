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

const bool nx::Engine::isServer() const
{
	return this->_serverOnly;
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
	bool ret = true;

	for (auto system : this->_systems) {
		bool systemState;
		ret = ret && (systemState = system->checkIntegrity());
		if (this->_debug)
			nx::Log::debug("State for " + system->getName() + " system is: " + std::to_string(systemState));
	}

	return ret;
}

/* MAIN */

void nx::Engine::setup(const std::string& confPath, bool serverOnly)
{
	if (serverOnly) {
		this->_systems = {
			std::make_shared<nx::ScriptSystem>(),
			std::make_shared<nx::NetworkServerSystem>()
		};	
	} else {
		this->_systems = {
			std::make_shared<nx::ScriptSystem>(),
			std::make_shared<nx::NetworkClientSystem>(),
			std::make_shared<nx::RenderingSystem>()
		};
	}

	this->_serverOnly = serverOnly;

	_gameInfosParser = std::make_shared<nx::GameInfosParser>(confPath);

	_gameInfosParser->dump();
	if (!nx::xml::Parser::fillEnvironment(this->_env, *_gameInfosParser)){
		std::cerr << "Error: xmlParser please look at the logs" << std::endl;
		//return;
	}

	this->_run = this->checkEngineIntegrity();
	this->loadResources();
}

void nx::Engine::loadResources()
{
	for (auto& scene : this->_env.getScenes()){
		for (auto& script : scene.getScriptComponents()){
			this->emit(nx::EVENT::SCRIPT_LOAD, script.getScriptPath());
		}
		for (auto& gameObject : scene.getGameObjects()){
			this->emit(nx::EVENT::SCRIPT_LOAD, gameObject.getScriptComponent().getScriptPath());
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

	for (auto& system : this->_systems) {
		system->init();
	}

	if (this->isServer())
		this->coreLoop(userCallback);
	else
		this->getSystemByName("rendering")->update();

	_systems.clear();
	return (0);
}

void nx::Engine::coreLoop(const std::function<void(void)>& userCallback)
{
	auto serverFramework = cast<nx::NetworkServerSystem>(getSystemByName(__NX_NETWORKSERVER_KEY__))->getFramework();
	if (!serverFramework)
	{
		nx::Log::warning("NetworkServer framework is corrupted, exiting...", "SERVER_INTEGRITY");
		return;
	}

	while (this->_run)
	{
		if (!serverFramework->isServerFull())
			continue;

		this->_fixedUpdate();
		this->_update();
		userCallback();
		this->_lateUpdate();
		this->_render();
	}
}

void	nx::Engine::fixUpdateScript(const std::string& fctName){
	for (auto& scene : getEnv().getScenes()){
		for (auto& script : scene.getScriptComponents()){
			this->emit(nx::EVENT::SCRIPT_EXEC_FUNCTION, nx::script::ScriptInfos(script.getScriptPath(), fctName, false));
		}
		for (auto& gameObject : scene.getGameObjects()){
			this->emit(nx::EVENT::SCRIPT_EXEC_FUNCTION, nx::script::ScriptInfos(gameObject.getScriptComponent().getScriptPath(), fctName, false));
		}
	}	
}

void	nx::Engine::_fixedUpdate()
{
	fixUpdateScript("FixedUpdate");
	// Boucler sur tout
	// Calculer la physique
	// this->emit(nx::EVENT::SCRIPT_EXEC_FUNCTION, nx::script::ScriptInfos("[nom_fichier]", "FixedUpdate"));
}

void	nx::Engine::_update()
{
	fixUpdateScript("Update");
	// Boucler sur tout
	// this->emit(nx::EVENT::SCRIPT_EXEC_FUNCTION, nx::script::ScriptInfos("[nom_fichier]", "Update"));
}

void	nx::Engine::_lateUpdate()
{
	fixUpdateScript("LateUpdate");
	// Boucler sur tout
	// this->emit(nx::EVENT::SCRIPT_EXEC_FUNCTION, nx::script::ScriptInfos("[nom_fichier]", "LateUpdate"));
}

void	nx::Engine::_render()
{
	for (auto& scene : getEnv().getScenes()){
		if (scene.isModified()){
			std::cout << scene.getEntityInfos().getName() << " need to be send !!!" << std::endl;
			emit(nx::EVENT::ENV_UPDATE_SCENE, scene);

			scene.resetModified();
		}
	}
}
