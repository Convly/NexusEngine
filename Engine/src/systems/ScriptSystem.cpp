#include "Nexus/script.hpp"
#include "Nexus/engine.hpp"
#include "Nexus/frameworks/FrameworkManager.hpp"

nx::ScriptSystem::ScriptSystem()
:
	nx::SystemTpl(__NX_SCRIPT_KEY__),
	_framework_m(std::make_shared<nx::FrameworkManager<nx::ScriptFrameworkTpl>>(__NX_SCRIPT_KEY__))
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
	else{
		std::string rootPath =  nx::Engine::Instance().getEnv().getGameInfos().getRootPath() + nx::Engine::Instance().getGameInfosParser()->getFields()._resources.at("scripts");
		f->runFile(rootPath + external::any_cast<std::string>(e.data));
	}
}

void nx::ScriptSystem::event_ScriptLoad(const nx::Event& e)
{
	auto& engine = nx::Engine::Instance();
	auto self = nx::Engine::cast<nx::ScriptSystem>(engine.getSystemByName(__NX_SCRIPT_KEY__));
	if (!self) return;
	
	auto f = self->getFramework();
	if (!f)
		nx::Log::warning("Script framework is corrupted", "SCRIPT_INTEGRITY");
	else{
		std::string rootPath =  nx::Engine::Instance().getEnv().getGameInfos().getRootPath() + nx::Engine::Instance().getGameInfosParser()->getFields()._resources.at("scripts");
		f->loadFile(rootPath + external::any_cast<std::string>(e.data));
	}
}

void nx::ScriptSystem::event_ScriptInit(const nx::Event& e)
{
	auto& engine = nx::Engine::Instance();
	auto self = nx::Engine::cast<nx::ScriptSystem>(engine.getSystemByName(__NX_SCRIPT_KEY__));
	if (!self) return;
	
	auto f = self->getFramework();
	if (!f)
		nx::Log::warning("Script framework is corrupted", "SCRIPT_INTEGRITY");
	else{
		std::string rootPath =  nx::Engine::Instance().getEnv().getGameInfos().getRootPath() + nx::Engine::Instance().getGameInfosParser()->getFields()._resources.at("scripts");
		f->init(rootPath + external::any_cast<std::string>(e.data));
	}
}

void nx::ScriptSystem::event_ScriptUpdate(const nx::Event& e)
{
	auto& engine = nx::Engine::Instance();
	auto self = nx::Engine::cast<nx::ScriptSystem>(engine.getSystemByName(__NX_SCRIPT_KEY__));
	if (!self) return;
	
	auto f = self->getFramework();
	if (!f)
		nx::Log::warning("Script framework is corrupted", "SCRIPT_INTEGRITY");
	else{
		std::string rootPath =  nx::Engine::Instance().getEnv().getGameInfos().getRootPath() + nx::Engine::Instance().getGameInfosParser()->getFields()._resources.at("scripts");
		f->update(rootPath + external::any_cast<std::string>(e.data));
	}
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
		std::string absPath = nx::Engine::Instance().getEnv().getGameInfos().getRootPath() + nx::Engine::Instance().getGameInfosParser()->getFields()._resources.at("scripts");
		nx::script::ScriptInfos si = external::any_cast<nx::script::ScriptInfos>(e.data);
		f->execFunction((si.absolute)? si.file : absPath + si.file, si.func);
	}
}