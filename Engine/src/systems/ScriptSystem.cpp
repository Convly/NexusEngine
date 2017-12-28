#include "Nexus/script.hpp"
#include "Nexus/engine.hpp"
#include "Nexus/frameworks/FrameworkManager.hpp"

nx::ScriptSystem::ScriptSystem()
:
	nx::SystemTpl(__NX_SCRIPT_KEY__),
	_framework_m(std::make_shared<nx::FrameworkManager<nx::ScriptFrameworkTpl>>(__NX_SCRIPT_KEY__, true))
{
	this->connect("SCRIPT_RUN", nx::ScriptSystem::event_ScriptRun);
}

nx::ScriptSystem::~ScriptSystem() {

}

 nx::ScriptFrameworkTpl* nx::ScriptSystem::getFramework()
{
	return this->_framework_m->getFramework();
}

void nx::ScriptSystem::init()
{
	
}

void nx::ScriptSystem::update()
{

}

bool nx::ScriptSystem::checkIntegrity() const
{
	if (this->_framework_m->getFramework()) {
		return true;
	}
	return false;
}

void nx::ScriptSystem::event_ScriptRun(const nx::Event& e)
{
	auto& engine = nx::Engine::Instance();
	auto self = nx::Engine::cast<nx::ScriptSystem>(engine.getSystemByName(__NX_SCRIPT_KEY__));
	if (!self) return;
	
	auto f = self->getFramework();
	if (!f)
		nx::Log::warning("Script framework is corrupted", "SCRIPT_INTEGRITY");
	else
		f->runFile(e.data.data());
}