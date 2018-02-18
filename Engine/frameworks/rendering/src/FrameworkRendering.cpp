#include "FrameworkRendering.hpp"

nx::Engine* enginePtr = nullptr;
GraphicResources resources;

FrameworkRendering::FrameworkRendering(nx::Engine* engine)
	:
	RenderingFrameworkTpl("FrameworkRendering"),
	_engine(engine),
	_win(nullptr),
	_guiHandler(nullptr),
	_graphicsHandler(nullptr),
	_sfxHandler(nullptr)
{
	enginePtr = engine;
	nx::Log::inform("New Rendering Framework created");
}

FrameworkRendering::~FrameworkRendering()
{
	nx::Log::inform("New Rendering Framework deleted");
}

void FrameworkRendering::InitializeWindow(int width, int height, std::string titleWin)
{
	this->_win = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), titleWin);
	this->_guiHandler = std::make_shared<nx::gui::GUIHandler>(this->_win);
	this->_graphicsHandler = std::make_shared<nx::graphics::GraphicsHandler>(this->_win);
	this->_sfxHandler = std::make_shared<nx::sfx::SfxHandler>();
}

void FrameworkRendering::RefreshRendering()
{
	if (this->_win && this->_guiHandler)
	{
		while (this->_win->isOpen())
		{
			// Getting input events	
			sf::Event event;

			while (this->_win->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					this->_win->close();
				this->_guiHandler->processEvent(event);
			}

			this->HandleKeyboard();
			
			// Clearing the window
			this->_win->clear(sf::Color(0, 0 , 0, 255));

			// Drawing stuff on screen
			this->_graphicsHandler->drawElements();
			this->_guiHandler->drawLayers();

			// Displaying screen
			this->_win->display();
		}
	}
}

void FrameworkRendering::HandleKeyboard()
{
	nx::env::Keyboard board;
	for (int k = -1; k <= nx::env::Keyboard::Key::KeyCount; ++k)
		board.setKeyState(k, sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(k)));

	if (board != _keyboard)
	{
		_keyboard = board;
		// TODO: SEND EVENT THROUGH NETWORK
	}
}

void FrameworkRendering::LoadScene(std::string const& sceneName)
{
	try
	{
		auto &scenes = enginePtr->getEnv().getScenes();

		auto scene = std::find_if(scenes.begin(), scenes.end(), [&](nx::env::Scene scene)
		{
			return (scene.getEntityInfos().getName() == sceneName);
		});
		if (scene != scenes.end())
		{
			auto &gameobjects = scene->getGameObjects();
			for (auto &gameobject : gameobjects)
			{
				if (gameobject.getEntityInfos().getActive())
				{
					nx::env::TransformComponent const& transform = gameobject.getTransformComponentConst();
					nx::env::RendererComponent const& renderer = gameobject.getRendererComponentConst();
					nx::env::EntityInfos const& infos = renderer.getEntityInfosConst();
					if (gameobject.getScriptComponentConst().getEntityInfos().getActiveConst())
					{
						const std::string scriptPath = gameobject.getScriptComponentConst().getScriptPath();
						enginePtr->emit(nx::EVENT::SCRIPT_LOAD, scriptPath);
						enginePtr->emit(nx::EVENT::SCRIPT_INIT, scriptPath);
					}

					switch (renderer.getShapeTypeConst())
					{
					case nx::env::ShapeType::RECTSHAPE:
						this->addGraphicsRectShape(nx::env::GraphicsElementInfos(transform.getPos(), transform.getSize(), infos.getNameConst()),
							nx::env::GraphicsRectInfos(renderer.getColorInfoConst()));
						break;
					case nx::env::ShapeType::CIRCLESHAPE:
						this->addGraphicsCirleShape(nx::env::GraphicsElementInfos(transform.getPos(), transform.getSize(), infos.getNameConst()),
							nx::env::GraphicsCircleInfos(renderer.getRadiusConst(), renderer.getColorInfoConst()));
						break;
					case nx::env::ShapeType::CONVEXSHAPE:
						this->addGraphicsConvexShape(nx::env::GraphicsElementInfos(transform.getPos(), transform.getSize(), infos.getNameConst()),
							nx::env::GraphicsConvexInfos(renderer.getColorInfoConst()));
						break;
					case nx::env::ShapeType::UNDEFINED:
						this->addGraphicsSprite(nx::env::GraphicsElementInfos(transform.getPos(), transform.getSize(), infos.getNameConst()),
							nx::env::GraphicsSpriteInfos(renderer.getTexturePathConst(), renderer.getSheetGridConst(), renderer.getSpriteSizeConst()));
						break;
					};
				}
			}
			auto &layers = scene->getLayers();
			for (auto &layer : layers)
			{
				if (layer.getEntityInfos().getActive())
				{
					this->addLayer(layer.getEntityInfos().getName());
					this->_registerGUICheckbox(layer.getAllCheckboxes(), layer.getEntityInfos().getName());
					this->_registerGUIComboBox(layer.getAllComboBoxes(), layer.getEntityInfos().getName());
					this->_registerGUIImage(layer.getAllImages(), layer.getEntityInfos().getName());
					this->_registerGUIProgressBar(layer.getAllProgressBars(), layer.getEntityInfos().getName());
					this->_registerGUISprite(layer.getAllSprites(), layer.getEntityInfos().getName());
					this->_registerGUIText(layer.getAllTexts(), layer.getEntityInfos().getName());
					this->_registerGUITextInput(layer.getAllTextInputs(), layer.getEntityInfos().getName());
					this->_registerGUIButton(layer.getAllButtons(), layer.getEntityInfos().getName());
				}
			}
		}
	}
	catch (std::exception e)
	{
		nx::Log::debug(e.what());
	}
}

void FrameworkRendering::RefreshScene(nx::env::Scene newScene)
{
	auto &scenes = enginePtr->getEnv().getScenes();

	auto scene = std::find_if(scenes.begin(), scenes.end(), [&](nx::env::Scene scene)
	{
		return (scene.getEntityInfos().getName() == newScene.getEntityInfos().getName());
	});

	if (scene != scenes.end())
	{
		auto &gameobjects = newScene.getGameObjects();
		for (auto &gameobject : gameobjects)
		{
			if (gameobject.isModified())
			{
				std::string gameObjectName = gameobject.getRendererComponent().getEntityInfos().getName();

				this->removeGraphicsElem(gameObjectName);
				scene->removeGameObject(gameObjectName);
				if (gameobject.getEntityInfos().getActive())
				{
					auto newGameObject = std::find_if(newScene.getGameObjects().begin(), newScene.getGameObjects().end(),
													  [&](nx::env::GameObject gameObject)
													  {
														  return (gameObject.getEntityInfos().getName() == gameObjectName);
													  });
					if (newGameObject != newScene.getGameObjects().end())
					{
						nx::env::TransformComponent const& transform = newGameObject->getTransformComponentConst();
						nx::env::RendererComponent const& renderer = newGameObject->getRendererComponentConst();
						nx::env::EntityInfos const& infos = renderer.getEntityInfosConst();

						switch (newGameObject->getRendererComponent().getShapeType())
						{
							case nx::env::ShapeType::RECTSHAPE:
								this->addGraphicsRectShape(nx::env::GraphicsElementInfos(transform.getPos(), transform.getSize(), infos.getNameConst()),
														   nx::env::GraphicsRectInfos(renderer.getColorInfoConst()));
								break;
							case nx::env::ShapeType::CIRCLESHAPE:
								this->addGraphicsCirleShape(nx::env::GraphicsElementInfos(transform.getPos(), transform.getSize(), infos.getNameConst()),
															nx::env::GraphicsCircleInfos(renderer.getRadiusConst(), renderer.getColorInfoConst()));
								break;
							case nx::env::ShapeType::CONVEXSHAPE:
								this->addGraphicsConvexShape(nx::env::GraphicsElementInfos(transform.getPos(), transform.getSize(), infos.getNameConst()),
															 nx::env::GraphicsConvexInfos(renderer.getColorInfoConst()));
								break;
							case nx::env::ShapeType::UNDEFINED:
								this->addGraphicsSprite(nx::env::GraphicsElementInfos(transform.getPos(), transform.getSize(), infos.getNameConst()),
														nx::env::GraphicsSpriteInfos(renderer.getTexturePathConst(), renderer.getSheetGridConst(), renderer.getSpriteSizeConst()));
								break;
						};
						scene->addGameObjectCopy(*newGameObject);
					}
				}
			}
		}
		auto &layers = newScene.getLayers();
		for (auto &layer : layers)
		{
			if (layer.isModified())
			{
				std::string layerName = layer.getEntityInfos().getName();

				std::cout << this->removeLayer(layerName) << std::endl;
				scene->removeLayer(layerName);
				if (layer.getEntityInfos().getActive())
				{
					this->addLayer(layer.getEntityInfos().getName());
					this->_registerGUIButton(layer.getAllButtons(), layerName);
					this->_registerGUICheckbox(layer.getAllCheckboxes(), layerName);
					this->_registerGUIComboBox(layer.getAllComboBoxes(), layerName);
					this->_registerGUIImage(layer.getAllImages(), layerName);
					this->_registerGUIProgressBar(layer.getAllProgressBars(), layerName);
					this->_registerGUISprite(layer.getAllSprites(), layerName);
					this->_registerGUIText(layer.getAllTexts(), layerName);
					this->_registerGUITextInput(layer.getAllTextInputs(), layerName);
					scene->addLayer(layer);
				}
			}
		}
	}

}

void FrameworkRendering::_registerGUIButton(std::vector<nx::env::gui::Button> const& buttons, std::string const& layerName)
{
	for (auto it : buttons)
		this->addButton(layerName, it.getGuiElementInfos(), it.getGuiButtonInfos());
}

void 	FrameworkRendering::_registerGUICheckbox(std::vector<nx::env::gui::Checkbox> const& checkboxes, std::string const& layerName)
{
	for (auto it : checkboxes)
		this->addCheckbox(layerName, it.getGuiElementInfos(), it.getGuiCheckBoxInfos());
}

void 	FrameworkRendering::_registerGUIComboBox(std::vector<nx::env::gui::ComboBox> const& comboboxes, std::string const& layerName)
{
	for (auto it : comboboxes)
		this->addComboBox(layerName, it.getGuiElementInfos(), it.getGuiComboBoxInfos());
}

void 	FrameworkRendering::_registerGUIImage(std::vector<nx::env::gui::Image> const& images, std::string const& layerName)
{
	for (auto it : images)
		this->addImage(layerName, it.getGuiElementInfos(), it.getGuiImageInfos());
}

void 	FrameworkRendering::_registerGUIProgressBar(std::vector<nx::env::gui::ProgressBar> const& progressbars, std::string const& layerName)
{
	for (auto it : progressbars)
		this->addProgressBar(layerName, it.getGuiElementInfos(), it.getGuiProgressBarInfos());
}

void 	FrameworkRendering::_registerGUISprite(std::vector<nx::env::gui::Sprite> const& sprites, std::string const& layerName)
{
	for (auto it : sprites)
		this->addGUISprite(layerName, it.getGuiElementInfos(), it.getGuiSpriteInfos());
}

