#include "Nexus/rendering.hpp"
#include "Nexus/engine.hpp"
#include "Nexus/frameworks/FrameworkManager.hpp"

nx::RenderingSystem::RenderingSystem()
:
	nx::SystemTpl(__NX_RENDERING_KEY__),
	_framework_m(std::make_shared<nx::FrameworkManager<nx::rendering::RenderingFrameworkTpl>>(__NX_RENDERING_KEY__, true))
{
	connect(nx::EVENT::ENV_UPDATE_SCENE, nx::RenderingSystem::event_EnvUpdateScene);
}

nx::RenderingSystem::~RenderingSystem() {

}

 nx::rendering::RenderingFrameworkTpl* nx::RenderingSystem::getFramework()
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
		f->LoadScene("Menu");
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

void nx::RenderingSystem::event_EnvUpdateScene(const nx::Event& e)
{
	auto& engine = nx::Engine::Instance();
	auto self = nx::Engine::cast<nx::RenderingSystem>(engine.getSystemByName(__NX_RENDERING_KEY__));
	if (!self) return;

	auto f = self->getFramework();
	if (!f)
	{
		nx::Log::warning("Rendering framework is corrupted", "RENDERING_FRAMEWORK_INTEGRITY");
		return;
	}

	/*nx::env::Scene &scene = external::any_cast<nx::env::Scene>(e.data);
	f->RefreshScene(scene);*/
	nx::env::Scene scene(external::any_cast<nx::env::Scene>(e.data));
	nx::Log::debug("r: " + std::to_string(scene.getLayerAt(0).getAllTexts()[0].getGuiTextInfos().getTextInfo().getTextColor().getRed()), false);
	nx::Log::debug(" | g: " + std::to_string(scene.getLayerAt(0).getAllTexts()[0].getGuiTextInfos().getTextInfo().getTextColor().getGreen()), false);
	nx::Log::debug(" | b: " + std::to_string(scene.getLayerAt(0).getAllTexts()[0].getGuiTextInfos().getTextInfo().getTextColor().getBlue()), false);
	nx::Log::debug(" | a: " + std::to_string(scene.getLayerAt(0).getAllTexts()[0].getGuiTextInfos().getTextInfo().getTextColor().getAlpha()));
	f->RefreshScene(scene);
}