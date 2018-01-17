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
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(100, 150), nx::maths::Vector2f(300, 50), "MyHerbauxButton",
			{
				{ "onLeftClickPressedInside",{ "alert.lua", "onClick" } },
			}),
			nx::rendering::GUIButtonInfos(true, nx::rendering::ColorInfo(nx::rendering::RGBa(100, 200, 100, 50), nx::rendering::RGBa(255, 0, 0, 150), 2),
										  nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "Herbaux is a true God", 20, nx::rendering::RGBa(50, 50, 200, 255), 0))
		);
		f->addCheckbox(
			"Menu",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(640, 30), nx::maths::Vector2f(30, 30), "MyCauvinButton",
			{

			}),
			nx::rendering::GUICheckboxInfos(nx::rendering::ColorInfo(nx::rendering::RGBa(200, 200, 200, 255), nx::rendering::RGBa(0, 0, 255, 255), 2))
		);
		f->setStateToCheckbox("Menu", "MyCauvinButton", nx::rendering::CheckboxState::PARTIAL);
		f->addProgressBar(
			"Menu",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(240, 500), nx::maths::Vector2f(300, 50), "MyCauvinProgressBar",
			{

			}),
			nx::rendering::GUIProgressBarInfos(nx::rendering::ColorInfo(nx::rendering::RGBa(200, 200, 200, 255), nx::rendering::RGBa(255, 255, 255, 255), 2),
											   nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "", 16, nx::rendering::RGBa(0, 0, 0, 255), 0))
		);
		f->addComboBox(
			"Menu",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(70, 250), nx::maths::Vector2f(140, 30), "MyCauvinComboBox",
			{

			}),
			nx::rendering::GUIComboBoxInfos(nx::rendering::ColorInfo(nx::rendering::RGBa(200, 200, 200, 255), nx::rendering::RGBa(255, 255, 0, 255), 2),
											nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "", 12, nx::rendering::RGBa(0, 0, 0, 255), 0))
		);
		f->addSelectionToComboBox("Menu", "MyCauvinComboBox", "First item");
		f->addSelectionToComboBox("Menu", "MyCauvinComboBox", "Second item");
		f->addSelectionToComboBox("Menu", "MyCauvinComboBox", "LEEERRROYYYY");
		f->addSelectionToComboBox("Menu", "MyCauvinComboBox", "JENKINSSSSS");
		f->addTextInput(
			"Menu",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(400, 350), nx::maths::Vector2f(230, 30), "MyCauvinTextInput",
			{

			}),
			nx::rendering::GUITextInputInfos(nx::rendering::ColorInfo(nx::rendering::RGBa(200, 200, 200, 255), nx::rendering::RGBa(255, 0, 255, 255), 2),
				nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "A default text..", 12, nx::rendering::RGBa(0, 0, 0, 255), 0))
		);
		f->addText(
			"Menu",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(500, 30), nx::maths::Vector2f(0, 0), "MyCauvinText",
			{

			}),
			nx::rendering::GUITextInfos(nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "Sample text", 16, nx::rendering::RGBa(0, 255, 0, 255), 0))
		);
		f->addImage(
			"Menu",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(300, 580), nx::maths::Vector2f(64, 64), "MyCauvinImage",
			{

			}),
			nx::rendering::GUIImageInfos("./images/defaultgamelogo.png")
			);
		f->addGUISprite(
			"Menu",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(50, 600), nx::maths::Vector2f(0, 0), "MyCauvinGUISprite",
			{

			}),
			nx::rendering::GUISpriteInfos("./images/guitarist.png", nx::maths::Vector2f(3, 2), nx::maths::Vector2f(103, 89))
			);
		f->setAnimateToGUISprite("Menu", "MyCauvinGUISprite", true);
		f->setSlownessToGUISprite("Menu", "MyCauvinGUISprite", 70);
		f->addGraphicsSprite(
			nx::rendering::GraphicsElementInfos(nx::maths::Vector2f(400, 620), nx::maths::Vector2f(0, 0), "MyCauvinGraphicsSprite",
			{

			}),
			nx::rendering::GraphicsSpriteInfos("./images/guitarist.png", nx::maths::Vector2f(3, 2), nx::maths::Vector2f(103, 89))
			);
		f->addGraphicsCirleShape(
			nx::rendering::GraphicsElementInfos(nx::maths::Vector2f(550, 640), nx::maths::Vector2f(0, 0), "MyCauvinGraphicsCircle",
			{

			}),
			nx::rendering::GraphicsCircleInfos(30, nx::rendering::ColorInfo(nx::rendering::RGBa(255, 50, 50, 255), nx::rendering::RGBa(0, 255, 0, 255), 3))
			);
		f->setBackgroundColorToCircleShape("MyCauvinGraphicsCircle", nx::rendering::RGBa(255, 255, 255, 255));
		f->addGraphicsRectShape(
			nx::rendering::GraphicsElementInfos(nx::maths::Vector2f(550, 540), nx::maths::Vector2f(20, 40), "MyCauvinGraphicsRect",
			{

			}),
			nx::rendering::GraphicsRectInfos(nx::rendering::ColorInfo(nx::rendering::RGBa(255, 50, 50, 255), nx::rendering::RGBa(0, 255, 0, 255), 3))
			);
		f->addGraphicsConvexShape(
			nx::rendering::GraphicsElementInfos(nx::maths::Vector2f(550, 440), nx::maths::Vector2f(0, 0), "MyCauvinGraphicsConvex",
			{

			}),
			nx::rendering::GraphicsConvexInfos(nx::rendering::ColorInfo(nx::rendering::RGBa(255, 50, 50, 255), nx::rendering::RGBa(0, 255, 0, 255), 3))
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