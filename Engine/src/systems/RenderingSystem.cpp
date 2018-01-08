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