void 	FrameworkRendering::_registerGUIText(std::vector<nx::env::gui::Text> const& texts, std::string const& layerName)
{
	for (auto it : texts)
		this->addText(layerName, it.getGuiElementInfos(), it.getGuiTextInfos());
}

void 	FrameworkRendering::_registerGUITextInput(std::vector<nx::env::gui::TextInput> const& textinputs, std::string const& layerName)
{
	for (auto it : textinputs)
		this->addTextInput(layerName, it.getGuiElementInfos(), it.getGuiTextInputInfos());
}

/// TOOLS ///

sf::Color FrameworkRendering::RGBa_to_sfColor(const nx::env::RGBa& color)
{
	return sf::Color(color.getRedConst(), color.getGreenConst(), color.getBlueConst(), color.getAlphaConst());
}

/// EVENTS ///


bool FrameworkRendering::addLayer(const std::string& layerIdentifier)
{
	if (!_guiHandler || !_win)
		return false;

	if (this->_guiHandler->getLayers().size() > 0) {
		if (this->_guiHandler->layer_exists(layerIdentifier))
		{
			nx::Log::error(layerIdentifier + " already exists", "LAYER_DUPLICATE", 500);
			return false;
		}
	}

	this->_guiHandler->addLayer(std::make_shared<nx::gui::GUILayer>(layerIdentifier));
	return true;
}

bool FrameworkRendering::addButton(const std::string& layerId, const nx::env::GUIElementInfos& guiParams, const nx::env::GUIButtonInfos& buttonsParams)
{
	if (!this->_guiHandler->layer_exists(layerId) || this->_guiHandler->getLayerByName(layerId)->object_exists(guiParams.getIdentifierConst())) {
		return (false);
	}

	std::shared_ptr<nx::gui::Button> button = std::make_shared<nx::gui::Button>(
		sf::Vector2f(guiParams.getPosConst().x, guiParams.getPosConst().y),
		sf::Vector2f(guiParams.getSizeConst().x, guiParams.getSizeConst().y),
		guiParams.getIdentifierConst(),
		guiParams.getEvents(),
		buttonsParams.getIsPushButtonConst(),
		nx::ColorInfo(
			FrameworkRendering::RGBa_to_sfColor(buttonsParams.getColorInfoConst().getBackgroundColorConst()),
			FrameworkRendering::RGBa_to_sfColor(buttonsParams.getColorInfoConst().getBorderColorConst()),
			buttonsParams.getColorInfoConst().getBorderThicknessConst()),
		nx::TextInfo(
			buttonsParams.getTextInfoConst().getFontPathConst(),
			buttonsParams.getTextInfoConst().getTextLabelConst(),
			buttonsParams.getTextInfoConst().getFontSizeConst(),
			FrameworkRendering::RGBa_to_sfColor(buttonsParams.getTextInfoConst().getTextColorConst()))
	);
	button->setVisible(guiParams.getActiveConst());
	auto b = guiParams.getActiveConst();
	this->_guiHandler->getLayerByName(layerId)->add(button);
	std::cout << "Adding new button (" << guiParams.getIdentifierConst() << ") in " << layerId << std::endl;
	return (true);
}


bool FrameworkRendering::addCheckbox(const std::string& layerId, const nx::env::GUIElementInfos& guiParams, const nx::env::GUICheckboxInfos& checkboxParams)
{
	if (!this->_guiHandler->layer_exists(layerId) || this->_guiHandler->getLayerByName(layerId)->object_exists(guiParams.getIdentifierConst())) {
		return (false);
	}

	std::shared_ptr<nx::gui::Checkbox> checkbox = std::make_shared<nx::gui::Checkbox>(
		sf::Vector2f(guiParams.getPosConst().x, guiParams.getPosConst().y),
		sf::Vector2f(guiParams.getSizeConst().x, guiParams.getSizeConst().y),
		guiParams.getIdentifierConst(),
		guiParams.getEvents(),
		nx::ColorInfo(
			FrameworkRendering::RGBa_to_sfColor(checkboxParams.getColorInfoConst().getBackgroundColorConst()),
			FrameworkRendering::RGBa_to_sfColor(checkboxParams.getColorInfoConst().getBorderColorConst()),
			checkboxParams.getColorInfoConst().getBorderThicknessConst())
	);
	checkbox->setVisible(guiParams.getActiveConst());
	this->_guiHandler->getLayerByName(layerId)->add(checkbox);
	std::cout << "Adding new checkbox (" << guiParams.getIdentifierConst() << ") in " << layerId << std::endl;
	return (true);
}

bool FrameworkRendering::addProgressBar(const std::string& layerId, const nx::env::GUIElementInfos& guiParams, const nx::env::GUIProgressBarInfos& progressBarParams)
{
	if (!this->_guiHandler->layer_exists(layerId) || this->_guiHandler->getLayerByName(layerId)->object_exists(guiParams.getIdentifierConst())) {
		return (false);
	}

	std::shared_ptr<nx::gui::ProgressBar> progressbar = std::make_shared<nx::gui::ProgressBar>(
		sf::Vector2f(guiParams.getPosConst().x, guiParams.getPosConst().y),
		sf::Vector2f(guiParams.getSizeConst().x, guiParams.getSizeConst().y),
		guiParams.getIdentifierConst(),
		guiParams.getEvents(),
		nx::ColorInfo(
			FrameworkRendering::RGBa_to_sfColor(progressBarParams.getColorInfoConst().getBackgroundColorConst()),
			FrameworkRendering::RGBa_to_sfColor(progressBarParams.getColorInfoConst().getBorderColorConst()),
			progressBarParams.getColorInfoConst().getBorderThicknessConst()),
		nx::TextInfo(
			progressBarParams.getTextInfoConst().getFontPathConst(),
			progressBarParams.getTextInfoConst().getTextLabelConst(),
			progressBarParams.getTextInfoConst().getFontSizeConst(),
			FrameworkRendering::RGBa_to_sfColor(progressBarParams.getTextInfoConst().getTextColorConst()))
		);
	progressbar->setVisible(guiParams.getActiveConst());
	this->_guiHandler->getLayerByName(layerId)->add(progressbar);
	std::cout << "Adding new progressbar (" << guiParams.getIdentifierConst() << ") in " << layerId << std::endl;
	return (true);
}

bool FrameworkRendering::addComboBox(const std::string& layerId, const nx::env::GUIElementInfos& guiParams, const nx::env::GUIComboBoxInfos& comboBoxParams)
{
	if (!this->_guiHandler->layer_exists(layerId) || this->_guiHandler->getLayerByName(layerId)->object_exists(guiParams.getIdentifierConst())) {
		return (false);
	}

	std::shared_ptr<nx::gui::ComboBox> combobox = std::make_shared<nx::gui::ComboBox>(
		sf::Vector2f(guiParams.getPosConst().x, guiParams.getPosConst().y),
		sf::Vector2f(guiParams.getSizeConst().x, guiParams.getSizeConst().y),
		guiParams.getIdentifierConst(),
		guiParams.getEvents(),
		nx::ColorInfo(
			FrameworkRendering::RGBa_to_sfColor(comboBoxParams.getColorInfoConst().getBackgroundColorConst()),
			FrameworkRendering::RGBa_to_sfColor(comboBoxParams.getColorInfoConst().getBorderColorConst()),
			comboBoxParams.getColorInfoConst().getBorderThicknessConst()),
		nx::TextInfo(
			comboBoxParams.getTextInfoConst().getFontPathConst(),
			comboBoxParams.getTextInfoConst().getTextLabelConst(),
			comboBoxParams.getTextInfoConst().getFontSizeConst(),
			FrameworkRendering::RGBa_to_sfColor(comboBoxParams.getTextInfoConst().getTextColorConst()))
		);
	combobox->setVisible(guiParams.getActiveConst());
	this->_guiHandler->getLayerByName(layerId)->add(combobox);
	std::cout << "Adding new combobox (" << guiParams.getIdentifierConst() << ") in " << layerId << std::endl;
	return (true);
}

bool FrameworkRendering::addTextInput(const std::string& layerId, const nx::env::GUIElementInfos& guiParams, const nx::env::GUITextInputInfos& textInputParams)
{
	if (!this->_guiHandler->layer_exists(layerId) || this->_guiHandler->getLayerByName(layerId)->object_exists(guiParams.getIdentifierConst())) {
		return (false);
	}

	std::shared_ptr<nx::gui::TextInput> textinput = std::make_shared<nx::gui::TextInput>(
		sf::Vector2f(guiParams.getPosConst().x, guiParams.getPosConst().y),
		sf::Vector2f(guiParams.getSizeConst().x, guiParams.getSizeConst().y),
		guiParams.getIdentifierConst(),
		guiParams.getEvents(),
		nx::ColorInfo(
			FrameworkRendering::RGBa_to_sfColor(textInputParams.getColorInfoConst().getBackgroundColorConst()),
			FrameworkRendering::RGBa_to_sfColor(textInputParams.getColorInfoConst().getBorderColorConst()),
			textInputParams.getColorInfoConst().getBorderThicknessConst()),
		nx::TextInfo(
			textInputParams.getTextInfoConst().getFontPathConst(),
			textInputParams.getTextInfoConst().getTextLabelConst(),
			textInputParams.getTextInfoConst().getFontSizeConst(),
			FrameworkRendering::RGBa_to_sfColor(textInputParams.getTextInfoConst().getTextColorConst()))
		);
	textinput->setVisible(guiParams.getActiveConst());
	this->_guiHandler->getLayerByName(layerId)->add(textinput);
	std::cout << "Adding new textinput (" << guiParams.getIdentifierConst() << ") in " << layerId << std::endl;
	return (true);
}

bool FrameworkRendering::addText(const std::string& layerId, const nx::env::GUIElementInfos& guiParams, const nx::env::GUITextInfos& textParams)
{
	if (!this->_guiHandler->layer_exists(layerId) || this->_guiHandler->getLayerByName(layerId)->object_exists(guiParams.getIdentifierConst())) {
		return (false);
	}

	std::shared_ptr<nx::gui::Text> text = std::make_shared<nx::gui::Text>(
		sf::Vector2f(guiParams.getPosConst().x, guiParams.getPosConst().y),
		guiParams.getIdentifierConst(),
		guiParams.getEvents(),
		nx::TextInfo(
			textParams.getTextInfoConst().getFontPathConst(),
			textParams.getTextInfoConst().getTextLabelConst(),
			textParams.getTextInfoConst().getFontSizeConst(),
			FrameworkRendering::RGBa_to_sfColor(textParams.getTextInfoConst().getTextColorConst()))
		);
	text->setVisible(guiParams.getActiveConst());
	this->_guiHandler->getLayerByName(layerId)->add(text);
	std::cout << "Adding new text (" << guiParams.getIdentifierConst() << ") in " << layerId << std::endl;
	return (true);
}

