#include "FrameworkScript.hpp"

nx::Engine* enginePtr = nullptr;

FrameworkScript::FrameworkScript(nx::Engine* engine)
:
	nx::ScriptFrameworkTpl("FrameworkScript"),
	_engine(engine)
{
	_state = luaL_newstate();
	luaL_openlibs(_state);
    registerEnv();
    enginePtr = engine;
}

FrameworkScript::~FrameworkScript() {}

lua_State* FrameworkScript::createThread()
{
    lua_State *thread = lua_newthread(_state);

	lua_newtable(thread);
    lua_newtable(thread);
    lua_pushliteral(thread, "__index");
    lua_pushvalue(thread, LUA_GLOBALSINDEX);
    lua_settable(thread, -3);
    lua_setmetatable(thread, -2);
    lua_replace(thread, LUA_GLOBALSINDEX);
     
    return thread;
};

void FrameworkScript::registerEnv() {
    luabridge::getGlobalNamespace(_state)
            .beginClass<nx::env::Keyboard>("Keyboard")
            .addConstructor<void(*)(void)>()
            .addFunction("compare", &nx::env::Keyboard::compare)
            .addFunction("getKeyState", &nx::env::Keyboard::getKeyState)
            .addFunction("print", &nx::env::Keyboard::print)
            .endClass()
            .beginClass<nx::Conn>("Conn")
            .addConstructor<void(*)(void)>()
            .addStaticFunction("localConnect", &nx::Conn::localConnect)
            .addStaticFunction("localDisconnect", &nx::Conn::localDisconnect)
            .endClass()
            .beginClass<nx::maths::Vector2f>("Vector2f")
            .addConstructor<void(*)(void)>()
            .addConstructor<void(*)(float, float)>()
            .addConstructor<void(*)(float)>()
            .addConstructor<void(*)(const nx::maths::Vector2f &)>()
            .addData("x", &nx::maths::Vector2f::x)
            .addData("y", &nx::maths::Vector2f::y)
            .endClass()
            .beginClass<nx::physics::Force2d>("Force2d")
			.addConstructor<void(*)(void)>()
			.addConstructor<void(*)(const double, const double)>()
			.addConstructor<void(*)(const nx::maths::Vector2f &)>()
			.addConstructor<void(*)(const nx::maths::Vector2f &, const nx::maths::Vector2f &)>()
			.addFunction("vx", &nx::physics::Force2d::vx)
			.addFunction("vy", &nx::physics::Force2d::vy)
			.addFunction("velocity", &nx::physics::Force2d::velocity)
	        .addFunction("inertia", &nx::physics::Force2d::inertia)
			.addFunction("setVX", &nx::physics::Force2d::setVX)
			.addFunction("setVY", &nx::physics::Force2d::setVY)
			.addFunction("setVelocity", &nx::physics::Force2d::setVelocity)
	        .addFunction("setInertia", &nx::physics::Force2d::setInertia)
            .endClass()
            .beginClass<nx::env::EntityInfos>("EntityInfos")
            .addConstructor<void(*)(void)>()
            .addConstructor<void(*)(std::string const&)>()
            .addConstructor<void(*)(std::string const &, bool const)>()
            .addConstructor<void(*)(const nx::env::EntityInfos &)>()
            .addFunction("setName", &nx::env::EntityInfos::setName)
            .addFunction("setActive", &nx::env::EntityInfos::setActive)
            .addFunction("getName", &nx::env::EntityInfos::getName)
            .addFunction("getActive", &nx::env::EntityInfos::getActive)
            .endClass()
			.beginClass<nx::env::TransformComponent>("TransformComponent")
			.addConstructor<void(*)(std::string const&)>()
			.addConstructor<void(*)(const nx::env::TransformComponent&)>()
			.addConstructor<void(*)(std::string const&, nx::maths::Vector2f const&)>()
			.addConstructor<void(*)(std::string const&, nx::maths::Vector2f const&, uint8_t const)>()
			.addConstructor<void(*)(std::string const&, nx::maths::Vector2f const&, uint8_t const, nx::maths::Vector2f const&)>()
			.addConstructor<void(*)(std::string const&, nx::maths::Vector2f const&, uint8_t const, nx::maths::Vector2f const&, nx::physics::Force2d const&)>()
			.addFunction("setPos", &nx::env::TransformComponent::setPos)
			.addFunction("setRotation", &nx::env::TransformComponent::setRotation)
			.addFunction("setSize", &nx::env::TransformComponent::setSize)
			.addFunction("setDirection", &nx::env::TransformComponent::setDirection)
			.addFunction("getEntityInfos", &nx::env::TransformComponent::getEntityInfos)
	        .addFunction("getPos", &nx::env::TransformComponent::getPos)
			.addFunction("getRotation", &nx::env::TransformComponent::getRotation)
			.addFunction("getSize", &nx::env::TransformComponent::getSize)
			.addFunction("getDirection", &nx::env::TransformComponent::getDirection)
			.endClass()
            .beginClass<nx::env::RigidBodyComponent>("RigidBodyComponent")
            .addConstructor<void(*)(std::string const&)>()
            .addConstructor<void(*)(std::string const&, double const)>()
            .addConstructor<void(*)(std::string const&, double const, double const)>()
            .addConstructor<void(*)(std::string const&, double const, double const, nx::maths::Vector2f const &)>()
            .addFunction("setMass", &nx::env::RigidBodyComponent::setMass)
            .addFunction("setBounciness", &nx::env::RigidBodyComponent::setBounciness)
            .addFunction("setSize", &nx::env::RigidBodyComponent::setSize)
            .addFunction("getMass", &nx::env::RigidBodyComponent::getMass)
            .addFunction("getEntityInfos", &nx::env::RigidBodyComponent::getEntityInfos)
            .addFunction("getBounciness", &nx::env::RigidBodyComponent::getBounciness)
            .addFunction("getSize", &nx::env::RigidBodyComponent::getSize)
            .endClass()
            .beginClass<nx::env::RendererComponent>("RendererComponent")
            .addConstructor<void(*)(std::string const&)>()
            .addFunction("setOpacity", &nx::env::RendererComponent::setOpacity)
            .addFunction("setTexturePath", &nx::env::RendererComponent::setTexturePath)
            .addFunction("setShapeType", &nx::env::RendererComponent::setShapeType)
            .addFunction("getOpacity", &nx::env::RendererComponent::getOpacity)
            .addFunction("getTexturePath", &nx::env::RendererComponent::getTexturePath)
            .addFunction("getShapeType", &nx::env::RendererComponent::getShapeType)
            .addFunction("getEntityInfos", &nx::env::RendererComponent::getEntityInfos)
            .endClass()
            .beginClass<nx::env::ScriptComponent>("ScriptComponent")
            .addConstructor<void(*)(std::string const&)>()
            .addConstructor<void(*)(std::string const &, std::string const&)>()
            .addFunction("setScriptPath", &nx::env::ScriptComponent::setScriptPath)
            .addFunction("getScriptPath", &nx::env::ScriptComponent::getScriptPath)
            .endClass()
            .beginClass<std::vector<nx::env::ScriptComponent> > ("ScriptComponentVector")
            .addFunction("size", &std::vector<nx::env::ScriptComponent>::size)
            .addFunction<std::vector<nx::env::ScriptComponent>::reference (std::vector<nx::env::ScriptComponent>::*)(std::vector<nx::env::ScriptComponent>::size_type)>("at", &std::vector<nx::env::ScriptComponent>::at)
            .endClass()
            .beginClass<nx::env::GameObject>("GameObject")
            .addConstructor<void(*)(std::string const&)>()
            .addConstructor<void(*)(std::string const&, bool const)>()
            .addFunction("setScriptComponent", &nx::env::GameObject::setScriptComponent)
            .addFunction("setTransformComponent", &nx::env::GameObject::setTransformComponent)
            .addFunction("setRenderComponent", &nx::env::GameObject::setRendererComponent)
            .addFunction("setRigidBodyComponent", &nx::env::GameObject::setRigidBodyComponent)
            .addFunction("getEntityInfos", &nx::env::GameObject::getEntityInfos)
            .addFunction("getScriptComponent", &nx::env::GameObject::getScriptComponent)
            .addFunction("getTransformComponent", &nx::env::GameObject::getTransformComponent)
            .addFunction("getRenderComponent", &nx::env::GameObject::getRendererComponent)
            .addFunction("getRigidBodyComponent", &nx::env::GameObject::getRigidBodyComponent)
            .endClass()
            .beginClass<std::vector<nx::env::GameObject> > ("GameObjectVector")
            .addFunction("size", &std::vector<nx::env::GameObject>::size)
            .addFunction<std::vector<nx::env::GameObject>::reference (std::vector<nx::env::GameObject>::*)(std::vector<nx::env::GameObject>::size_type)>("at", &std::vector<nx::env::GameObject>::at)
            .endClass()
            .beginClass<nx::env::RGBa>("RGBa")
            .addConstructor<void(*)(void)>()
            .addConstructor<void(*)(const uint32_t, const uint32_t, const uint32_t, const uint32_t)>()
            //.addConstructor<void(*)(const nx::env::RGBa &)>()
            .addFunction("setRed", &nx::env::RGBa::setRed)
            .addFunction("getRed", &nx::env::RGBa::getRed)
            .addFunction("setGreen", &nx::env::RGBa::setGreen)
            .addFunction("setGreen", &nx::env::RGBa::getGreen)
            .addFunction("setBlue", &nx::env::RGBa::setBlue)
            .addFunction("setBlue", &nx::env::RGBa::getBlue)
            .addFunction("setAlpha", &nx::env::RGBa::setAlpha)
            .addFunction("setAlpha", &nx::env::RGBa::getAlpha)
            .endClass()
            .beginClass<nx::env::GameInfos>("GameInfos")
            .addConstructor<void(*)(void)>()
            .endClass()
            .beginClass<std::vector<std::string> > ("StringVector")
            .addFunction("size", &std::vector<std::string>::size)
            .addFunction<std::vector<std::string>::reference (std::vector<std::string>::*)(std::vector<std::string>::size_type)>("at", &std::vector<std::string>::at)
            .endClass()
            .beginClass<nx::env::Ressources>("Ressources")
            .addConstructor<void(*)(void)>()
            .addFunction("addSoundPath", &nx::env::Ressources::addSoundPath)
            .addFunction("addMusicPath", &nx::env::Ressources::addMusicPath)
            .addFunction("addImagePath", &nx::env::Ressources::addImagePath)
            .addFunction("addScriptPath", &nx::env::Ressources::addScriptPath)
            .addFunction("getSoundPathAt", &nx::env::Ressources::getSoundPathAt)
            .addFunction("getMusicPathAt", &nx::env::Ressources::getMusicPathAt)
            .addFunction("getImagePathAt", &nx::env::Ressources::getImagePathAt)
            .addFunction("getScriptPathAt", &nx::env::Ressources::getScriptPathAt)
            .endClass()

            .beginClass<nx::env::ColorInfo>("ColorInfo")
            .addConstructor<void(*)(const nx::env::RGBa&, const nx::env::RGBa&, const unsigned int)>()
            .addConstructor<void(*)(const nx::env::ColorInfo&)>()
            .addFunction("setBackgroundColor", &nx::env::ColorInfo::setBackgroundColor)
            .addFunction("setBorderColor", &nx::env::ColorInfo::setBorderColor)
            .addFunction("setBorderThickness", &nx::env::ColorInfo::setBorderThickness)
            .addFunction("getBackgroundColor", &nx::env::ColorInfo::getBackgroundColor)
            .addFunction("getBorderColor", &nx::env::ColorInfo::getBorderColor)
            .addFunction("getBorderThickness", &nx::env::ColorInfo::getBorderThickness)
            .endClass()

            .beginClass<nx::env::TextInfo>("TextInfo")
            .addConstructor<void(*)(const nx::env::TextInfo&)>()
            .addConstructor<void(*)(const std::string&, const std::string&, const unsigned int, const nx::env::RGBa&, const uint32_t)>()
            .addFunction("setFontPath", &nx::env::TextInfo::setFontPath)
            .addFunction("setFontSize", &nx::env::TextInfo::setFontSize)
            .addFunction("setTextLabel", &nx::env::TextInfo::setTextLabel)
            .addFunction("setTextColor", &nx::env::TextInfo::setTextColor)
            .addFunction("setFontSize", &nx::env::TextInfo::setFontSize)
            .addFunction("getFontPath", &nx::env::TextInfo::getFontPath)
            .addFunction("getFontSize", &nx::env::TextInfo::getFontSize)
            .addFunction("getTextLabel", &nx::env::TextInfo::getTextLabel)
            .addFunction("getTextColor", &nx::env::TextInfo::getTextColor)
            .addFunction("getFontSize", &nx::env::TextInfo::getFontSize)
            .endClass()

            .beginClass<nx::env::GUIElementInfos>("GUIElementInfos")
            .addConstructor<void(*)()>()
            .addFunction("getActive", &nx::env::GUIElementInfos::getActive)
            .addFunction("getPos", &nx::env::GUIElementInfos::getPos)
            .addFunction("getIdentifier", &nx::env::GUIElementInfos::getIdentifier)
            .addFunction("getIsModified", &nx::env::GUIElementInfos::getIsModified)
            .addFunction("getSize", &nx::env::GUIElementInfos::getSize)
            .addFunction("setActive", &nx::env::GUIElementInfos::setActive)
            .addFunction("setPos", &nx::env::GUIElementInfos::setPos)
            .addFunction("setIdentifier", &nx::env::GUIElementInfos::setIdentifier)
            .addFunction("setIsModified", &nx::env::GUIElementInfos::setIsModified)
            .addFunction("setSize", &nx::env::GUIElementInfos::setSize)
            .endClass()

            .beginClass<nx::env::GUIButtonInfos>("GUIButtonInfos")
            .addConstructor<void(*)(const nx::env::GUIButtonInfos)>()
            .addConstructor<void(*)(bool const, nx::env::ColorInfo const&, nx::env::TextInfo const&)>()
            .addFunction("setIsPushButton", &nx::env::GUIButtonInfos::setIsPushButton)
            .addFunction("setColorInfo", &nx::env::GUIButtonInfos::setColorInfo)
            .addFunction("setTextInfo", &nx::env::GUIButtonInfos::setTextInfo)
            .addFunction("getIsPushButton", &nx::env::GUIButtonInfos::getIsPushButton)
            .addFunction("getColorInfo", &nx::env::GUIButtonInfos::getColorInfo)
            .addFunction("getTextInfo", &nx::env::GUIButtonInfos::getTextInfo)
            .addFunction("setIsModified", &nx::env::GUIButtonInfos::setIsModified)
            .addFunction("getIsModified", &nx::env::GUIButtonInfos::getIsModified)
            .endClass()

            .beginClass<nx::env::GUICheckboxInfos>("GUICheckboxInfos")
            .addConstructor<void(*)(nx::env::ColorInfo const&)>()
            .addFunction("setIsModified", &nx::env::GUICheckboxInfos::setIsModified)
            .addFunction("getIsModified", &nx::env::GUICheckboxInfos::getIsModified)
            .addFunction("getColorInfo", &nx::env::GUICheckboxInfos::getColorInfo)
            .addFunction("setColorInfo", &nx::env::GUICheckboxInfos::setColorInfo)
            .endClass()

            .beginClass<nx::env::GUIProgressBarInfos>("GUIProgressBarInfos")
            .addConstructor<void(*)(nx::env::ColorInfo const&, nx::env::TextInfo const&)>()
            .addFunction("setIsModified", &nx::env::GUIProgressBarInfos::setIsModified)
            .addFunction("getIsModified", &nx::env::GUIProgressBarInfos::getIsModified)
            .addFunction("getColorInfo", &nx::env::GUIProgressBarInfos::getColorInfo)
            .addFunction("setColorInfo", &nx::env::GUIProgressBarInfos::setColorInfo)
            .addFunction("getTextInfo", &nx::env::GUIProgressBarInfos::getTextInfo)
            .addFunction("setTextInfo", &nx::env::GUIProgressBarInfos::setTextInfo)
            .endClass()

            .beginClass<nx::env::GUIComboBoxInfos>("GUIComboBoxInfos")
            .addConstructor<void(*)(nx::env::ColorInfo const&, nx::env::TextInfo const&)>()
            .addFunction("setIsModified", &nx::env::GUIComboBoxInfos::setIsModified)
            .addFunction("getIsModified", &nx::env::GUIComboBoxInfos::getIsModified)
            .addFunction("getColorInfo", &nx::env::GUIComboBoxInfos::getColorInfo)
            .addFunction("setColorInfo", &nx::env::GUIComboBoxInfos::setColorInfo)
            .addFunction("getTextInfo", &nx::env::GUIComboBoxInfos::getTextInfo)
            .addFunction("setTextInfo", &nx::env::GUIComboBoxInfos::setTextInfo)
            .endClass()

            .beginClass<nx::env::GUITextInputInfos>("GUITextInputInfos")
            .addConstructor<void(*)(nx::env::ColorInfo const&, nx::env::TextInfo const&)>()
            .addFunction("setIsModified", &nx::env::GUITextInputInfos::setIsModified)
            .addFunction("getIsModified", &nx::env::GUITextInputInfos::getIsModified)
            .addFunction("getColorInfo", &nx::env::GUITextInputInfos::getColorInfo)
            .addFunction("setColorInfo", &nx::env::GUITextInputInfos::setColorInfo)
            .addFunction("getTextInfo", &nx::env::GUITextInputInfos::getTextInfo)
            .addFunction("setTextInfo", &nx::env::GUITextInputInfos::setTextInfo)
            .endClass()

            .beginClass<nx::env::GUITextInfos>("GUITextInfos")
            .addConstructor<void(*)(nx::env::TextInfo const&)>()
            .addFunction("setIsModified", &nx::env::GUITextInfos::setIsModified)
            .addFunction("getIsModified", &nx::env::GUITextInfos::getIsModified)
            .addFunction("setTextInfo", &nx::env::GUITextInfos::setTextInfo)
            .addFunction("getTextInfo", &nx::env::GUITextInfos::getTextInfo)
            .endClass()

            .beginClass<nx::env::GUIImageInfos>("GUIImageInfos")
            .addConstructor<void(*)(std::string const&)>()
            .addFunction("setIsModified", &nx::env::GUIImageInfos::setIsModified)
            .addFunction("getIsModified", &nx::env::GUIImageInfos::getIsModified)
            .addFunction("getImagePath", &nx::env::GUIImageInfos::getImagePath)
            .addFunction("setImagePath", &nx::env::GUIImageInfos::setImagePath)
            .endClass()

            .beginClass<nx::env::GUISpriteInfos>("GUISpriteInfos")
            .addConstructor<void(*)(std::string const&, nx::maths::Vector2f const&, nx::maths::Vector2f const&)>()
            .addFunction("setIsModified", &nx::env::GUISpriteInfos::setIsModified)
            .addFunction("getIsModified", &nx::env::GUISpriteInfos::getIsModified)
            .addFunction("getSheetGrid", &nx::env::GUISpriteInfos::getSheetGrid)
            .addFunction("setSheetGrid", &nx::env::GUISpriteInfos::setSheetGrid)
            .addFunction("getSpriteSheetPath", &nx::env::GUISpriteInfos::getSpritesheetPath)
            .addFunction("setSpriteSheetPath", &nx::env::GUISpriteInfos::setSpritesheetPath)
            .addFunction("setSpriteSize", &nx::env::GUISpriteInfos::getSpriteSize)
            .addFunction("setSpriteSize", &nx::env::GUISpriteInfos::setSpriteSize)
            .endClass()

            .beginClass<nx::env::GraphicsElementInfos>("GraphicsElementInfos")
            .addConstructor<void(*)(nx::env::GraphicsElementInfos const&)>()
            .addData("pos", &nx::env::GraphicsElementInfos::pos)
            .addData("identifier", &nx::env::GraphicsElementInfos::identifier)
            .addData("size", &nx::env::GraphicsElementInfos::size)
            .endClass()

            .beginClass<nx::env::GraphicsSpriteInfos>("GraphicsSpriteInfos")
            .addConstructor<void(*)(std::string const&, nx::maths::Vector2f const&, nx::maths::Vector2f const&)>()
            .addConstructor<void(*)(nx::env::GraphicsSpriteInfos const&)>()
            .addData("spritesheetPath", &nx::env::GraphicsSpriteInfos::spritesheetPath)
            .addData("sheetGrid", &nx::env::GraphicsSpriteInfos::sheetGrid)
            .addData("spriteSize", &nx::env::GraphicsSpriteInfos::spriteSize)
            .endClass()

            .beginClass<nx::env::GraphicsCircleInfos>("GraphicsCircleInfos")
            .addConstructor<void(*)(nx::env::GraphicsCircleInfos const&)>()
            .addConstructor<void(*)(float const, nx::env::ColorInfo const&)>()
            .addFunction("setRadius", &nx::env::GraphicsCircleInfos::setRadius)
            .addFunction("getRadius", &nx::env::GraphicsCircleInfos::getRadius)
            .addFunction("setColorInfo", &nx::env::GraphicsCircleInfos::setColorInfo)
            .addFunction("getColorInfo", &nx::env::GraphicsCircleInfos::getColorInfo)
            .endClass()

            .beginClass<nx::env::GraphicsRectInfos>("GraphicsRectInfos")
            .addConstructor<void(*)(nx::env::ColorInfo const&)>()
            .addConstructor<void(*)(nx::env::GraphicsRectInfos const&)>()
            .addData("colorInfo", &nx::env::GraphicsRectInfos::colorInfo)
            .endClass()

            .beginClass<nx::env::GraphicsConvexInfos>("GraphicsConvexInfos")
            .addConstructor<void(*)(nx::env::ColorInfo const&)>()
            .addConstructor<void(*)(nx::env::GraphicsConvexInfos const&)>()
            .addData("colorInfo", &nx::env::GraphicsConvexInfos::colorInfo)
            .endClass()

            .beginClass<nx::env::gui::TextInput>("TextInput")
            .addConstructor<void(*)(nx::env::GUIElementInfos const&, nx::env::GUITextInputInfos const&)>()
            .addFunction("getGuiTextInputInfos", &nx::env::gui::TextInput::getGuiTextInputInfos)
            .addFunction("getGuiElementInfos", &nx::env::gui::TextInput::getGuiElementInfos)
            .endClass()

            .beginClass<std::vector<nx::env::gui::TextInput> > ("TextInputVector")
            .addFunction("size", &std::vector<nx::env::gui::TextInput>::size)
            .addFunction<std::vector<nx::env::gui::TextInput>::reference (std::vector<nx::env::gui::TextInput>::*)(std::vector<nx::env::gui::TextInput>::size_type)>("at", &std::vector<nx::env::gui::TextInput>::at)
            .endClass()

            .beginClass<nx::env::gui::Text>("Text")
            .addConstructor<void(*)(nx::env::GUIElementInfos const&, nx::env::GUITextInfos const&)>()
            .addFunction("getGuiTextInfos", &nx::env::gui::Text::getGuiTextInfos)
            .addFunction("getGuiElementInfos", &nx::env::gui::Text::getGuiElementInfos)
            .endClass()

            .beginClass<std::vector<nx::env::gui::Text> > ("TextVector")
            .addFunction("size", &std::vector<nx::env::gui::Text>::size)
            .addFunction<std::vector<nx::env::gui::Text>::reference (std::vector<nx::env::gui::Text>::*)(std::vector<nx::env::gui::Text>::size_type)>("at", &std::vector<nx::env::gui::Text>::at)
            .endClass()

            .beginClass<nx::env::gui::Sprite>("Sprite")
            .addConstructor<void(*)(nx::env::GUIElementInfos const&, nx::env::GUISpriteInfos const&)>()
            .endClass()

            .beginClass<std::vector<nx::env::gui::Sprite> > ("SpriteVector")
            .addFunction("size", &std::vector<nx::env::gui::Sprite>::size)
            .addFunction<std::vector<nx::env::gui::Sprite>::reference (std::vector<nx::env::gui::Sprite>::*)(std::vector<nx::env::gui::Sprite>::size_type)>("at", &std::vector<nx::env::gui::Sprite>::at)
            .endClass()

            .beginClass<nx::env::gui::ProgressBar>("ProgressBar")
            .addConstructor<void(*)(nx::env::GUIElementInfos const&, nx::env::GUIProgressBarInfos const&)>()
            .endClass()

            .beginClass<std::vector<nx::env::gui::ProgressBar> > ("ProgressBarVector")
            .addFunction("size", &std::vector<nx::env::gui::ProgressBar>::size)
            .addFunction<std::vector<nx::env::gui::ProgressBar>::reference (std::vector<nx::env::gui::ProgressBar>::*)(std::vector<nx::env::gui::ProgressBar>::size_type)>("at", &std::vector<nx::env::gui::ProgressBar>::at)
            .endClass()

            .beginClass<nx::env::gui::Image>("Image")
            .addConstructor<void(*)(nx::env::GUIElementInfos const&, nx::env::GUIImageInfos const&)>()
            .endClass()

            .beginClass<std::vector<nx::env::gui::Image> > ("ImageVector")
            .addFunction("size", &std::vector<nx::env::gui::Image>::size)
            .addFunction<std::vector<nx::env::gui::Image>::reference (std::vector<nx::env::gui::Image>::*)(std::vector<nx::env::gui::Image>::size_type)>("at", &std::vector<nx::env::gui::Image>::at)
            .endClass()

            .beginClass<nx::env::gui::ComboBox>("ComboBox")
            .addConstructor<void(*)(nx::env::GUIElementInfos const&, nx::env::GUIComboBoxInfos const&)>()
            .endClass()

            .beginClass<std::vector<nx::env::gui::ComboBox> > ("ComboBoxVector")
            .addFunction("size", &std::vector<nx::env::gui::ComboBox>::size)
            .addFunction<std::vector<nx::env::gui::ComboBox>::reference (std::vector<nx::env::gui::ComboBox>::*)(std::vector<nx::env::gui::ComboBox>::size_type)>("at", &std::vector<nx::env::gui::ComboBox>::at)
            .endClass()

            .beginClass<nx::env::gui::Checkbox>("CheckBox")
            .addConstructor<void(*)(nx::env::GUIElementInfos const&, nx::env::GUICheckboxInfos const&)>()
            .endClass()

            .beginClass<std::vector<nx::env::gui::Checkbox> > ("CheckBoxVector")
            .addFunction("size", &std::vector<nx::env::gui::Checkbox>::size)
            .addFunction<std::vector<nx::env::gui::Checkbox>::reference (std::vector<nx::env::gui::Checkbox>::*)(std::vector<nx::env::gui::Checkbox>::size_type)>("at", &std::vector<nx::env::gui::Checkbox>::at)
            .endClass()

            .beginClass<nx::env::gui::Button>("Button")
            .addConstructor<void(*)(nx::env::GUIElementInfos const&, nx::env::GUIButtonInfos const&)>()
            .endClass()

            .beginClass<std::vector<nx::env::gui::Button> > ("ButtonVector")
            .addFunction("size", &std::vector<nx::env::gui::Button>::size)
            .addFunction<std::vector<nx::env::gui::Button>::reference (std::vector<nx::env::gui::Button>::*)(std::vector<nx::env::gui::Button>::size_type)>("at", &std::vector<nx::env::gui::Button>::at)
            .endClass()

            .beginClass<nx::env::Layer>("Layer")
            .addConstructor<void(*)(std::string const&)>()
            .addConstructor<void(*)(std::string const&, bool const)>()
            .addFunction("addButton", &nx::env::Layer::addButton)
            .addFunction("addCheckbox", &nx::env::Layer::addCheckbox)
            .addFunction("addComboBox", &nx::env::Layer::addComboBox)
            .addFunction("addImage", &nx::env::Layer::addImage)
            .addFunction("addProgressBar", &nx::env::Layer::addProgressBar)
            .addFunction("addSprite", &nx::env::Layer::addSprite)
            .addFunction("addText", &nx::env::Layer::addText)
            .addFunction("addTextInput", &nx::env::Layer::addTextInput)
            .addFunction("getEntityInfos", &nx::env::Layer::getEntityInfos)
            .addFunction("getButtonAt", &nx::env::Layer::getButtonAt)
            .addFunction("getButtonsSize", &nx::env::Layer::getButtonsSize)
            .addFunction("getCheckboxAt", &nx::env::Layer::getCheckboxAt)
            .addFunction("getCheckBoxesSize", &nx::env::Layer::getCheckBoxesSize)
            .addFunction("getComboBoxAt", &nx::env::Layer::getComboBoxAt)
            .addFunction("getComboBoxesSize", &nx::env::Layer::getComboBoxesSize)
            .addFunction("getImageAt", &nx::env::Layer::getImageAt)
            .addFunction("getImagesSize", &nx::env::Layer::getImagesSize)
            .addFunction("getProgressBarAt", &nx::env::Layer::getProgressBarAt)
            .addFunction("getProgressBarsSize", &nx::env::Layer::getProgressBarsSize)
            .addFunction("getSpriteAt", &nx::env::Layer::getSpriteAt)
            .addFunction("getSpritesSize", &nx::env::Layer::getSpritesSize)
            .addFunction("getTextAt", &nx::env::Layer::getTextAt)
            .addFunction("getTextsSize", &nx::env::Layer::getTextsSize)
            .addFunction("getTextByName", &nx::env::Layer::getTextByName)
            .addFunction("getTextInputAt", &nx::env::Layer::getTextInputAt)
            .addFunction("getTextInputsSize", &nx::env::Layer::getTextInputsSize)
            .addFunction("getButtonByName", &nx::env::Layer::getButtonByName)
            .addFunction("getCheckboxByName", &nx::env::Layer::getCheckBoxByName)
            .addFunction("getComboBoxByName", &nx::env::Layer::getComboBoxByName)
            .addFunction("getImageByName", &nx::env::Layer::getImageByName)
            .addFunction("getProgressBarByName", &nx::env::Layer::getProgressBarByName)
            .addFunction("getSpriteByName", &nx::env::Layer::getSpriteByName)
            .addFunction("getTextByName", &nx::env::Layer::getTextByName)
            .addFunction("getTextInputByName", &nx::env::Layer::getTextInputByName)
            .endClass()

            .beginClass<std::vector<nx::env::Layer> > ("LayerVector")
            .addFunction("size", &std::vector<nx::env::Layer>::size)
            .addFunction<std::vector<nx::env::Layer>::reference (std::vector<nx::env::Layer>::*)(std::vector<nx::env::Layer>::size_type)>("at", &std::vector<nx::env::Layer>::at)
            .endClass()

            .beginClass<nx::env::Scene>("Scene")
            .addConstructor<void(*)(std::string const&)>()
            .addConstructor<void(*)(std::string const&, bool const)>()
            .addFunction("addScriptComponent", &nx::env::Scene::addScriptComponent)
            .addFunction("addGameObject", &nx::env::Scene::addGameObject)
            .addFunction("setBackgroundColor", &nx::env::Scene::setBackgroundColor)
            .addFunction("addLayer", &nx::env::Scene::addLayer)
            .addFunction("getEntityInfos", &nx::env::Scene::getEntityInfos)
            .addFunction("getScriptComponentAt", &nx::env::Scene::getScriptComponentAt)
            .addFunction("getScriptComponentByName", &nx::env::Scene::getScriptComponentByName)
            .addFunction("getGameObjectAt", &nx::env::Scene::getGameObjectAt)
            .addFunction("getLayerAt", &nx::env::Scene::getLayerAt)
            .addFunction("getLayerByName", &nx::env::Scene::getLayerByName)
            .addFunction("getBackgroundColor", &nx::env::Scene::getBackgroundColor)
			.addFunction("getScriptComponentsSize", &nx::env::Scene::getScriptComponentsSize)
            .addFunction("getGameObjectByName", &nx::env::Scene::getGameObjectByName)
            .addFunction("getGameObjectsSize", &nx::env::Scene::getGameObjectsSize)
            .addFunction("getLayersSize", &nx::env::Scene::getLayersSize)
            .endClass()

            .beginClass<std::vector<nx::env::Scene> > ("SceneVector")
            .addFunction("size", &std::vector<nx::env::Scene>::size)
            .addFunction<std::vector<nx::env::Scene>::reference (std::vector<nx::env::Scene>::*)(std::vector<nx::env::Scene>::size_type)>("at", &std::vector<nx::env::Scene>::at)
            .endClass()

            .beginClass<std::vector<nx::env::Keyboard> > ("KeyboardVector")
            .addFunction("size", &std::vector<nx::env::Keyboard>::size)
            .addFunction<std::vector<nx::env::Keyboard>::reference (std::vector<nx::env::Keyboard>::*)(std::vector<nx::env::Keyboard>::size_type)>("at", &std::vector<nx::env::Keyboard>::at)
            .endClass()

            //Environment
            .beginClass<nx::env::Environment>("Environment")
            .addConstructor<void(*)(void)>()
            .addFunction("addScene", &nx::env::Environment::addScene)
            .addFunction("getSceneAt", &nx::env::Environment::getSceneAt)
            .addFunction("getSceneByName", &nx::env::Environment::getSceneByName)
            .addFunction("getRessources", &nx::env::Environment::getRessources)
            .addFunction("getGameInfos", &nx::env::Environment::getGameInfos)
			.addFunction("getScenesSize", &nx::env::Environment::getScenesSize)
            .addFunction("getConnectedClient", &nx::env::Environment::getConnectedClient)
            .addFunction("getKeyboardAt", &nx::env::Environment::getKeyboardAt)
            .addFunction("getKeyboards", &nx::env::Environment::getKeyboards)
            .endClass();
    luabridge::push(_state, &_engine->getEnv());
    lua_setglobal(_state, "Env");
}

