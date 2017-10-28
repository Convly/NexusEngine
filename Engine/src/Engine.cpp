#include "Nexus/engine.hpp"
#include "Nexus/log.hpp"

nx::Engine::Engine(const bool debug)
:
	_run(false),
	_debug(debug),
	_systems({
		std::make_shared<nx::gui::GUISystem>()
	})
{
	if (this->_debug)
		nx::Log::debug("Nexus Engine successfully created!");
}

nx::Engine::~Engine()
{
	if (this->_debug)
		nx::Log::debug("Nexus Engine successfully destroyed!");
}

/* GETTERS */

bool nx::Engine::debug() const
{
	return this->_debug;
}

const std::vector<std::shared_ptr<nx::SystemTpl>>& nx::Engine::getSystems() const
{
	return this->_systems;
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

int nx::Engine::run(const std::function<void(void)>& userCallback) {
	if (!(this->_run)) {
		throw nx::RunWithoutSetupException();
	}

	while (this->_run) {
		for (auto system : this->_systems) {
			nx::Log::debug("Calling update for " + system->getName());
			system->update();
		}
		userCallback();
	}
	return (0);
}