bool FrameworkRendering::addImage(const std::string& layerId, const nx::env::GUIElementInfos& guiParams, const nx::env::GUIImageInfos& imageParams)
{
	if (!this->_guiHandler->layer_exists(layerId) || this->_guiHandler->getLayerByName(layerId)->object_exists(guiParams.getIdentifierConst())) {
		return (false);
	}

	std::shared_ptr<nx::gui::Image> image = std::make_shared<nx::gui::Image>(
		sf::Vector2f(guiParams.getPosConst().x, guiParams.getPosConst().y),
		sf::Vector2f(guiParams.getSizeConst().x, guiParams.getSizeConst().y),
		guiParams.getIdentifierConst(),
		guiParams.getEvents(),
		imageParams.getImagePathConst()
		);
	image->setVisible(guiParams.getActiveConst());
	this->_guiHandler->getLayerByName(layerId)->add(image);
	std::cout << "Adding new image (" << guiParams.getIdentifierConst() << ") in " << layerId << std::endl;
	return (true);
}

bool FrameworkRendering::addGUISprite(const std::string& layerId, const nx::env::GUIElementInfos& guiParams, const nx::env::GUISpriteInfos& spriteParams)
{
	if (!this->_guiHandler->layer_exists(layerId) || this->_guiHandler->getLayerByName(layerId)->object_exists(guiParams.getIdentifierConst())) {
		return (false);
	}

	std::shared_ptr<nx::gui::Sprite> sprite = std::make_shared<nx::gui::Sprite>(
		sf::Vector2f(guiParams.getPosConst().x, guiParams.getPosConst().y),
		sf::Vector2f(guiParams.getSizeConst().x, guiParams.getSizeConst().y),
		guiParams.getIdentifierConst(),
		guiParams.getEvents(),
		spriteParams.getSpritesheetPathConst(),
		sf::Vector2f(spriteParams.getSheetGridConst().x, spriteParams.getSheetGridConst().y),
		sf::Vector2f(spriteParams.getSpriteSizeConst().x, spriteParams.getSpriteSizeConst().y)
		);
	sprite->setVisible(guiParams.getActiveConst());
	this->_guiHandler->getLayerByName(layerId)->add(sprite);
	std::cout << "Adding new guiSprite (" << guiParams.getIdentifierConst() << ") in " << layerId << std::endl;
	return (true);
}

bool FrameworkRendering::removeLayer(std::string const& layerId)
{
	return (this->_guiHandler->removeLayer(layerId));
}

bool FrameworkRendering::removeGUIElem(std::string const& layerId, std::string const& elemId)
{
	if (!this->_guiHandler->layer_exists(layerId)) {
		return (false);
	}

	std::shared_ptr<nx::gui::GUILayer> layer = this->_guiHandler->getLayerByName(layerId);

	if (layer)
		return (layer->remove(elemId));
	return (false);
}

bool FrameworkRendering::addGraphicsSprite(const nx::env::GraphicsElementInfos& graphicsParams, const nx::env::GraphicsSpriteInfos& spriteParams)
{
	if (this->_graphicsHandler->object_exists(graphicsParams.identifier)) {
		return (false);
	}

	std::shared_ptr<nx::graphics::Sprite> sprite = std::make_shared<nx::graphics::Sprite>(
		sf::Vector2f(graphicsParams.pos.x, graphicsParams.pos.y),
		sf::Vector2f(graphicsParams.size.x, graphicsParams.size.y),
		graphicsParams.identifier,
		spriteParams.spritesheetPath,
		sf::Vector2f(spriteParams.sheetGrid.x, spriteParams.sheetGrid.y),
		sf::Vector2f(spriteParams.spriteSize.x, spriteParams.spriteSize.y)
		);
	this->_graphicsHandler->addElement(sprite);
	std::cout << "Adding new graphicsSprite (" << graphicsParams.identifier << ")" << std::endl;
	return (true);
}

bool FrameworkRendering::addGraphicsCirleShape(const nx::env::GraphicsElementInfos& graphicsParams, const nx::env::GraphicsCircleInfos& circleShapeParams)
{
	if (this->_graphicsHandler->object_exists(graphicsParams.identifier)) {
		return (false);
	}
	
	std::shared_ptr<nx::graphics::CircleShape> circle = std::make_shared<nx::graphics::CircleShape>(
		sf::Vector2f(graphicsParams.pos.x, graphicsParams.pos.y),
		sf::Vector2f(graphicsParams.size.x, graphicsParams.size.y),
		graphicsParams.identifier,
		circleShapeParams.getRadiusConst(),
		nx::ColorInfo(
			FrameworkRendering::RGBa_to_sfColor(circleShapeParams.getColorInfoConst().getBackgroundColorConst()),
			FrameworkRendering::RGBa_to_sfColor(circleShapeParams.getColorInfoConst().getBorderColorConst()),
			circleShapeParams.getColorInfoConst().getBorderThicknessConst())
		);

	this->_graphicsHandler->addElement(circle);
	std::cout << "Adding new graphicsCircle (" << graphicsParams.identifier << ")" << std::endl;
	return (true);
}

bool FrameworkRendering::addGraphicsRectShape(const nx::env::GraphicsElementInfos& graphicsParams, const nx::env::GraphicsRectInfos& rectShapeParams)
{
	if (this->_graphicsHandler->object_exists(graphicsParams.identifier)) {
		return (false);
	}

	std::shared_ptr<nx::graphics::RectShape> rect = std::make_shared<nx::graphics::RectShape>(
		sf::Vector2f(graphicsParams.pos.x, graphicsParams.pos.y),
		sf::Vector2f(graphicsParams.size.x, graphicsParams.size.y),
		graphicsParams.identifier,
		nx::ColorInfo(
			FrameworkRendering::RGBa_to_sfColor(rectShapeParams.colorInfo.getBackgroundColorConst()),
			FrameworkRendering::RGBa_to_sfColor(rectShapeParams.colorInfo.getBorderColorConst()),
			rectShapeParams.colorInfo.getBorderThicknessConst())
		);

	this->_graphicsHandler->addElement(rect);
	std::cout << "Adding new graphicsRect (" << graphicsParams.identifier << ")" << std::endl;
	return (true);
}

bool FrameworkRendering::addGraphicsConvexShape(const nx::env::GraphicsElementInfos& graphicsParams, const nx::env::GraphicsConvexInfos& convexShapeParams)
{
	if (this->_graphicsHandler->object_exists(graphicsParams.identifier)) {
		return (false);
	}

	std::shared_ptr<nx::graphics::ConvexShape> convex = std::make_shared<nx::graphics::ConvexShape>(
		sf::Vector2f(graphicsParams.pos.x, graphicsParams.pos.y),
		sf::Vector2f(graphicsParams.size.x, graphicsParams.size.y),
		graphicsParams.identifier,
		nx::ColorInfo(
			FrameworkRendering::RGBa_to_sfColor(convexShapeParams.colorInfo.getBackgroundColorConst()),
			FrameworkRendering::RGBa_to_sfColor(convexShapeParams.colorInfo.getBorderColorConst()),
			convexShapeParams.colorInfo.getBorderThicknessConst())
		);

	this->_graphicsHandler->addElement(convex);
	std::cout << "Adding new graphicsConvex (" << graphicsParams.identifier << ")" << std::endl;
	return (true);
}

bool FrameworkRendering::removeGraphicsElem(std::string const& elemId)
{
	return (this->_graphicsHandler->removeElement(elemId));
}

nx::gui::GUIElement	*FrameworkRendering::_getGUIElementFromHandler(std::string const& layerId, std::string const& elemId) const
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(elemId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(elemId))
		throw nx::ElementNotFoundException(elemId);

	nx::gui::GUIElement *elem = this->_guiHandler->getLayerByName(layerId)->getElementByName(elemId).get();

	if (!elem)
		throw nx::NullElementException(elemId);

	return (elem);
}

nx::gui::Button		*FrameworkRendering::_getGUIButtonFromHandler(std::string const& layerId, std::string const& buttonId) const
{
	nx::gui::Button *button = dynamic_cast<nx::gui::Button *>(this->_getGUIElementFromHandler(layerId, buttonId));

	if (!button)
		throw nx::InvalidCastElementException(buttonId, "nx::gui::Button");

	return (button);
}

nx::gui::Checkbox		*FrameworkRendering::_getGUICheckboxFromHandler(std::string const& layerId, std::string const& checkboxId) const
{
	nx::gui::Checkbox *checkbox = dynamic_cast<nx::gui::Checkbox *>(this->_getGUIElementFromHandler(layerId, checkboxId));

	if (!checkbox)
		throw nx::InvalidCastElementException(checkboxId, "nx::gui::Checkbox");

	return (checkbox);
}

nx::gui::ProgressBar	*FrameworkRendering::_getGUIProgressBarFromHandler(std::string const& layerId, std::string const& progressBarId) const
{
	nx::gui::ProgressBar *progressBar = dynamic_cast<nx::gui::ProgressBar *>(this->_getGUIElementFromHandler(layerId, progressBarId));

	if (!progressBar)
		throw nx::InvalidCastElementException(progressBarId, "nx::gui::ProgressBar");

	return (progressBar);
}

nx::gui::ComboBox		*FrameworkRendering::_getGUIComboBoxFromHandler(std::string const& layerId, std::string const& comboBoxId) const
{
	nx::gui::ComboBox *comboBox = dynamic_cast<nx::gui::ComboBox *>(this->_getGUIElementFromHandler(layerId, comboBoxId));

	if (!comboBox)
		throw nx::InvalidCastElementException(comboBoxId, "nx::gui::ComboBox");

	return (comboBox);
}

nx::gui::TextInput		*FrameworkRendering::_getGUITextInputFromHandler(std::string const& layerId, std::string const& textInputId) const
{
	nx::gui::TextInput *textInput = dynamic_cast<nx::gui::TextInput *>(this->_getGUIElementFromHandler(layerId, textInputId));

	if (!textInput)
		throw nx::InvalidCastElementException(textInputId, "nx::gui::TextInput");

	return (textInput);
}

nx::gui::Text			*FrameworkRendering::_getGUITextFromHandler(std::string const& layerId, std::string const& textId) const
{
	nx::gui::Text *text = dynamic_cast<nx::gui::Text *>(this->_getGUIElementFromHandler(layerId, textId));

	if (!text)
		throw nx::InvalidCastElementException(textId, "nx::gui::Text");

	return (text);
}

nx::gui::Image			*FrameworkRendering::_getGUIImageFromHandler(std::string const& layerId, std::string const& imageId) const
{
	nx::gui::Image *image = dynamic_cast<nx::gui::Image *>(this->_getGUIElementFromHandler(layerId, imageId));

	if (!image)
		throw nx::InvalidCastElementException(imageId, "nx::gui::Image");

	return (image);
}

nx::gui::Sprite			*FrameworkRendering::_getGUISpriteFromHandler(std::string const& layerId, std::string const& spriteId) const
{
	nx::gui::Sprite *sprite = dynamic_cast<nx::gui::Sprite *>(this->_getGUIElementFromHandler(layerId, spriteId));

	if (!sprite)
		throw nx::InvalidCastElementException(spriteId, "nx::gui::Sprite");

	return (sprite);
}


