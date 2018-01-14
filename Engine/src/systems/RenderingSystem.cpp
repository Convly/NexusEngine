#include "Nexus/rendering.hpp"
#include "Nexus/engine.hpp"
#include "Nexus/frameworks/FrameworkManager.hpp"

nx::RenderingSystem::RenderingSystem()
:
	nx::SystemTpl(__NX_RENDERING_KEY__),
	_framework_m(std::make_shared<nx::FrameworkManager<nx::RenderingFrameworkTpl>>(__NX_RENDERING_KEY__, true))
{

}

nx::RenderingSystem::~RenderingSystem() {

}

 nx::RenderingFrameworkTpl* nx::RenderingSystem::getFramework()
{
	return this->_framework_m->getFramework();
}

void nx::RenderingSystem::init()
{
	auto f = this->getFramework();
	if (!f)
		nx::Log::print("Framework is nullptr");
	else {
		f->InitializeWindow(1024, 768, "R-Type");
		f->addLayer("Menu");
		f->addLayer("HUD");
		f->addLayer("Inventory");
		f->addButton(
			"Menu",
			nx::rendering::GUIElementInfos(nx::Vector2f(100, 150), nx::Vector2f(300, 50), "MyHerbauxButton",
			{
				{"onLeftClickPressedInside", {"alert.lua", "click"}},
				{"onLeftClickReleasedInside", {"alert.lua", "clickRelease"}},
				{"keyPressed", {"alert.lua", "keyPressed"}}
			}),
			nx::rendering::GUIButtonInfos(true, nx::rendering::ColorInfo(nx::rendering::RGBa(100, 200, 100, 50), nx::rendering::RGBa(255, 0, 0, 150), 2), nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "Herbaux is a true God", 20, nx::rendering::RGBa(50, 50, 200, 255), 0))
		);
	}
}

void nx::RenderingSystem::update()
{
	auto f = this->getFramework();
	if (!f)
		nx::Log::print("Framework is nullptr");
	else
		f->RefreshRendering();
}

bool nx::RenderingSystem::checkIntegrity() const
{
	if (this->_framework_m->getFramework()) {
		return true;
	}
	return false;
}