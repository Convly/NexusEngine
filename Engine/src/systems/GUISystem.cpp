#include "Nexus/gui.hpp"

nx::gui::GUISystem::GUISystem()
	:
	nx::SystemTpl("gui")
{

}

nx::gui::GUISystem::~GUISystem() {

}

void nx::gui::GUISystem::init() {
	std::cout << "Init" << std::endl;
}

void nx::gui::GUISystem::update() {

	std::cout << "Update" << std::endl;
}

bool nx::gui::GUISystem::checkIntegrity() const {
	return true;
}

const std::string& nx::gui::GUISystem::getName() const {
	return this->_name;
}