nx::graphics::GraphicsElement	*FrameworkRendering::_getGraphicsElementFromHandler(std::string const& elemId) const
{
	if (!this->_graphicsHandler->object_exists(elemId))
		throw nx::ElementNotFoundException(elemId);

	nx::graphics::GraphicsElement *elem = this->_graphicsHandler->getElementByName(elemId).get();

	if (!elem)
		throw nx::NullElementException(elemId);

	return (elem);
}

nx::graphics::Sprite			*FrameworkRendering::_getGraphicsSpriteFromHandler(std::string const& spriteId) const
{
	nx::graphics::Sprite *sprite = dynamic_cast<nx::graphics::Sprite *>(this->_getGraphicsElementFromHandler(spriteId));

	if (!sprite)
		throw nx::InvalidCastElementException(spriteId, "nx::graphics::Sprite");

	return (sprite);
}

nx::graphics::CircleShape		*FrameworkRendering::_getGraphicsCircleShapeFromHandler(std::string const& circleShapeId) const
{
	nx::graphics::CircleShape *circleShape = dynamic_cast<nx::graphics::CircleShape *>(this->_getGraphicsElementFromHandler(circleShapeId));

	if (!circleShape)
		throw nx::InvalidCastElementException(circleShapeId, "nx::graphics::CircleShape");

	return (circleShape);
}

nx::graphics::RectShape			*FrameworkRendering::_getGraphicsRectShapeFromHandler(std::string const& rectShapeId) const
{
	nx::graphics::RectShape *rectShape = dynamic_cast<nx::graphics::RectShape *>(this->_getGraphicsElementFromHandler(rectShapeId));

	if (!rectShape)
		throw nx::InvalidCastElementException(rectShapeId, "nx::graphics::RectShape");

	return (rectShape);
}

nx::graphics::ConvexShape		*FrameworkRendering::_getGraphicsConvexShapeFromHandler(std::string const& convexShapeId) const
{
	nx::graphics::ConvexShape *convexShape = dynamic_cast<nx::graphics::ConvexShape *>(this->_getGraphicsElementFromHandler(convexShapeId));

	if (!convexShape)
		throw nx::InvalidCastElementException(convexShapeId, "nx::graphics::ConvexShape");

	return (convexShape);
}


void		FrameworkRendering::setVisibleToGUIElement(std::string const& layerId, std::string const& elemId, bool const isVisible)
{
	this->_getGUIButtonFromHandler(layerId, elemId)->setVisible(isVisible);
}

void		FrameworkRendering::setVisibleToGraphicsElement(std::string const& elemId, bool const isVisible)
{
	this->_getGraphicsElementFromHandler(elemId)->setVisible(isVisible);
}

std::string const	FrameworkRendering::getTypeFromGUIElement(std::string const& layerId, std::string const& elemId) const
{
	return (this->_getGUIElementFromHandler(layerId, elemId)->getType());
}

nx::maths::Vector2f const	FrameworkRendering::getPosFromGUIElement(std::string const& layerId, std::string const& elemId) const
{
	sf::Vector2f const& pos = this->_getGUIElementFromHandler(layerId, elemId)->getPos();
	return (nx::maths::Vector2f(pos.x, pos.y));
}

nx::maths::Vector2f const	FrameworkRendering::getSizeFromGUIElement(std::string const& layerId, std::string const& elemId) const
{
	sf::Vector2f const& size = this->_getGUIElementFromHandler(layerId, elemId)->getSize();
	return (nx::maths::Vector2f(size.x, size.y));
}

std::string const			FrameworkRendering::getTypeFromGraphicsElement(std::string const& elemId) const
{
	return (this->_getGraphicsElementFromHandler(elemId)->getType());
}

nx::maths::Vector2f const	FrameworkRendering::getPosFromGraphicsElement(std::string const& elemId) const
{
	sf::Vector2f const& pos = this->_getGraphicsElementFromHandler(elemId)->getPos();
	return (nx::maths::Vector2f(pos.x, pos.y));
}

nx::maths::Vector2f const	FrameworkRendering::getSizeFromGraphicsElement(std::string const& elemId) const
{
	sf::Vector2f const& size = this->_getGraphicsElementFromHandler(elemId)->getSize();
	return (nx::maths::Vector2f(size.x, size.y));
}


// Button

void FrameworkRendering::setStateToButton(std::string const& layerId, std::string const& buttonId, bool const state)
{
	this->_getGUIButtonFromHandler(layerId, buttonId)->setState(state);
}

void FrameworkRendering::setTextToButton(std::string const& layerId, std::string const& buttonId, std::string const& text)
{
	this->_getGUIButtonFromHandler(layerId, buttonId)->setText(text);
}

void FrameworkRendering::setFontSizeToButton(std::string const& layerId, std::string const& buttonId, unsigned int const fontSize)
{
	this->_getGUIButtonFromHandler(layerId, buttonId)->setFontSize(fontSize);
}

void FrameworkRendering::setColorNotSelectedToButton(std::string const& layerId, std::string const& buttonId, nx::env::RGBa const& color)
{
	this->_getGUIButtonFromHandler(layerId, buttonId)->setColorNotSelected(FrameworkRendering::RGBa_to_sfColor(color));
}

void FrameworkRendering::setColorSelectedToButton(std::string const& layerId, std::string const& buttonId, nx::env::RGBa const& color)
{
	this->_getGUIButtonFromHandler(layerId, buttonId)->setColorSelected(FrameworkRendering::RGBa_to_sfColor(color));
}

void FrameworkRendering::setBorderColorToButton(std::string const& layerId, std::string const& buttonId, nx::env::RGBa const& color)
{
	this->_getGUIButtonFromHandler(layerId, buttonId)->setBorderColor(FrameworkRendering::RGBa_to_sfColor(color));
}

void FrameworkRendering::setBorderThicknessToButton(std::string const& layerId, std::string const& buttonId, int const thickness)
{
	this->_getGUIButtonFromHandler(layerId, buttonId)->setBorderThickness(thickness);
}

void FrameworkRendering::setPosToButton(std::string const& layerId, std::string const& buttonId, nx::maths::Vector2f const& pos)
{
	this->_getGUIButtonFromHandler(layerId, buttonId)->setPos(sf::Vector2f(pos.x, pos.y));
}

void FrameworkRendering::setSizeToButton(std::string const& layerId, std::string const& buttonId, nx::maths::Vector2f const& size)
{
	this->_getGUIButtonFromHandler(layerId, buttonId)->setSize(sf::Vector2f(size.x, size.y));
}

bool const					FrameworkRendering::getStateFromButton(std::string const& layerId, std::string const& buttonId) const
{
	return (this->_getGUIButtonFromHandler(layerId, buttonId)->getState());
}

std::string const			FrameworkRendering::getTextFromButton(std::string const& layerId, std::string const& buttonId) const
{
	return (this->_getGUIButtonFromHandler(layerId, buttonId)->getText());
}

unsigned int const			FrameworkRendering::getFontSizeFromButton(std::string const& layerId, std::string const& buttonId) const
{
	return (this->_getGUIButtonFromHandler(layerId, buttonId)->getFontSize());
}

nx::env::RGBa const	FrameworkRendering::getColorNotSelectedFromButton(std::string const& layerId, std::string const& buttonId) const
{
	sf::Color const &color = this->_getGUIButtonFromHandler(layerId, buttonId)->getColorNotSelected();
	return (nx::env::RGBa(color.r, color.g, color.b, color.a));
}

nx::env::RGBa const	FrameworkRendering::getColorSelectedFromButton(std::string const& layerId, std::string const& buttonId) const
{
	sf::Color const &color = this->_getGUIButtonFromHandler(layerId, buttonId)->getColorSelected();
	return (nx::env::RGBa(color.r, color.g, color.b, color.a));
}

nx::env::RGBa const	FrameworkRendering::getBorderColorFromButton(std::string const& layerId, std::string const& buttonId) const
{
	sf::Color const &color = this->_getGUIButtonFromHandler(layerId, buttonId)->getBorderColor();
	return (nx::env::RGBa(color.r, color.g, color.b, color.a));
}

int const					FrameworkRendering::getBorderThicknessFromButton(std::string const& layerId, std::string const& buttonId) const
{
	return (this->_getGUIButtonFromHandler(layerId, buttonId)->getBorderThickness());
}


//Checkbox

void		FrameworkRendering::setStateToCheckbox(std::string const& layerId, std::string const& checkboxId, nx::env::CheckboxState const state)
{
	this->_getGUICheckboxFromHandler(layerId, checkboxId)->setState(static_cast<nx::gui::Checkbox::State>(state));
}

void		FrameworkRendering::setBackgroundColorToCheckbox(std::string const& layerId, std::string const& checkboxId, nx::env::RGBa const& color)
{
	this->_getGUICheckboxFromHandler(layerId, checkboxId)->setBackgroundColor(FrameworkRendering::RGBa_to_sfColor(color));
}

void		FrameworkRendering::setBorderColorToCheckbox(std::string const& layerId, std::string const& checkboxId, nx::env::RGBa const& color)
{
	this->_getGUICheckboxFromHandler(layerId, checkboxId)->setBorderColor(FrameworkRendering::RGBa_to_sfColor(color));
}
void		FrameworkRendering::setBorderThicknessToCheckbox(std::string const& layerId, std::string const& checkboxId, int const thickness)
{
	this->_getGUICheckboxFromHandler(layerId, checkboxId)->setBorderThickness(thickness);
}
void		FrameworkRendering::setPosToCheckbox(std::string const& layerId, std::string const& checkboxId, nx::maths::Vector2f const& pos)
{
	this->_getGUICheckboxFromHandler(layerId, checkboxId)->setPos(sf::Vector2f(pos.x, pos.y));
}
void		FrameworkRendering::setSizeToCheckbox(std::string const& layerId, std::string const& checkboxId, nx::maths::Vector2f const& size)
{
	this->_getGUICheckboxFromHandler(layerId, checkboxId)->setSize(sf::Vector2f(size.x, size.y));
}

nx::env::CheckboxState const	FrameworkRendering::getStateFromCheckbox(std::string const& layerId, std::string const& checkboxId) const
{
	return (static_cast<nx::env::CheckboxState>(this->_getGUICheckboxFromHandler(layerId, checkboxId)->getState()));
}
nx::env::RGBa const			FrameworkRendering::getBackgroundColorFromCheckbox(std::string const& layerId, std::string const& checkboxId) const
{
	sf::Color const &color = this->_getGUICheckboxFromHandler(layerId, checkboxId)->getBackgroundColor();
	return (nx::env::RGBa(color.r, color.g, color.b, color.a));
}
nx::env::RGBa const			FrameworkRendering::getBorderColorFromCheckbox(std::string const& layerId, std::string const& checkboxId) const
{
	sf::Color const &color = this->_getGUICheckboxFromHandler(layerId, checkboxId)->getBorderColor();
	return (nx::env::RGBa(color.r, color.g, color.b, color.a));
}
int const							FrameworkRendering::getBorderThicknessFromCheckbox(std::string const& layerId, std::string const& checkboxId) const
{
	return (this->_getGUICheckboxFromHandler(layerId, checkboxId)->getBorderThickness());
}


