#include "Nexus/gui.hpp"
#include "Nexus/engine.hpp"

nx::GUISystem::GUISystem()
:
	nx::SystemTpl("gui"),
	_framework_m("gui", true)
{

}

nx::GUISystem::~GUISystem() {

}

nx::GUISystem* nx::GUISystem::cast(const std::shared_ptr<nx::SystemTpl>& src)
{
	auto ptr = src.get();
	if (!ptr) return nullptr;
	return dynamic_cast<nx::GUISystem*>(ptr);
}

 nx::GuiFrameworkTpl* nx::GUISystem::getFramework()
{
	return this->_framework_m.getFramework();
}

void nx::GUISystem::init()
{

}

void nx::GUISystem::update()
{
	auto f = this->getFramework();
	if (!f)
		nx::Log::print("Aled ptr is nullptr");
	else
		f->displaySquare(10, 20, 30);
	std::cout << "Update for " << this->getName() << std::endl;
}

bool nx::GUISystem::checkIntegrity() const
{
	if (this->_framework_m.getFramework()) {
		return true;
	}
	return false;
}