void FrameworkScript::runFile(const std::string& scriptPath)
{
	lua_State* s = this->createThread();
	luaL_dofile(s, scriptPath.c_str());
}

void FrameworkScript::loadFile(const std::string& scriptPath)
{
	if (this->_scripts.find(scriptPath) != this->_scripts.end())
	{
		nx::Log::inform("Script '" + scriptPath + "' already loaded");
		return;
	}

	lua_State* s = this->createThread();
	if (luaL_dofile(s, scriptPath.c_str())) {
		nx::Log::error(scriptPath + " doesn't exists in you env", "BAD_FILE", 549);		
		return;
	}
	this->_scripts[scriptPath] = s;
}

void FrameworkScript::execMethod(const std::string& scriptPath, const std::string& methodName)
{
	if (this->_scripts.find(scriptPath) == this->_scripts.end()) {
		throw nx::ScriptNotLoaded(scriptPath);
	}
	// if (!luaL_dofile(this->_scripts[scriptPath], scriptPath.c_str())) {
		try {
			luabridge::getGlobal(this->_scripts[scriptPath], methodName.c_str())();
		} catch (const luabridge::LuaException& e) {
			nx::Log::error(e.what(), "BAD_LUA", 550);
		}
	// } else {
		// nx::Log::error(scriptPath + " doesn't exists in you env", "BAD_FILE", 549);
	// }
}

void FrameworkScript::init(const std::string& scriptPath)
{
	this->execMethod(scriptPath, "Init");
}

void FrameworkScript::update(const std::string& scriptPath)
{
	this->execMethod(scriptPath, "Update");	
}

void FrameworkScript::execFunction(const std::string& scriptPath, const std::string& funcName)
{
	try {
		this->execMethod(scriptPath, funcName);
	} catch (const nx::ScriptNotLoaded& e) {
		nx::Log::error(e.what(), "SCRIPT_NOT_LOADED", 404);
	}
}