//CircleShape

void	FrameworkRendering::setBackgroundColorToCircleShape(std::string const& circleShapeId, nx::env::RGBa const& color)
{
	this->_getGraphicsCircleShapeFromHandler(circleShapeId)->setBackgroundColor(FrameworkRendering::RGBa_to_sfColor(color));
}

void	FrameworkRendering::setBorderColorToCircleShape(std::string const& circleShapeId, nx::env::RGBa const& color)
{
	this->_getGraphicsCircleShapeFromHandler(circleShapeId)->setBorderColor(FrameworkRendering::RGBa_to_sfColor(color));
}

void	FrameworkRendering::setBorderThicknessToCircleShape(std::string const& circleShapeId, int const thickness)
{
	this->_getGraphicsCircleShapeFromHandler(circleShapeId)->setBorderThickness(thickness);
}

void	FrameworkRendering::setRotationToCircleShape(std::string const& circleShapeId, float const angle)
{
	this->_getGraphicsCircleShapeFromHandler(circleShapeId)->setRotation(angle);
}

void	FrameworkRendering::setRadiusToCircleShape(std::string const& circleShapeId, float const radius)
{
	this->_getGraphicsCircleShapeFromHandler(circleShapeId)->setRadius(radius);
}

void	FrameworkRendering::setPosToCircleShape(std::string const& circleShapeId, nx::maths::Vector2f const& pos)
{
	this->_getGraphicsCircleShapeFromHandler(circleShapeId)->setPos(sf::Vector2f(pos.x, pos.y));
}

void	FrameworkRendering::setSizeToCircleShape(std::string const& circleShapeId, nx::maths::Vector2f const& size)
{
	this->_getGraphicsCircleShapeFromHandler(circleShapeId)->setSize(sf::Vector2f(size.x, size.y));
}

void	FrameworkRendering::setPointCountToCircleShape(std::string const& circleShapeId, size_t const count)
{
	this->_getGraphicsCircleShapeFromHandler(circleShapeId)->setPointCount(count);
}

void	FrameworkRendering::setScaleToCircleShape(std::string const& circleShapeId, nx::maths::Vector2f const& factor)
{
	this->_getGraphicsCircleShapeFromHandler(circleShapeId)->setScale(sf::Vector2f(factor.x, factor.y));
}
void	FrameworkRendering::setOriginToCircleShape(std::string const& circleShapeId, nx::maths::Vector2f const& origin)
{
	this->_getGraphicsCircleShapeFromHandler(circleShapeId)->setOrigin(sf::Vector2f(origin.x, origin.y));
}

void	FrameworkRendering::moveToCircleShape(std::string const& circleShapeId, nx::maths::Vector2f const& offset)
{
	this->_getGraphicsCircleShapeFromHandler(circleShapeId)->move(sf::Vector2f(offset.x, offset.y));
}

void	FrameworkRendering::rotateToCircleShape(std::string const& circleShapeId, float const angle)
{
	this->_getGraphicsCircleShapeFromHandler(circleShapeId)->rotate(angle);
}

void	FrameworkRendering::scaleToCircleShape(std::string const& circleShapeId, nx::maths::Vector2f const& factor)
{
	this->_getGraphicsCircleShapeFromHandler(circleShapeId)->scale(sf::Vector2f(factor.x, factor.y));
}

void	FrameworkRendering::setTextureToCircleShape(std::string const& circleShapeId, std::string const& texturePath, bool const resetRect)
{
	this->_getGraphicsCircleShapeFromHandler(circleShapeId)->setTexture(texturePath);
}

void	FrameworkRendering::setTextureRectToCircleShape(std::string const& circleShapeId, nx::maths::Rect const& rect)
{
	this->_getGraphicsCircleShapeFromHandler(circleShapeId)->setTextureRect(sf::IntRect(static_cast<int>(rect.position().x), static_cast<int>(rect.position().y), static_cast<int>(rect.width()), static_cast<int>(rect.height())));
}

nx::env::RGBa const	FrameworkRendering::getBackgroundColorFromCircleShape(std::string const& circleShapeId) const
{
	sf::Color const &color = this->_getGraphicsCircleShapeFromHandler(circleShapeId)->getBackgroundColor();
	return (nx::env::RGBa(color.r, color.g, color.b, color.a));
}

nx::env::RGBa const	FrameworkRendering::getBorderColorFromCircleShape(std::string const& circleShapeId) const
{
	sf::Color const &color = this->_getGraphicsCircleShapeFromHandler(circleShapeId)->getBorderColor();
	return (nx::env::RGBa(color.r, color.g, color.b, color.a));
}

int const					FrameworkRendering::getBorderThicknessFromCircleShape(std::string const& circleShapeId) const
{
	return (this->_getGraphicsCircleShapeFromHandler(circleShapeId)->getBorderThickness());
}

float const					FrameworkRendering::getRotationFromCircleShape(std::string const& circleShapeId) const
{
	return (this->_getGraphicsCircleShapeFromHandler(circleShapeId)->getRotation());
}

float const					FrameworkRendering::getRadiusFromCircleShape(std::string const& circleShapeId) const
{
	return (this->_getGraphicsCircleShapeFromHandler(circleShapeId)->getRadius());
}

size_t const						FrameworkRendering::getPointCountFromCircleShape(std::string const& circleShapeId) const
{
	return (this->_getGraphicsCircleShapeFromHandler(circleShapeId)->getPointCount());
}

nx::maths::Vector2f const					FrameworkRendering::getPointFromCircleShape(std::string const& circleShapeId, size_t const index) const
{
	sf::Vector2f point = this->_getGraphicsCircleShapeFromHandler(circleShapeId)->getPoint(index);
	return (nx::maths::Vector2f(point.x, point.y));
}

nx::maths::Rect const						FrameworkRendering::getTextureRectFromCircleShape(std::string const& circleShapeId) const
{
	sf::IntRect const& rect = this->_getGraphicsCircleShapeFromHandler(circleShapeId)->getTextureRect();
	return (nx::maths::Rect(nx::maths::Vector2f(static_cast<float>(rect.left), static_cast<float>(rect.top)), nx::maths::Vector2f(static_cast<float>(rect.width), static_cast<float>(rect.height))));
}

nx::maths::Vector2f const					FrameworkRendering::getScaleFromCircleShape(std::string const& circleShapeId) const
{
	sf::Vector2f const& scale = this->_getGraphicsCircleShapeFromHandler(circleShapeId)->getScale();
	return (nx::maths::Vector2f(scale.x, scale.y));
}

nx::maths::Vector2f const					FrameworkRendering::getOriginFromCircleShape(std::string const& circleShapeId) const
{
	sf::Vector2f const& origin = this->_getGraphicsCircleShapeFromHandler(circleShapeId)->getOrigin();
	return (nx::maths::Vector2f(origin.x, origin.y));
}


//ComboBox

void	FrameworkRendering::setBackgroundColorToComboBox(std::string const& layerId, std::string const& comboBoxId, nx::env::RGBa const& color)
{
	this->_getGUIComboBoxFromHandler(layerId, comboBoxId)->setBackgroundColor(FrameworkRendering::RGBa_to_sfColor(color));
}

void	FrameworkRendering::setBorderColorToComboBox(std::string const& layerId, std::string const& comboBoxId, nx::env::RGBa const& color)
{
	this->_getGUIComboBoxFromHandler(layerId, comboBoxId)->setBorderColor(FrameworkRendering::RGBa_to_sfColor(color));
}

void	FrameworkRendering::setBorderThicknessToComboBox(std::string const& layerId, std::string const& comboBoxId, int const thickness)
{
	this->_getGUIComboBoxFromHandler(layerId, comboBoxId)->setBorderThickness(thickness);
}

void	FrameworkRendering::setFontSizeToComboBox(std::string const& layerId, std::string const& comboBoxId, unsigned int const fontSize)
{
	this->_getGUIComboBoxFromHandler(layerId, comboBoxId)->setFontSize(fontSize);
}

void	FrameworkRendering::addSelectionToComboBox(std::string const& layerId, std::string const& comboBoxId, std::string const& selection)
{
	this->_getGUIComboBoxFromHandler(layerId, comboBoxId)->addSelection(selection);
}

void	FrameworkRendering::removeSelectionToComboBox(std::string const& layerId, std::string const& comboBoxId, std::string const& selection, uint16_t const nbTimes)
{
	this->_getGUIComboBoxFromHandler(layerId, comboBoxId)->removeSelection(selection, nbTimes);
}

void	FrameworkRendering::removeSelectionToComboBox(std::string const& layerId, std::string const& comboBoxId, uint16_t const idx, uint16_t const nbTimes)
{
	this->_getGUIComboBoxFromHandler(layerId, comboBoxId)->removeSelection(idx, nbTimes);
}

void	FrameworkRendering::clearSelectionsToComboBox(std::string const& layerId, std::string const& comboBoxId)
{
	this->_getGUIComboBoxFromHandler(layerId, comboBoxId)->clearSelections();
}

void	FrameworkRendering::setPosToComboBox(std::string const& layerId, std::string const& comboBoxId, nx::maths::Vector2f const& pos)
{
	this->_getGUIComboBoxFromHandler(layerId, comboBoxId)->setPos(sf::Vector2f(pos.x, pos.y));
}

void	FrameworkRendering::setSizeToComboBox(std::string const& layerId, std::string const& comboBoxId, nx::maths::Vector2f const& size)
{
	this->_getGUIComboBoxFromHandler(layerId, comboBoxId)->setSize(sf::Vector2f(size.x, size.y));
}

nx::env::RGBa const	FrameworkRendering::getBackgroundColorFromComboBox(std::string const& layerId, std::string const& comboBoxId) const
{
	sf::Color const &color = this->_getGUIComboBoxFromHandler(layerId, comboBoxId)->getBackgroundColor();
	return (nx::env::RGBa(color.r, color.g, color.b, color.a));
}

nx::env::RGBa const	FrameworkRendering::getBorderColorFromComboBox(std::string const& layerId, std::string const& comboBoxId) const
{
	sf::Color const &color = this->_getGUIComboBoxFromHandler(layerId, comboBoxId)->getBorderColor();
	return (nx::env::RGBa(color.r, color.g, color.b, color.a));
}

int const					FrameworkRendering::getBorderThicknessFromComboBox(std::string const& layerId, std::string const& comboBoxId) const
{
	return (this->_getGUIComboBoxFromHandler(layerId, comboBoxId)->getBorderThickness());
}

unsigned int const			FrameworkRendering::getFontSizeFromComboBox(std::string const& layerId, std::string const& comboBoxId) const
{
	return (this->_getGUIComboBoxFromHandler(layerId, comboBoxId)->getFontSize());
}

std::string const			FrameworkRendering::getSelectedFromComboBox(std::string const& layerId, std::string const& comboBoxId) const
{
	return (this->_getGUIComboBoxFromHandler(layerId, comboBoxId)->getSelected());
}

uint16_t const				FrameworkRendering::getIdxSelectedFromComboBox(std::string const& layerId, std::string const& comboBoxId) const
{
	return (this->_getGUIComboBoxFromHandler(layerId, comboBoxId)->getIdxSelected());
}


