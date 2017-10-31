#include "Nexus/gui.hpp"
#include "Nexus/engine.hpp"

nx::GUISystem::GUISystem()
	:
	nx::SystemTpl("gui")
{

}

nx::GUISystem::~GUISystem() {

}

nx::GUISystem* nx::GUISystem::cast(const std::shared_ptr<nx::SystemTpl>& src)
{
	auto ptr = src.get();
	if (!ptr) return nullptr;
	auto dst = dynamic_cast<nx::GUISystem*>(ptr);
	return dst;
}

void nx::GUISystem::init()
{
	std::cout << "Init for " << this->getName() << std::endl;
}

void nx::GUISystem::update()
{
	std::cout << "Update for " << this->getName() << std::endl;
}

bool nx::GUISystem::checkIntegrity() const
{
	return true;
}