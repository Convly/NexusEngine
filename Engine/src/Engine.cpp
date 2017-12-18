#include "Nexus/engine.hpp"
#include "Nexus/log.hpp"

nx::Engine nx::Engine::_instance = nx::Engine();

nx::Engine&  				nx::Engine::Instance()
{
	return nx::Engine::_instance;
}

nx::Engine::Engine(const bool debug)
:
	_run(false),
	_debug(debug),
	_systems({
		/* std::make_shared<nx::XxxSystem>() */
	})
{
	for (auto system : this->_systems) {
		system->init();
	}
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

void nx::Engine::setup() {
	this->_run = this->checkEngineIntegrity();
}

void nx::Engine::stop() {
	this->_run = false;
}

void nx::Engine::emit(const std::string& name, const std::string& data)
{
	this->emit(nx::Event(name, data));
}

void nx::Engine::emit(const nx::Event& event)
{
	nx::Log::inform("New event catched in the Engine: {" + event.name + ", " + event.data + "}");
	std::for_each(
		this->_systems.begin(),
		this->_systems.end(),
		[&](const auto system){
			system->emitter(event);
		}
	);
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