#include "Nexus/script.hpp"
#include "Nexus/engine.hpp"
#include "Nexus/frameworks/FrameworkManager.hpp"

nx::ScriptSystem::ScriptSystem()
:
	nx::SystemTpl(__NX_SCRIPT_KEY__),
	_framework_m(std::make_shared<nx::FrameworkManager<nx::ScriptFrameworkTpl>>(__NX_SCRIPT_KEY__, true))
{
	this->connect(nx::EVENT::SCRIPT_RUN, nx::ScriptSystem::event_ScriptRun);
	this->connect(nx::EVENT::SCRIPT_LOAD, nx::ScriptSystem::event_ScriptLoad);
	this->connect(nx::EVENT::SCRIPT_INIT, nx::ScriptSystem::event_ScriptInit);
	this->connect(nx::EVENT::SCRIPT_UPDATE, nx::ScriptSystem::event_ScriptUpdate);
	this->connect(nx::EVENT::SCRIPT_EXEC_FUNCTION, nx::ScriptSystem::event_ScriptExecFunction);
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
		f->runFile(std::experimental::any_cast<std::string>(e.data));
}

void nx::ScriptSystem::event_ScriptLoad(const nx::Event& e)
{
	auto& engine = nx::Engine::Instance();
	auto self = nx::Engine::cast<nx::ScriptSystem>(engine.getSystemByName(__NX_SCRIPT_KEY__));
	if (!self) return;
	
	auto f = self->getFramework();
	if (!f)
		nx::Log::warning("Script framework is corrupted", "SCRIPT_INTEGRITY");
	else
		f->loadFile(std::experimental::any_cast<std::string>(e.data));
}

void nx::ScriptSystem::event_ScriptInit(const nx::Event& e)
{
	auto& engine = nx::Engine::Instance();
	auto self = nx::Engine::cast<nx::ScriptSystem>(engine.getSystemByName(__NX_SCRIPT_KEY__));
	if (!self) return;
	
	auto f = self->getFramework();
	if (!f)
		nx::Log::warning("Script framework is corrupted", "SCRIPT_INTEGRITY");
	else
		f->init(std::experimental::any_cast<std::string>(e.data));
}

void nx::ScriptSystem::event_ScriptUpdate(const nx::Event& e)
{
	auto& engine = nx::Engine::Instance();
	auto self = nx::Engine::cast<nx::ScriptSystem>(engine.getSystemByName(__NX_SCRIPT_KEY__));
	if (!self) return;
	
	auto f = self->getFramework();
	if (!f)
		nx::Log::warning("Script framework is corrupted", "SCRIPT_INTEGRITY");
	else
		f->update(std::experimental::any_cast<std::string>(e.data));
}

void nx::ScriptSystem::event_ScriptExecFunction(const nx::Event& e)
{
    auto& engine = nx::Engine::Instance();
	auto self = nx::Engine::cast<nx::ScriptSystem>(engine.getSystemByName(__NX_SCRIPT_KEY__));
	if (!self) return;
	auto f = self->getFramework();
	if (!f)
		nx::Log::warning("Script framework is corrupted", "SCRIPT_INTEGRITY");
	else
	{
		nx::script::ScriptInfos si = std::experimental::any_cast<nx::script::ScriptInfos>(e.data);
		f->execFunction(si.file, si.func);
	}
}