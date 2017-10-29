#include "Nexus/gui.hpp"
#include "Nexus/engine.hpp"

nx::gui::GUISystem::GUISystem(nx::Engine& engine)
	:
	nx::SystemTpl("gui", engine)
{

}

nx::gui::GUISystem::~GUISystem() {

}

void nx::gui::GUISystem::init()
{
	std::cout << "Init" << std::endl;
}

void nx::gui::GUISystem::update()
{
	std::cout << "Update for " << this->getName() << std::endl;
}

bool nx::gui::GUISystem::checkIntegrity() const
{
	return true;
}