//ConvexShape

void	FrameworkRendering::setBackgroundColorToConvexShape(std::string const& convexShapeId, nx::env::RGBa const& color)
{
	this->_getGraphicsConvexShapeFromHandler(convexShapeId)->setBackgroundColor(FrameworkRendering::RGBa_to_sfColor(color));
}

void	FrameworkRendering::setBorderColorToConvexShape(std::string const& convexShapeId, nx::env::RGBa const& color)
{
	this->_getGraphicsConvexShapeFromHandler(convexShapeId)->setBorderColor(FrameworkRendering::RGBa_to_sfColor(color));
}
void	FrameworkRendering::setBorderThicknessToConvexShape(std::string const& convexShapeId, int const thickness)
{
	this->_getGraphicsConvexShapeFromHandler(convexShapeId)->setBorderThickness(thickness);
;}
void	FrameworkRendering::setRotationToConvexShape(std::string const& convexShapeId, float const angle)
{
	this->_getGraphicsConvexShapeFromHandler(convexShapeId)->setRotation(angle);
}

void	FrameworkRendering::setPointCountToConvexShape(std::string const& convexShapeId, size_t const pointCount)
{
	this->_getGraphicsConvexShapeFromHandler(convexShapeId)->setPointCount(pointCount);
}

void	FrameworkRendering::setPointToConvexShape(std::string const& convexShapeId, size_t const index, nx::maths::Vector2f const& point)
{
	this->_getGraphicsConvexShapeFromHandler(convexShapeId)->setPoint(index, sf::Vector2f(point.x, point.y));
}

void	FrameworkRendering::setScaleToConvexShape(std::string const& convexShapeId, nx::maths::Vector2f const& factor)
{
	this->_getGraphicsConvexShapeFromHandler(convexShapeId)->setScale(sf::Vector2f(factor.x, factor.y));
}

void	FrameworkRendering::setOriginToConvexShape(std::string const& convexShapeId, nx::maths::Vector2f const& origin)
{
	this->_getGraphicsConvexShapeFromHandler(convexShapeId)->setOrigin(sf::Vector2f(origin.x, origin.y));
}

void	FrameworkRendering::moveToConvexShape(std::string const& convexShapeId, nx::maths::Vector2f const& offset)
{
	this->_getGraphicsConvexShapeFromHandler(convexShapeId)->move(sf::Vector2f(offset.x, offset.y));
}

void	FrameworkRendering::rotateToConvexShape(std::string const& convexShapeId, float const angle)
{
	this->_getGraphicsConvexShapeFromHandler(convexShapeId)->rotate(angle);
}

void	FrameworkRendering::scaleToConvexShape(std::string const& convexShapeId, nx::maths::Vector2f const& factor)
{
	this->_getGraphicsConvexShapeFromHandler(convexShapeId)->scale(sf::Vector2f(factor.x, factor.y));
}

void	FrameworkRendering::setTextureToConvexShape(std::string const& convexShapeId, std::string const& texturePath, bool const resetRect)
{
	this->_getGraphicsConvexShapeFromHandler(convexShapeId)->setTexture(texturePath, resetRect);
}

void	FrameworkRendering::setTextureRectToConvexShape(std::string const& convexShapeId, nx::maths::Rect const& rect)
{
	this->_getGraphicsConvexShapeFromHandler(convexShapeId)->setTextureRect(sf::IntRect(static_cast<int>(rect.position().x), static_cast<int>(rect.position().y), static_cast<int>(rect.width()), static_cast<int>(rect.height())));
}

void	FrameworkRendering::setPosToConvexShape(std::string const& convexShapeId, nx::maths::Vector2f const& pos)
{
	this->_getGraphicsConvexShapeFromHandler(convexShapeId)->setPos(sf::Vector2f(pos.x, pos.y));
}

void	FrameworkRendering::setSizeToConvexShape(std::string const& convexShapeId, nx::maths::Vector2f const& size)
{
	this->_getGraphicsConvexShapeFromHandler(convexShapeId)->setSize(sf::Vector2f(size.x, size.y));
}


nx::env::RGBa const	FrameworkRendering::getBackgroundColorFromConvexShape(std::string const& convexShapeId) const
{
	sf::Color const &color = this->_getGraphicsConvexShapeFromHandler(convexShapeId)->getBackgroundColor();
	return (nx::env::RGBa(color.r, color.g, color.b, color.a));
}

nx::env::RGBa const	FrameworkRendering::getBorderColorFromConvexShape(std::string const& convexShapeId) const
{
	sf::Color const &color = this->_getGraphicsConvexShapeFromHandler(convexShapeId)->getBorderColor();
	return (nx::env::RGBa(color.r, color.g, color.b, color.a));
}

int const					FrameworkRendering::getBorderThicknessFromConvexShape(std::string const& convexShapeId) const
{
	return (this->_getGraphicsConvexShapeFromHandler(convexShapeId)->getBorderThickness());
}

float const					FrameworkRendering::getRotationFromConvexShape(std::string const& convexShapeId) const
{
	return (this->_getGraphicsConvexShapeFromHandler(convexShapeId)->getRotation());
}

size_t const				FrameworkRendering::getPointCountFromConvexShape(std::string const& convexShapeId) const
{
	return (this->_getGraphicsConvexShapeFromHandler(convexShapeId)->getPointCount());
}

nx::maths::Vector2f const			FrameworkRendering::getPointFromConvexShape(std::string const& convexShapeId, size_t const index) const
{
	sf::Vector2f point(this->_getGraphicsConvexShapeFromHandler(convexShapeId)->getPoint(index));
	return (nx::maths::Vector2f(point.x, point.y));
}

nx::maths::Rect const			FrameworkRendering::getTextureRectFromConvexShape(std::string const& convexShapeId) const
{
	sf::IntRect const& rect = this->_getGraphicsConvexShapeFromHandler(convexShapeId)->getTextureRect();
	return (nx::maths::Rect(nx::maths::Vector2f(static_cast<float>(rect.left), static_cast<float>(rect.top)), nx::maths::Vector2f(static_cast<float>(rect.width), static_cast<float>(rect.height))));
}

nx::maths::Vector2f const		FrameworkRendering::getScaleFromConvexShape(std::string const& convexShapeId) const
{
	sf::Vector2f const& scale = this->_getGraphicsConvexShapeFromHandler(convexShapeId)->getScale();
	return (nx::maths::Vector2f(scale.x, scale.y));
}

nx::maths::Vector2f const		FrameworkRendering::getOriginFromConvexShape(std::string const& convexShapeId) const
{
	sf::Vector2f const& origin = this->_getGraphicsConvexShapeFromHandler(convexShapeId)->getOrigin();
	return (nx::maths::Vector2f(origin.x, origin.y));
}

//Image

void	FrameworkRendering::setImagePathToImage(std::string const& layerId, std::string const& imageId, std::string const& spritePath)
{
	this->_getGUIImageFromHandler(layerId, imageId)->setImagePath(spritePath);
}

void	FrameworkRendering::setPosToImage(std::string const& layerId, std::string const& imageId, nx::maths::Vector2f const& pos)
{
	this->_getGUIImageFromHandler(layerId, imageId)->setPos(sf::Vector2f(pos.x, pos.y));
}

void	FrameworkRendering::setSizeToImage(std::string const& layerId, std::string const& imageId, nx::maths::Vector2f const& size)
{
	this->_getGUIImageFromHandler(layerId, imageId)->setSize(sf::Vector2f(size.x, size.y));
}

std::string const		FrameworkRendering::getImagePathFromImage(std::string const& layerId, std::string const& imageId) const
{
	return (std::string(this->_getGUIImageFromHandler(layerId, imageId)->getImagePath()));
}


//ProgressBar
void		FrameworkRendering::setBackgroundColorToProgressBar(std::string const& layerId, std::string const& progressBarId, nx::env::RGBa const& color)
{
	this->_getGUIProgressBarFromHandler(layerId, progressBarId)->setBackgroundColor(FrameworkRendering::RGBa_to_sfColor(color));
}

void		FrameworkRendering::setBorderColorToProgressBar(std::string const& layerId, std::string const& progressBarId, nx::env::RGBa const& color)
{
	this->_getGUIProgressBarFromHandler(layerId, progressBarId)->setBorderColor(FrameworkRendering::RGBa_to_sfColor(color));
}

void		FrameworkRendering::setBorderThicknessToProgressBar(std::string const& layerId, std::string const& progressBarId, int const thickness)
{
	this->_getGUIProgressBarFromHandler(layerId, progressBarId)->setBorderThickness(thickness);
}

void		FrameworkRendering::setFilledToProgressBar(std::string const& layerId, std::string const& progressBarId, int const percentage)
{
	this->_getGUIProgressBarFromHandler(layerId, progressBarId)->setFilled(percentage);
}

void		FrameworkRendering::setFontSizeToProgressBar(std::string const& layerId, std::string const& progressBarId, unsigned int const fontSize)
{
	this->_getGUIProgressBarFromHandler(layerId, progressBarId)->setFontSize(fontSize);
}

void		FrameworkRendering::setPosToProgressBar(std::string const& layerId, std::string const& progressBarId, nx::maths::Vector2f const& pos)
{
	this->_getGUIProgressBarFromHandler(layerId, progressBarId)->setPos(sf::Vector2f(pos.x, pos.y));
}

void		FrameworkRendering::setSizeToProgressBar(std::string const& layerId, std::string const& progressBarId, nx::maths::Vector2f const& size)
{
	this->_getGUIProgressBarFromHandler(layerId, progressBarId)->setSize(sf::Vector2f(size.x, size.y));
}

nx::env::RGBa const	FrameworkRendering::getBackgroundColorFromProgressBar(std::string const& layerId, std::string const& progressBarId) const
{
	sf::Color const &color = this->_getGUIProgressBarFromHandler(layerId, progressBarId)->getBackgroundColor();
	return (nx::env::RGBa(color.r, color.g, color.b, color.a));
}

nx::env::RGBa const	FrameworkRendering::getBorderColorFromProgressBar(std::string const& layerId, std::string const& progressBarId) const
{
	sf::Color const &color = this->_getGUIProgressBarFromHandler(layerId, progressBarId)->getBorderColor();
	return (nx::env::RGBa(color.r, color.g, color.b, color.a));
}

int const					FrameworkRendering::getBorderThicknessFromProgressBar(std::string const& layerId, std::string const& progressBarId) const
{
	return (this->_getGUIProgressBarFromHandler(layerId, progressBarId)->getBorderThickness());
}

int const					FrameworkRendering::getFilledFromProgressBar(std::string const& layerId, std::string const& progressBarId) const
{
	return (this->_getGUIProgressBarFromHandler(layerId, progressBarId)->getFilled());
}

unsigned int const			FrameworkRendering::getFontSizeFromProgressBar(std::string const& layerId, std::string const& progressBarId) const
{
	return (this->_getGUIProgressBarFromHandler(layerId, progressBarId)->getFontSize());
}


//RectShape

