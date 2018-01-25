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
		//Home layer
		f->addLayer("Home");
		f->addText(
			"Home",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(470, 225), nx::maths::Vector2f(0, 0), "IpAddressText",
			{

			}),
			nx::rendering::GUITextInfos(nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "IP Address", 16, nx::rendering::RGBa(255, 255, 255, 255), 0))
		);
		f->addTextInput(
			"Home",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(392, 260), nx::maths::Vector2f(240, 28), "IpAddressTextInput",
				{

				}),
			nx::rendering::GUITextInputInfos(nx::rendering::ColorInfo(nx::rendering::RGBa(200, 200, 200, 255), nx::rendering::RGBa(255, 255, 255, 255), 2),
											 nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "", 12, nx::rendering::RGBa(0, 0, 0, 255), 0))
		);
		f->addText(
			"Home",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(497, 315), nx::maths::Vector2f(0, 0), "PortText",
				{

				}),
				nx::rendering::GUITextInfos(nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "Port", 16, nx::rendering::RGBa(255, 255, 255, 255), 0))
				);
		f->addTextInput(
			"Home",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(477, 350), nx::maths::Vector2f(70, 28), "PortTextInput",
				{	

				}),
			nx::rendering::GUITextInputInfos(nx::rendering::ColorInfo(nx::rendering::RGBa(200, 200, 200, 255), nx::rendering::RGBa(255, 255, 255, 255), 2),
											 nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "", 12, nx::rendering::RGBa(0, 0, 0, 255), 0))
		);
		f->addButton(
			"Home",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(432, 480), nx::maths::Vector2f(160, 30), "ConnectButton",
			{
				{ "onLeftClickPressedInside",{ "menu.lua", "displayAlertConnectionToServer" } }
			}),
			nx::rendering::GUIButtonInfos(true, nx::rendering::ColorInfo(nx::rendering::RGBa(200, 200, 200, 255), nx::rendering::RGBa(255, 255, 255, 255), 2),
										  nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "Connect", 20, nx::rendering::RGBa(0, 0, 0, 255), 0))
		);
		f->addButton(
			"Home",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(0, 0), nx::maths::Vector2f(1024, 768), "OpaqueBackground",
			{

			}),
			nx::rendering::GUIButtonInfos(true, nx::rendering::ColorInfo(nx::rendering::RGBa(0, 0, 0, 190), nx::rendering::RGBa(0, 0, 0, 0), 0),
										  nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "", 0, nx::rendering::RGBa(0, 0, 0, 0), 0))
		);
		f->addGUISprite(
			"Home",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(477, 349), nx::maths::Vector2f(0, 0), "LoadingSprite",
				{

				}),
				nx::rendering::GUISpriteInfos("./images/loading.png", nx::maths::Vector2f(4, 2), nx::maths::Vector2f(68, 70))
		);
		f->setAnimateToGUISprite("Home", "LoadingSprite", true);
		f->setSlownessToGUISprite("Home", "LoadingSprite", 70);
		// Waiting room
		/*f->addLayer("WaitingRoom");
		f->addButton(
			"WaitingRoom",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(247, 300), nx::maths::Vector2f(80, 30), "Player1Status",
			{

			}),
			nx::rendering::GUIButtonInfos(true, nx::rendering::ColorInfo(nx::rendering::RGBa(180, 0, 0, 255), nx::rendering::RGBa(120, 120, 120, 255), 2),
										  nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "Player 1", 14, nx::rendering::RGBa(255, 255, 255, 255), 0))
		);
		f->addButton(
			"WaitingRoom",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(397, 300), nx::maths::Vector2f(80, 30), "Player2Status",
			{

			}),
			nx::rendering::GUIButtonInfos(true, nx::rendering::ColorInfo(nx::rendering::RGBa(180, 0, 0, 255), nx::rendering::RGBa(120, 120, 120, 255), 2),
										  nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "Player 2", 14, nx::rendering::RGBa(255, 255, 255, 255), 0))
		);
		f->addButton(
			"WaitingRoom",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(547, 300), nx::maths::Vector2f(80, 30), "Player3Status",
			{

			}),
			nx::rendering::GUIButtonInfos(true, nx::rendering::ColorInfo(nx::rendering::RGBa(180, 0, 0, 255), nx::rendering::RGBa(120, 120, 120, 255), 2),
										  nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "Player 3", 14, nx::rendering::RGBa(255, 255, 255, 255), 0))
		); 
		f->addButton(
			"WaitingRoom",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(697, 300), nx::maths::Vector2f(80, 30), "Player4Status",
			{

			}),
			nx::rendering::GUIButtonInfos(true, nx::rendering::ColorInfo(nx::rendering::RGBa(180, 0, 0, 255), nx::rendering::RGBa(120, 120, 120, 255), 2),
										  nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "Player 4", 14, nx::rendering::RGBa(255, 255, 255, 255), 0))
		);
		f->addText(
			"WaitingRoom",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(410, 420), nx::maths::Vector2f(0, 0), "WaitingText",
			{

			}),
			nx::rendering::GUITextInfos(nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "Waiting for players..", 22, nx::rendering::RGBa(255, 255, 255, 255), 0))
		);*/
		//HUD
		/*f->addLayer("HUD");
		f->addText(
			"HUD",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(20, 20), nx::maths::Vector2f(0, 0), "P1ScoreText",
			{

			}),
			nx::rendering::GUITextInfos(nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "P1:", 16, nx::rendering::RGBa(255, 255, 255, 255), 0))
		);
		f->addText(
			"HUD",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(50, 20), nx::maths::Vector2f(0, 0), "P1ScoreValue",
			{

			}),
			nx::rendering::GUITextInfos(nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "0", 16, nx::rendering::RGBa(255, 255, 255, 255), 0))
		);
		f->addText(
			"HUD",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(20, 50), nx::maths::Vector2f(0, 0), "P2ScoreText",
			{

			}),
			nx::rendering::GUITextInfos(nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "P2:", 16, nx::rendering::RGBa(255, 255, 255, 255), 0))
		);
		f->addText(
			"HUD",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(50, 50), nx::maths::Vector2f(0, 0), "P2ScoreValue",
			{

			}),
			nx::rendering::GUITextInfos(nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "0", 16, nx::rendering::RGBa(255, 255, 255, 255), 0))
		);
		f->addText(
			"HUD",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(20, 80), nx::maths::Vector2f(0, 0), "P3ScoreText",
			{

			}),
			nx::rendering::GUITextInfos(nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "P3:", 16, nx::rendering::RGBa(255, 255, 255, 255), 0))
		);
		f->addText(
			"HUD",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(50, 80), nx::maths::Vector2f(0, 0), "P3ScoreValue",
			{

			}),
			nx::rendering::GUITextInfos(nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "0", 16, nx::rendering::RGBa(255, 255, 255, 255), 0))
		);
		f->addText(
			"HUD",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(20, 110), nx::maths::Vector2f(0, 0), "P4ScoreText",
			{

			}),
			nx::rendering::GUITextInfos(nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "P4:", 16, nx::rendering::RGBa(255, 255, 255, 255), 0))
		);
		f->addText(
			"HUD",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(50, 110), nx::maths::Vector2f(0, 0), "P4ScoreValue",
			{

			}),
			nx::rendering::GUITextInfos(nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "0", 16, nx::rendering::RGBa(255, 255, 255, 255), 0))
		);
		f->addText(
			"HUD",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(915, 25), nx::maths::Vector2f(0, 0), "PlayerLifeValue",
			{

			}),
			nx::rendering::GUITextInfos(nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "100", 24, nx::rendering::RGBa(255, 255, 255, 255), 0))
		);
		f->addImage(
			"HUD",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(965, 20), nx::maths::Vector2f(40, 40), "PlayerLifeSprite",
			{

			}),
			nx::rendering::GUIImageInfos("./images/heart.png")
		);*/
		//EscapeMenu
		/*f->addButton(
			"HUD",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(0, 0), nx::maths::Vector2f(1024, 768), "EscapeMenuBackground",
			{

			}),
			nx::rendering::GUIButtonInfos(true, nx::rendering::ColorInfo(nx::rendering::RGBa(0, 0, 0, 170), nx::rendering::RGBa(0, 0, 0, 0), 0),
										  nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "", 0, nx::rendering::RGBa(0, 0, 0, 0), 0))
		);
		f->addButton(
			"HUD",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(457, 300), nx::maths::Vector2f(110, 40), "ContinueButton",
			{

			}),
			nx::rendering::GUIButtonInfos(true, nx::rendering::ColorInfo(nx::rendering::RGBa(200, 200, 200, 255), nx::rendering::RGBa(255, 255, 255, 255), 2),
										  nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "Continue", 18, nx::rendering::RGBa(0, 0, 0, 255), 0))
		);
		f->addButton(
			"HUD",
			nx::rendering::GUIElementInfos(nx::maths::Vector2f(457, 450), nx::maths::Vector2f(110, 40), "QuitButton",
			{

			}),
			nx::rendering::GUIButtonInfos(true, nx::rendering::ColorInfo(nx::rendering::RGBa(200, 200, 200, 255), nx::rendering::RGBa(255, 255, 255, 255), 2),
										  nx::rendering::TextInfo("./fonts/Roboto-Regular.ttf", "Quit", 18, nx::rendering::RGBa(0, 0, 0, 255), 0))
		);*/
		/*f->addLayer("Menu");
		f->addLayer("HUD");
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
		f->setBackgroundColorToRectShape("MyCauvinGraphicsRect", nx::rendering::RGBa(255, 255, 255, 255));
		f->addGraphicsConvexShape(
			nx::rendering::GraphicsElementInfos(nx::maths::Vector2f(550, 440), nx::maths::Vector2f(0, 0), "MyCauvinGraphicsConvex",
			{

			}),
			nx::rendering::GraphicsConvexInfos(nx::rendering::ColorInfo(nx::rendering::RGBa(255, 50, 50, 255), nx::rendering::RGBa(0, 255, 0, 255), 3))
			);*/
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