void	FrameworkRendering::setBackgroundColorToRectShape(std::string const& rectShapeId, nx::env::RGBa const& color)
{
	this->_getGraphicsRectShapeFromHandler(rectShapeId)->setBackgroundColor(RGBa_to_sfColor(color));
}

void	FrameworkRendering::setBorderColorToRectShape(std::string const& rectShapeId, nx::env::RGBa const& color)
{
	this->_getGraphicsRectShapeFromHandler(rectShapeId)->setBorderColor(RGBa_to_sfColor(color));
}

void	FrameworkRendering::setBorderThicknessToRectShape(std::string const& rectShapeId, int const thickness)
{
	this->_getGraphicsRectShapeFromHandler(rectShapeId)->setBorderThickness(thickness);
}

void	FrameworkRendering::setRotationToRectShape(std::string const& rectShapeId, float const angle)
{
	this->_getGraphicsRectShapeFromHandler(rectShapeId)->setRotation(angle);
}

void	FrameworkRendering::setScaleToRectShape(std::string const& rectShapeId, nx::maths::Vector2f const& factor)
{
	this->_getGraphicsRectShapeFromHandler(rectShapeId)->setScale(sf::Vector2f(factor.x, factor.y));
}

void	FrameworkRendering::setOriginToRectShape(std::string const& rectShapeId, nx::maths::Vector2f const& origin)
{
	this->_getGraphicsRectShapeFromHandler(rectShapeId)->setOrigin(sf::Vector2f(origin.x, origin.y));
}

void	FrameworkRendering::moveToRectShape(std::string const& rectShapeId, nx::maths::Vector2f const& offset)
{
	this->_getGraphicsRectShapeFromHandler(rectShapeId)->move(sf::Vector2f(offset.x, offset.y));
}

void	FrameworkRendering::rotateToRectShape(std::string const& rectShapeId, float const angle)
{
	this->_getGraphicsRectShapeFromHandler(rectShapeId)->rotate(angle);
}

void	FrameworkRendering::scaleToRectShape(std::string const& rectShapeId, nx::maths::Vector2f const& factor)
{
	this->_getGraphicsRectShapeFromHandler(rectShapeId)->scale(sf::Vector2f(factor.x, factor.y));
}

void	FrameworkRendering::setTextureToRectShape(std::string const& rectShapeId, std::string const& texturePath, bool const resetRect)
{
	this->_getGraphicsRectShapeFromHandler(rectShapeId)->setTexture(texturePath, resetRect);
}

void	FrameworkRendering::setTextureRectToRectShape(std::string const& rectShapeId, nx::maths::Rect const& rect)
{
	this->_getGraphicsRectShapeFromHandler(rectShapeId)->setTextureRect(sf::IntRect(static_cast<int>(rect.position().x), static_cast<int>(rect.position().y), static_cast<int>(rect.width()), static_cast<int>(rect.height())));
}

void	FrameworkRendering::setPosToRectShape(std::string const& rectShapeId, nx::maths::Vector2f const& pos)
{
	this->_getGraphicsRectShapeFromHandler(rectShapeId)->setPos(sf::Vector2f(pos.x, pos.y));
}

void	FrameworkRendering::setSizeToRectShape(std::string const& rectShapeId, nx::maths::Vector2f const& size)
{
	this->_getGraphicsRectShapeFromHandler(rectShapeId)->setSize(sf::Vector2f(size.x, size.y));
}

nx::env::RGBa const	FrameworkRendering::getBackgroundColorFromRectShape(std::string const& rectShapeId) const
{
	sf::Color const &color = this->_getGraphicsRectShapeFromHandler(rectShapeId)->getBackgroundColor();
	return (nx::env::RGBa(color.r, color.g, color.b, color.a));
}

nx::env::RGBa const	FrameworkRendering::getBorderColorFromRectShape(std::string const& rectShapeId) const
{
	sf::Color const &color = this->_getGraphicsRectShapeFromHandler(rectShapeId)->getBorderColor();
	return (nx::env::RGBa(color.r, color.g, color.b, color.a));
}

int const					FrameworkRendering::getBorderThicknessFromRectShape(std::string const& rectShapeId) const
{
	return (this->_getGraphicsRectShapeFromHandler(rectShapeId)->getBorderThickness());
}

float const					FrameworkRendering::getRotationFromRectShape(std::string const& rectShapeId) const
{
	return (this->_getGraphicsRectShapeFromHandler(rectShapeId)->getRotation());
}

size_t const				FrameworkRendering::getPointCountFromRectShape(std::string const& rectShapeId) const
{
	return (this->_getGraphicsRectShapeFromHandler(rectShapeId)->getPointCount());
}

nx::maths::Vector2f const	FrameworkRendering::getPointFromRectShape(std::string const& rectShapeId, size_t const index) const
{
	sf::Vector2f const point = this->_getGraphicsRectShapeFromHandler(rectShapeId)->getPoint(index);
	return (nx::maths::Vector2f(point.x, point.y));
}

nx::maths::Rect const		FrameworkRendering::getTextureRectFromRectShape(std::string const& rectShapeId) const
{
	sf::IntRect const& textureRect = this->_getGraphicsRectShapeFromHandler(rectShapeId)->getTextureRect();
	return (nx::maths::Rect(nx::maths::Vector2f(static_cast<float>(textureRect.left), static_cast<float>(textureRect.top)), nx::maths::Vector2f(static_cast<float>(textureRect.width), static_cast<float>(textureRect.height))));
}

nx::maths::Vector2f const	FrameworkRendering::getScaleFromRectShape(std::string const& rectShapeId) const
{
	sf::Vector2f const& scale = this->_getGraphicsRectShapeFromHandler(rectShapeId)->getScale();
	return (nx::maths::Vector2f(scale.x, scale.y));
}

nx::maths::Vector2f const	FrameworkRendering::getOriginFromRectShape(std::string const& rectShapeId) const
{
	sf::Vector2f const& origin = this->_getGraphicsRectShapeFromHandler(rectShapeId)->getOrigin();
	return (nx::maths::Vector2f(origin.x, origin.y));
}


//GraphicsSprite

void	FrameworkRendering::setSpritesheetPathToGraphicsSprite(std::string const& spriteId, std::string const& spritesheetPath)
{
	this->_getGraphicsSpriteFromHandler(spriteId)->setSpritesheetPath(spritesheetPath);
}

void	FrameworkRendering::setSpriteIdxToGraphicsSprite(std::string const& spriteId, uint16_t const spriteIdx)
{
	this->_getGraphicsSpriteFromHandler(spriteId)->setSpriteIdx(spriteIdx);
}

void	FrameworkRendering::setSlownessToGraphicsSprite(std::string const& spriteId, uint16_t const slowness)
{
	this->_getGraphicsSpriteFromHandler(spriteId)->setSlowness(slowness);
}

void	FrameworkRendering::setAnimateToGraphicsSprite(std::string const& spriteId, bool const animate)
{
	this->_getGraphicsSpriteFromHandler(spriteId)->setAnimate(animate);
}

void	FrameworkRendering::setSpritesAnimatedToGraphicsSprite(std::string const& spriteId, std::vector<uint16_t> const& spritesAnimated)
{
	this->_getGraphicsSpriteFromHandler(spriteId)->setSpritesAnimated(spritesAnimated);
}

void	FrameworkRendering::setAnimationIdxToGraphicsSprite(std::string const& spriteId, uint16_t const animationIdx)
{
	this->_getGraphicsSpriteFromHandler(spriteId)->setAnimationIdx(animationIdx);
}

void	FrameworkRendering::setPosToGraphicsSprite(std::string const& spriteId, nx::maths::Vector2f const& pos)
{
	this->_getGraphicsSpriteFromHandler(spriteId)->setPos(sf::Vector2f(pos.x, pos.y));
}

void	FrameworkRendering::setSizeToGraphicsSprite(std::string const& spriteId, nx::maths::Vector2f const& size)
{
	this->_getGraphicsSpriteFromHandler(spriteId)->setSize(sf::Vector2f(size.x, size.y));
}


std::string const &				FrameworkRendering::getSpritesheetPathFromGraphicsSprite(std::string const& spriteId) const
{
	return (this->_getGraphicsSpriteFromHandler(spriteId)->getSpritesheetPath());
}

uint16_t const					FrameworkRendering::getSpriteIdxFromGraphicsSprite(std::string const& spriteId) const
{
	return (this->_getGraphicsSpriteFromHandler(spriteId)->getSpriteIdx());
}

uint16_t const					FrameworkRendering::getSlownessFromGraphicsSprite(std::string const& spriteId) const
{
	return (this->_getGraphicsSpriteFromHandler(spriteId)->getSlowness());
}

bool const						FrameworkRendering::getAnimateFromGraphicsSprite(std::string const& spriteId) const
{
	return (this->_getGraphicsSpriteFromHandler(spriteId)->getAnimate());
}

std::vector<uint16_t> const &	FrameworkRendering::getSpritesAnimatedFromGraphicsSprite(std::string const& spriteId) const
{
	return (this->_getGraphicsSpriteFromHandler(spriteId)->getSpritesAnimated());
}

uint16_t const					FrameworkRendering::getAnimationIdxFromGraphicsSprite(std::string const& spriteId) const
{
	return (this->_getGraphicsSpriteFromHandler(spriteId)->getAnimationIdx());
}


//GUISprite

void	FrameworkRendering::setSpritesheetPathToGUISprite(std::string const& layerId, std::string const& spriteId, std::string const& spritesheetPath)
{
	this->_getGUISpriteFromHandler(layerId, spriteId)->setSpritesheetPath(spritesheetPath);
}

void	FrameworkRendering::setSpriteIdxToGUISprite(std::string const& layerId, std::string const& spriteId, uint16_t const spriteIdx)
{
	this->_getGUISpriteFromHandler(layerId, spriteId)->setSpriteIdx(spriteIdx);
}

void	FrameworkRendering::setSlownessToGUISprite(std::string const& layerId, std::string const& spriteId, uint16_t const slowness)
{
	this->_getGUISpriteFromHandler(layerId, spriteId)->setSlowness(slowness);
}

void	FrameworkRendering::setAnimateToGUISprite(std::string const& layerId, std::string const& spriteId, bool const animate)
{
	this->_getGUISpriteFromHandler(layerId, spriteId)->setAnimate(animate);
}

void	FrameworkRendering::setSpritesAnimatedToGUISprite(std::string const& layerId, std::string const& spriteId, std::vector<uint16_t> const& spritesAnimated)
{
	this->_getGUISpriteFromHandler(layerId, spriteId)->setSpritesAnimated(spritesAnimated);
}

void	FrameworkRendering::setAnimationIdxToGUISprite(std::string const& layerId, std::string const& spriteId, uint16_t const animationIdx)
{
	this->_getGUISpriteFromHandler(layerId, spriteId)->setAnimationIdx(animationIdx);
}

void	FrameworkRendering::setPosToGUISprite(std::string const& layerId, std::string const& spriteId, nx::maths::Vector2f const& pos)
{
	this->_getGUISpriteFromHandler(layerId, spriteId)->setPos(sf::Vector2f(pos.x, pos.y));
}

void	FrameworkRendering::setSizeToGUISprite(std::string const& layerId, std::string const& spriteId, nx::maths::Vector2f const& size)
{
	this->_getGUISpriteFromHandler(layerId, spriteId)->setSize(sf::Vector2f(size.x, size.y));
}


std::string const &				FrameworkRendering::getSpritesheetPathFromGUISprite(std::string const& layerId, std::string const& spriteId) const
{
	return (this->_getGUISpriteFromHandler(layerId, spriteId)->getSpritesheetPath());
}

uint16_t const					FrameworkRendering::getSpriteIdxFromGUISprite(std::string const& layerId, std::string const& spriteId) const
{
	return (this->_getGUISpriteFromHandler(layerId, spriteId)->getSpriteIdx());
}

uint16_t const					FrameworkRendering::getSlownessFromGUISprite(std::string const& layerId, std::string const& spriteId) const
{
	return (this->_getGUISpriteFromHandler(layerId, spriteId)->getSlowness());
}

bool const						FrameworkRendering::getAnimateFromGUISprite(std::string const& layerId, std::string const& spriteId) const
{
	return (this->_getGUISpriteFromHandler(layerId, spriteId)->getAnimate());
}

std::vector<uint16_t> const &	FrameworkRendering::getSpritesAnimatedFromGUISprite(std::string const& layerId, std::string const& spriteId) const
{
	return (this->_getGUISpriteFromHandler(layerId, spriteId)->getSpritesAnimated());
}

uint16_t const					FrameworkRendering::getAnimationIdxFromGUISprite(std::string const& layerId, std::string const& spriteId) const
{
	return (this->_getGUISpriteFromHandler(layerId, spriteId)->getAnimationIdx());
}


//Text

void FrameworkRendering::setTextToText(std::string const& layerId, std::string const& textId, std::string const& text)
{
	this->_getGUITextFromHandler(layerId, textId)->setText(text);
}

void FrameworkRendering::setFontSizeToText(std::string const& layerId, std::string const& textId, unsigned int const fontSize)
{
	this->_getGUITextFromHandler(layerId, textId)->setFontSize(fontSize);
}

void FrameworkRendering::setPosToText(std::string const& layerId, std::string const& textId, nx::maths::Vector2f const& pos)
{
	this->_getGUITextFromHandler(layerId, textId)->setPos(sf::Vector2f(pos.x, pos.y));
}

void FrameworkRendering::setSizeToText(std::string const& layerId, std::string const& textId, nx::maths::Vector2f const& size)
{
	this->_getGUITextFromHandler(layerId, textId)->setSize(sf::Vector2f(size.x, size.y));
}

std::string const	FrameworkRendering::getTextFromText(std::string const& layerId, std::string const& textId) const
{
	return (this->_getGUITextFromHandler(layerId, textId)->getText());
}

unsigned int const	FrameworkRendering::getFontSizeFromText(std::string const& layerId, std::string const& textId) const
{
	return (this->_getGUITextFromHandler(layerId, textId)->getFontSize());
}

//TextInput

void	FrameworkRendering::setStateToTextInput(std::string const& layerId, std::string const& textInputId, bool const state)
{
	this->_getGUITextInputFromHandler(layerId, textInputId)->setState(state);
}

void	FrameworkRendering::setBackgroundColorToTextInput(std::string const& layerId, std::string const& textInputId, nx::env::RGBa const& color)
{
	this->_getGUITextInputFromHandler(layerId, textInputId)->setBackgroundColor(FrameworkRendering::RGBa_to_sfColor(color));
}

void	FrameworkRendering::setBorderColorToTextInput(std::string const& layerId, std::string const& textInputId, nx::env::RGBa const& color)
{
	this->_getGUITextInputFromHandler(layerId, textInputId)->setBorderColor(FrameworkRendering::RGBa_to_sfColor(color));
}

void	FrameworkRendering::setBorderThicknessToTextInput(std::string const& layerId, std::string const& textInputId, int const thickness)
{
	this->_getGUITextInputFromHandler(layerId, textInputId)->setBorderThickness(thickness);
}

void	FrameworkRendering::setTextToTextInput(std::string const& layerId, std::string const& textInputId, std::string const& text)
{
	this->_getGUITextInputFromHandler(layerId, textInputId)->setText(text);
}

void	FrameworkRendering::setCursorIdxToTextInput(std::string const& layerId, std::string const& textInputId, unsigned int idx)
{
	this->_getGUITextInputFromHandler(layerId, textInputId)->setCursorIdx(idx);
}

void	FrameworkRendering::setPosToTextInput(std::string const& layerId, std::string const& textInputId, nx::maths::Vector2f const& pos)
{
	this->_getGUITextInputFromHandler(layerId, textInputId)->setPos(sf::Vector2f(pos.x, pos.y));
}

void	FrameworkRendering::setSizeToTextInput(std::string const& layerId, std::string const& textInputId, nx::maths::Vector2f const& size)
{
	this->_getGUITextInputFromHandler(layerId, textInputId)->setSize(sf::Vector2f(size.x, size.y));
}

bool const					FrameworkRendering::getStateFromTextInput(std::string const& layerId, std::string const& textInputId) const
{
	return (this->_getGUITextInputFromHandler(layerId, textInputId)->getState());
}

nx::env::RGBa const	FrameworkRendering::getBackgroundColorFromTextInput(std::string const& layerId, std::string const& textInputId) const
{
	sf::Color const &color = this->_getGUITextInputFromHandler(layerId, textInputId)->getBackgroundColor();
	return (nx::env::RGBa(color.r, color.g, color.b, color.a));
}

nx::env::RGBa const	FrameworkRendering::getBorderColorFromTextInput(std::string const& layerId, std::string const& textInputId) const
{
	sf::Color const &color = this->_getGUITextInputFromHandler(layerId, textInputId)->getBorderColor();
	return (nx::env::RGBa(color.r, color.g, color.b, color.a));
}

int const					FrameworkRendering::getBorderThicknessFromTextInput(std::string const& layerId, std::string const& textInputId) const
{
	return (this->_getGUITextInputFromHandler(layerId, textInputId)->getBorderThickness());
}

std::string const &			FrameworkRendering::getTextFromTextInput(std::string const& layerId, std::string const& textInputId) const
{
	return (this->_getGUITextInputFromHandler(layerId, textInputId)->getText());
}

unsigned int const			FrameworkRendering::getCursorIdxFromTextInput(std::string const& layerId, std::string const& textInputId) const
{
	return (this->_getGUITextInputFromHandler(layerId, textInputId)->getCursorIdx());
}

//Sound

bool	FrameworkRendering::addSound(const std::string & name)
{
return (this->_sfxHandler->addSound(name));
}

void	FrameworkRendering::removeSound(const std::string & name)
{
this->_sfxHandler->removeSound(name);
}

void	FrameworkRendering::playSound(const std::string & name)
{
this->_sfxHandler->playSound(name);
}

void	FrameworkRendering::pauseSound(const std::string & name)
{
this->_sfxHandler->pauseSound(name);
}

void	FrameworkRendering::stopSound(const std::string & name)
{
this->_sfxHandler->stopSound(name);
}

void 	FrameworkRendering::setSoundLoop(const std::string & name, const bool loop)
{
this->_sfxHandler->setSoundLoop(name, loop);
}

void 	FrameworkRendering::setSoundPitch(const std::string & name, const float pitch)
{
this->_sfxHandler->setSoundPitch(name, pitch);
}

void 	FrameworkRendering::setSoundVolume(const std::string & name, const float volume)
{
this->_sfxHandler->setSoundVolume(name, volume);
}

void 	FrameworkRendering::setSoundAttenuation(const std::string & name, const float attenuation)
{
this->_sfxHandler->setSoundAttenuation(name, attenuation);
}

const bool					FrameworkRendering::soundExist(const std::string & name) const
{
return (this->_sfxHandler->soundExist(name));
}

const bool 					FrameworkRendering::getSoundLoop(const std::string & name) const
{
return (this->_sfxHandler->getSoundLoop(name));
}

const nx::sfx::SFX_STATUS 	FrameworkRendering::getSoundStatus(const std::string & name) const
{
return (this->_sfxHandler->getSoundStatus(name));
}

const float 				FrameworkRendering::getSoundVolume(const std::string & name) const
{
return (this->_sfxHandler->getSoundVolume(name));
}

const float					FrameworkRendering::getSoundPitch(const std::string & name) const
{
return (this->_sfxHandler->getSoundPitch(name));
}

const float 				FrameworkRendering::getSoundAttenuation(const std::string & name) const
{
return (this->_sfxHandler->getSoundAttenuation(name));
}

//Music

bool	FrameworkRendering::addMusic(const std::string & name)
{
	return (this->_sfxHandler->addMusic(name));
}

void	FrameworkRendering::removeMusic(const std::string & name)
{
this->_sfxHandler->removeMusic(name);
}

void	FrameworkRendering::playMusic(const std::string & name)
{
this->_sfxHandler->playMusic(name);
}

void	FrameworkRendering::pauseMusic(const std::string & name)
{
this->_sfxHandler->pauseMusic(name);
}

void	FrameworkRendering::stopMusic(const std::string & name)
{
this->_sfxHandler->stopMusic(name);
}

void 	FrameworkRendering::setMusicLoop(const std::string & name, const bool loop)
{
this->_sfxHandler->setMusicLoop(name, loop);
}

void 	FrameworkRendering::setMusicPitch(const std::string & name, const float pitch)
{
this->_sfxHandler->setMusicPitch(name, pitch);
}

void 	FrameworkRendering::setMusicVolume(const std::string & name, const float volume)
{
this->_sfxHandler->setMusicVolume(name, volume);
}

void 	FrameworkRendering::setMusicAttenuation(const std::string & name, const float attenuation)
{
this->_sfxHandler->setMusicAttenuation(name, attenuation);
}

const bool					FrameworkRendering::musicExist(const std::string & name) const
{
return (this->_sfxHandler->musicExist(name));
}

const bool 					FrameworkRendering::getMusicLoop(const std::string & name) const
{
return (this->_sfxHandler->getMusicLoop(name));
}

const nx::sfx::SFX_STATUS 	FrameworkRendering::getMusicStatus(const std::string & name) const
{
return (this->_sfxHandler->getMusicStatus(name));
}

const float 				FrameworkRendering::getMusicVolume(const std::string & name) const
{
return (this->_sfxHandler->getMusicVolume(name));
}

const float					FrameworkRendering::getMusicPitch(const std::string & name) const
{
return (this->_sfxHandler->getMusicPitch(name));
}

const float 				FrameworkRendering::getMusicAttenuation(const std::string & name) const
{
return (this->_sfxHandler->getMusicAttenuation(name));
}

const unsigned int 			FrameworkRendering::getMusicChannelCount(const std::string & name) const
{
return (this->_sfxHandler->getMusicChannelCount(name));
}

const unsigned int 			FrameworkRendering::getMusicSampleRate(const std::string & name) const
{
return (this->_sfxHandler->getMusicSampleRate(name));
}
