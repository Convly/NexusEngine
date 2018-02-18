#ifndef FRAMEWORK_RENDERING
# define FRAMEWORK_RENDERING

# include <functional>
# include "./gui/GUIHandler.hpp"
# include "./graphics/GraphicsHandler.hpp"
# include "Nexus/engine.hpp"
# include "Nexus/log.hpp"
# include "Nexus/frameworks/RenderingFrameworkTpl.hpp"
# include "./audio/SfxHandler.hpp"
# include "Nexus/modules/environment/Keyboard.hpp"
# include "GraphicResources.hpp"
# include "Nexus/standalone/thread/ScopedLock.hpp"

class FrameworkRendering : public nx::rendering::RenderingFrameworkTpl
{
public:
	FrameworkRendering(nx::Engine*);
	~FrameworkRendering();

	void InitializeWindow(int width, int height, std::string titleWin);
	void RefreshRendering();
	void LoadScene(std::string const& sceneName);
	void RefreshScene(nx::env::Scene & scene);
	void HandleKeyboard();	

	bool addLayer(const std::string& layerId);
	bool addButton(const std::string& layerId, const nx::env::GUIElementInfos& guiParams, const nx::env::GUIButtonInfos& buttonsParams);
	bool addCheckbox(const std::string& layerId, const nx::env::GUIElementInfos& guiParams, const nx::env::GUICheckboxInfos& checkboxParams);
	bool addProgressBar(const std::string& layerId, const nx::env::GUIElementInfos& guiParams, const nx::env::GUIProgressBarInfos& progressBarParams);
	bool addComboBox(const std::string& layerId, const nx::env::GUIElementInfos& guiParams, const nx::env::GUIComboBoxInfos& comboBoxParams);
	bool addTextInput(const std::string& layerId, const nx::env::GUIElementInfos& guiParams, const nx::env::GUITextInputInfos& textInputParams);
	bool addText(const std::string& layerId, const nx::env::GUIElementInfos& guiParams, const nx::env::GUITextInfos& textParams);
	bool addImage(const std::string& layerId, const nx::env::GUIElementInfos& guiParams, const nx::env::GUIImageInfos& imageParams);
	bool addGUISprite(const std::string& layerId, const nx::env::GUIElementInfos& guiParams, const nx::env::GUISpriteInfos& spriteParams);

	bool removeLayer(std::string const& layerId);
	bool removeGUIElem(std::string const& layerId, std::string const& elemId);
		
	bool addGraphicsSprite(const nx::env::GraphicsElementInfos& graphicsParams, const nx::env::GraphicsSpriteInfos& spriteParams);
	bool addGraphicsCirleShape(const nx::env::GraphicsElementInfos& graphicsParams, const nx::env::GraphicsCircleInfos& circleShapeParams);
	bool addGraphicsRectShape(const nx::env::GraphicsElementInfos& graphicsParams, const nx::env::GraphicsRectInfos& rectShapeParams);
	bool addGraphicsConvexShape(const nx::env::GraphicsElementInfos& graphicsParams, const nx::env::GraphicsConvexInfos& convexShapeParams);

	bool removeGraphicsElem(std::string const& elemId);

	void						setVisibleToGUIElement(std::string const& layerId, std::string const& elemId, bool const isVisible);
	void						setVisibleToGraphicsElement(std::string const& elemId, bool const isVisible);

	std::string const			getTypeFromGUIElement(std::string const& layerId, std::string const& elemId) const;
	nx::maths::Vector2f const	getPosFromGUIElement(std::string const& layerId, std::string const& elemId) const;
	nx::maths::Vector2f const	getSizeFromGUIElement(std::string const& layerId, std::string const& elemId) const;
	std::string const			getTypeFromGraphicsElement(std::string const& elemId) const;
	nx::maths::Vector2f const	getPosFromGraphicsElement(std::string const& elemId) const;
	nx::maths::Vector2f const	getSizeFromGraphicsElement(std::string const& elemId) const;

	//Button
	void		setStateToButton(std::string const& layerId, std::string const& buttonId, bool const state);
	void		setTextToButton(std::string const& layerId, std::string const& buttonId, std::string const& text);
	void		setFontSizeToButton(std::string const& layerId, std::string const& buttonId, unsigned int const fontSize);
	void		setColorNotSelectedToButton(std::string const& layerId, std::string const& buttonId, nx::env::RGBa const& color);
	void		setColorSelectedToButton(std::string const& layerId, std::string const& buttonId, nx::env::RGBa const& color);
	void		setBorderColorToButton(std::string const& layerId, std::string const& buttonId, nx::env::RGBa const& color);
	void		setBorderThicknessToButton(std::string const& layerId, std::string const& buttonId, int const thickness);
	void		setPosToButton(std::string const& layerId, std::string const& buttonId, nx::maths::Vector2f const& pos);
	void		setSizeToButton(std::string const& layerId, std::string const& buttonId, nx::maths::Vector2f const& size);

	bool const						getStateFromButton(std::string const& layerId, std::string const& buttonId) const;
	std::string const				getTextFromButton(std::string const& layerId, std::string const& buttonId) const;
	unsigned int const				getFontSizeFromButton(std::string const& layerId, std::string const& buttonId) const;
	nx::env::RGBa const		getColorNotSelectedFromButton(std::string const& layerId, std::string const& buttonId) const;
	nx::env::RGBa const		getColorSelectedFromButton(std::string const& layerId, std::string const& buttonId) const;
	nx::env::RGBa const		getBorderColorFromButton(std::string const& layerId, std::string const& buttonId) const;
	int const						getBorderThicknessFromButton(std::string const& layerId, std::string const& buttonId) const;

	//Checkbox
	void		setStateToCheckbox(std::string const& layerId, std::string const& checkboxId, nx::env::CheckboxState const state);
	void		setBackgroundColorToCheckbox(std::string const& layerId, std::string const& checkboxId, nx::env::RGBa const& color);
	void		setBorderColorToCheckbox(std::string const& layerId, std::string const& checkboxId, nx::env::RGBa const& color);
	void		setBorderThicknessToCheckbox(std::string const& layerId, std::string const& checkboxId, int const thickness);
	void		setPosToCheckbox(std::string const& layerId, std::string const& checkboxId, nx::maths::Vector2f const& pos);
	void		setSizeToCheckbox(std::string const& layerId, std::string const& checkboxId, nx::maths::Vector2f const& size);

	nx::env::CheckboxState const	getStateFromCheckbox(std::string const& layerId, std::string const& checkboxId) const;
	nx::env::RGBa const			getBackgroundColorFromCheckbox(std::string const& layerId, std::string const& checkboxId) const;
	nx::env::RGBa const			getBorderColorFromCheckbox(std::string const& layerId, std::string const& checkboxId) const;
	int const							getBorderThicknessFromCheckbox(std::string const& layerId, std::string const& checkboxId) const;

	//CircleShape
	void	setBackgroundColorToCircleShape(std::string const& circleShapeId, nx::env::RGBa const& color);
	void	setBorderColorToCircleShape(std::string const& circleShapeId, nx::env::RGBa const& color);
	void	setBorderThicknessToCircleShape(std::string const& circleShapeId, int const thickness);
	void	setRotationToCircleShape(std::string const& circleShapeId, float const angle);
	void	setRadiusToCircleShape(std::string const& circleShapeId, float const radius);
	void	setPosToCircleShape(std::string const& circleShapeId, nx::maths::Vector2f const& pos);
	void	setSizeToCircleShape(std::string const& circleShapeId, nx::maths::Vector2f const& size);
	void	setPointCountToCircleShape(std::string const& circleShapeId, size_t const count);
	void	setScaleToCircleShape(std::string const& circleShapeId, nx::maths::Vector2f const& factor);
	void	setOriginToCircleShape(std::string const& circleShapeId, nx::maths::Vector2f const& origin);
	void	moveToCircleShape(std::string const& circleShapeId, nx::maths::Vector2f const& offset);
	void	rotateToCircleShape(std::string const& circleShapeId, float const angle);
	void	scaleToCircleShape(std::string const& circleShapeId, nx::maths::Vector2f const& factor);
	void	setTextureToCircleShape(std::string const& circleShapeId, std::string const& texturePath, bool const resetRect = false);
	void	setTextureRectToCircleShape(std::string const& circleShapeId, nx::maths::Rect const& rect);

	nx::env::RGBa const		getBackgroundColorFromCircleShape(std::string const& circleShapeId) const;
	nx::env::RGBa const		getBorderColorFromCircleShape(std::string const& circleShapeId) const;
	int const						getBorderThicknessFromCircleShape(std::string const& circleShapeId) const;
	float const						getRotationFromCircleShape(std::string const& circleShapeId) const;
	float const						getRadiusFromCircleShape(std::string const& circleShapeId) const;
	size_t const					getPointCountFromCircleShape(std::string const& circleShapeId) const;
	nx::maths::Vector2f const		getPointFromCircleShape(std::string const& circleShapeId, size_t const index) const;
	nx::maths::Rect const			getTextureRectFromCircleShape(std::string const& circleShapeId) const;
	nx::maths::Vector2f const		getScaleFromCircleShape(std::string const& circleShapeId) const;
	nx::maths::Vector2f const		getOriginFromCircleShape(std::string const& circleShapeId) const;

	//ComboBox
	void	setBackgroundColorToComboBox(std::string const& layerId, std::string const& comboBoxId, nx::env::RGBa const& color);
	void	setBorderColorToComboBox(std::string const& layerId, std::string const& comboBoxId, nx::env::RGBa const& color);
	void	setBorderThicknessToComboBox(std::string const& layerId, std::string const& comboBoxId, int const thickness);
	void	setFontSizeToComboBox(std::string const& layerId, std::string const& comboBoxId, unsigned int const fontSize);
	void	addSelectionToComboBox(std::string const& layerId, std::string const& comboBoxId, std::string const& selection);
	void	removeSelectionToComboBox(std::string const& layerId, std::string const& comboBoxId, std::string const& selection, uint16_t const nbTimes);
	void	removeSelectionToComboBox(std::string const& layerId, std::string const& comboBoxId, uint16_t const idx, uint16_t const nbTimes);
	void	clearSelectionsToComboBox(std::string const& layerId, std::string const& comboBoxId);
	void	setPosToComboBox(std::string const& layerId, std::string const& comboBoxId, nx::maths::Vector2f const& pos);
	void	setSizeToComboBox(std::string const& layerId, std::string const& comboBoxId, nx::maths::Vector2f const& size);

	nx::env::RGBa const	getBackgroundColorFromComboBox(std::string const& layerId, std::string const& comboBoxId) const;
	nx::env::RGBa const	getBorderColorFromComboBox(std::string const& layerId, std::string const& comboBoxId) const;
	int const					getBorderThicknessFromComboBox(std::string const& layerId, std::string const& comboBoxId) const;
	unsigned int const			getFontSizeFromComboBox(std::string const& layerId, std::string const& comboBoxId) const;
	std::string const			getSelectedFromComboBox(std::string const& layerId, std::string const& comboBoxId) const;
	uint16_t const				getIdxSelectedFromComboBox(std::string const& layerId, std::string const& comboBoxId) const;

	//ConvexShape
	void	setBackgroundColorToConvexShape(std::string const& convexShapeId, nx::env::RGBa const& color);
	void	setBorderColorToConvexShape(std::string const& convexShapeId, nx::env::RGBa const& color);
	void	setBorderThicknessToConvexShape(std::string const& convexShapeId, int const thickness);
	void	setRotationToConvexShape(std::string const& convexShapeId, float const angle);
	void	setPointCountToConvexShape(std::string const& convexShapeId, size_t const pointCount);
	void	setPointToConvexShape(std::string const& convexShapeId, size_t const index, nx::maths::Vector2f const& point);
	void	setScaleToConvexShape(std::string const& convexShapeId, nx::maths::Vector2f const& factor);
	void	setOriginToConvexShape(std::string const& convexShapeId, nx::maths::Vector2f const& origin);
	void	moveToConvexShape(std::string const& convexShapeId, nx::maths::Vector2f const& offset);
	void	rotateToConvexShape(std::string const& convexShapeId, float const angle);
	void	scaleToConvexShape(std::string const& convexShapeId, nx::maths::Vector2f const& factor);
	void	setTextureToConvexShape(std::string const& convexShapeId, std::string const& texturePath, bool const resetRect = false);
	void	setTextureRectToConvexShape(std::string const& convexShapeId, nx::maths::Rect const& rect);
	void	setPosToConvexShape(std::string const& convexShapeId, nx::maths::Vector2f const& pos);
	void	setSizeToConvexShape(std::string const& convexShapeId, nx::maths::Vector2f const& size);

	nx::env::RGBa const		getBackgroundColorFromConvexShape(std::string const& convexShapeId) const;
	nx::env::RGBa const		getBorderColorFromConvexShape(std::string const& convexShapeId) const;
	int const						getBorderThicknessFromConvexShape(std::string const& convexShapeId) const;
	float const						getRotationFromConvexShape(std::string const& convexShapeId) const;
	size_t const					getPointCountFromConvexShape(std::string const& convexShapeId) const;
	nx::maths::Vector2f const		getPointFromConvexShape(std::string const& convexShapeId, size_t const index) const;
	nx::maths::Rect const			getTextureRectFromConvexShape(std::string const& convexShapeId) const;
	nx::maths::Vector2f const		getScaleFromConvexShape(std::string const& convexShapeId) const;
	nx::maths::Vector2f const		getOriginFromConvexShape(std::string const& convexShapeId) const;

	//Image
	void	setImagePathToImage(std::string const& layerId, std::string const& imageId, std::string const& spritePath);
	void	setPosToImage(std::string const& layerId, std::string const& imageId, nx::maths::Vector2f const& pos);
	void	setSizeToImage(std::string const& layerId, std::string const& imageId, nx::maths::Vector2f const& size);

	std::string const		getImagePathFromImage(std::string const& layerId, std::string const& imageId) const;

	//ProgressBar
	void		setBackgroundColorToProgressBar(std::string const& layerId, std::string const& progressBarId, nx::env::RGBa const& color);
	void		setBorderColorToProgressBar(std::string const& layerId, std::string const& progressBarId, nx::env::RGBa const& color);
	void		setBorderThicknessToProgressBar(std::string const& layerId, std::string const& progressBarId, int const thickness);
	void		setFilledToProgressBar(std::string const& layerId, std::string const& progressBarId, int const percentage);
	void		setFontSizeToProgressBar(std::string const& layerId, std::string const& progressBarId, unsigned int const fontSize);
	void		setPosToProgressBar(std::string const& layerId, std::string const& progressBarId, nx::maths::Vector2f const& pos);
	void		setSizeToProgressBar(std::string const& layerId, std::string const& progressBarId, nx::maths::Vector2f const& size);

	nx::env::RGBa const	getBackgroundColorFromProgressBar(std::string const& layerId, std::string const& progressBarId) const;
	nx::env::RGBa const	getBorderColorFromProgressBar(std::string const& layerId, std::string const& progressBarId) const;
	int const					getBorderThicknessFromProgressBar(std::string const& layerId, std::string const& progressBarId) const;
	int const					getFilledFromProgressBar(std::string const& layerId, std::string const& progressBarId) const;
	unsigned int const			getFontSizeFromProgressBar(std::string const& layerId, std::string const& progressBarId) const;

	//RectShape
	void	setBackgroundColorToRectShape(std::string const& rectShapeId, nx::env::RGBa const& color);
	void	setBorderColorToRectShape(std::string const& rectShapeId, nx::env::RGBa const& color);
	void	setBorderThicknessToRectShape(std::string const& rectShapeId, int const thickness);
	void	setRotationToRectShape(std::string const& rectShapeId, float const angle);
	void	setScaleToRectShape(std::string const& rectShapeId, nx::maths::Vector2f const& factor);
	void	setOriginToRectShape(std::string const& rectShapeId, nx::maths::Vector2f const& origin);
	void	moveToRectShape(std::string const& rectShapeId, nx::maths::Vector2f const& offset);
	void	rotateToRectShape(std::string const& rectShapeId, float const angle);
	void	scaleToRectShape(std::string const& rectShapeId, nx::maths::Vector2f const& factor);
	void	setTextureToRectShape(std::string const& rectShapeId, std::string const& texturePath, bool const resetRect = false);
	void	setTextureRectToRectShape(std::string const& rectShapeId, nx::maths::Rect const& rect);

	void	setPosToRectShape(std::string const& rectShapeId, nx::maths::Vector2f const& pos);
	void	setSizeToRectShape(std::string const& rectShapeId, nx::maths::Vector2f const& size);
	
	nx::env::RGBa const	getBackgroundColorFromRectShape(std::string const& rectShapeId) const;
	nx::env::RGBa const	getBorderColorFromRectShape(std::string const& rectShapeId) const;
	int const					getBorderThicknessFromRectShape(std::string const& rectShapeId) const;
	float const					getRotationFromRectShape(std::string const& rectShapeId) const;
	size_t const				getPointCountFromRectShape(std::string const& rectShapeId) const;
	nx::maths::Vector2f const	getPointFromRectShape(std::string const& rectShapeId, size_t const index) const;
	nx::maths::Rect const		getTextureRectFromRectShape(std::string const& rectShapeId) const;
	nx::maths::Vector2f const	getScaleFromRectShape(std::string const& rectShapeId) const;
	nx::maths::Vector2f const	getOriginFromRectShape(std::string const& rectShapeId) const;

	//GraphicsSprite
	void	setSpritesheetPathToGraphicsSprite(std::string const& spriteId, std::string const& spritesheetPath);
	void	setSpriteIdxToGraphicsSprite(std::string const& spriteId, uint16_t const spriteIdx);
	void	setSlownessToGraphicsSprite(std::string const& spriteId, uint16_t const slowness);
	void	setAnimateToGraphicsSprite(std::string const& spriteId, bool const animate);
	void	setSpritesAnimatedToGraphicsSprite(std::string const& spriteId, std::vector<uint16_t> const& spritesAnimated);
	void	setAnimationIdxToGraphicsSprite(std::string const& spriteId, uint16_t const animationIdx);
	void	setPosToGraphicsSprite(std::string const& spriteId, nx::maths::Vector2f const& pos);
	void	setSizeToGraphicsSprite(std::string const& spriteId, nx::maths::Vector2f const& size);
	
	std::string const &				getSpritesheetPathFromGraphicsSprite(std::string const& spriteId) const;
	uint16_t const					getSpriteIdxFromGraphicsSprite(std::string const& spriteId) const;
	uint16_t const					getSlownessFromGraphicsSprite(std::string const& spriteId) const;
	bool const						getAnimateFromGraphicsSprite(std::string const& spriteId) const;
	std::vector<uint16_t> const &	getSpritesAnimatedFromGraphicsSprite(std::string const& spriteId) const;
	uint16_t const					getAnimationIdxFromGraphicsSprite(std::string const& spriteId) const;

	//GUISprite
	void	setSpritesheetPathToGUISprite(std::string const& layerId, std::string const& spriteId, std::string const& spritesheetPath);
	void	setSpriteIdxToGUISprite(std::string const& layerId, std::string const& spriteId, uint16_t const spriteIdx);
	void	setSlownessToGUISprite(std::string const& layerId, std::string const& spriteId, uint16_t const slowness);
	void	setAnimateToGUISprite(std::string const& layerId, std::string const& spriteId, bool const animate);
	void	setSpritesAnimatedToGUISprite(std::string const& layerId, std::string const& spriteId, std::vector<uint16_t> const& spritesAnimated);
	void	setAnimationIdxToGUISprite(std::string const& layerId, std::string const& spriteId, uint16_t const animationIdx);
	void	setPosToGUISprite(std::string const& layerId, std::string const& spriteId, nx::maths::Vector2f const& pos);
	void	setSizeToGUISprite(std::string const& layerId, std::string const& spriteId, nx::maths::Vector2f const& size);
	
	std::string const &				getSpritesheetPathFromGUISprite(std::string const& layerId, std::string const& spriteId) const;
	uint16_t const					getSpriteIdxFromGUISprite(std::string const& layerId, std::string const& spriteId) const;
	uint16_t const					getSlownessFromGUISprite(std::string const& layerId, std::string const& spriteId) const;
	bool const						getAnimateFromGUISprite(std::string const& layerId, std::string const& spriteId) const;
	std::vector<uint16_t> const &	getSpritesAnimatedFromGUISprite(std::string const& layerId, std::string const& spriteId) const;
	uint16_t const					getAnimationIdxFromGUISprite(std::string const& layerId, std::string const& spriteId) const;

	//Text
	void setTextToText(std::string const& layerId, std::string const& textId, std::string const& text);
	void setFontSizeToText(std::string const& layerId, std::string const& textId, unsigned int const fontSize);
	void setPosToText(std::string const& layerId, std::string const& textId, nx::maths::Vector2f const& pos);
	void setSizeToText(std::string const& layerId, std::string const& textId, nx::maths::Vector2f const& size);

	std::string const	getTextFromText(std::string const& layerId, std::string const& textId) const;
	unsigned int const	getFontSizeFromText(std::string const& layerId, std::string const& textId) const;
	
	//TextInput
	void	setStateToTextInput(std::string const& layerId, std::string const& textInputId, bool const state);
	void	setBackgroundColorToTextInput(std::string const& layerId, std::string const& textInputId, nx::env::RGBa const& color);
	void	setBorderColorToTextInput(std::string const& layerId, std::string const& textInputId, nx::env::RGBa const& color);
	void	setBorderThicknessToTextInput(std::string const& layerId, std::string const& textInputId, int const thickness);
	void	setTextToTextInput(std::string const& layerId, std::string const& textInputId, std::string const& text);
	void	setCursorIdxToTextInput(std::string const& layerId, std::string const& textInputId, unsigned int idx);
	void	setPosToTextInput(std::string const& layerId, std::string const& textInputId, nx::maths::Vector2f const& pos);
	void	setSizeToTextInput(std::string const& layerId, std::string const& textInputId, nx::maths::Vector2f const& size);

	bool const					getStateFromTextInput(std::string const& layerId, std::string const& textInputId) const;
	nx::env::RGBa const	getBackgroundColorFromTextInput(std::string const& layerId, std::string const& textInputId) const;
	nx::env::RGBa const	getBorderColorFromTextInput(std::string const& layerId, std::string const& textInputId) const;
	int const					getBorderThicknessFromTextInput(std::string const& layerId, std::string const& textInputId) const;
	std::string const &			getTextFromTextInput(std::string const& layerId, std::string const& textInputId) const;
	unsigned int const			getCursorIdxFromTextInput(std::string const& layerId, std::string const& textInputId) const;
	
	//Sound
	bool	addSound(const std::string & name);
	void	removeSound(const std::string & name);
	void	playSound(const std::string & name);
	void	pauseSound(const std::string & name);
	void	stopSound(const std::string & name);

	void 	setSoundLoop(const std::string & name, const bool loop);
	void 	setSoundPitch(const std::string & name, const float pitch);
	void 	setSoundVolume(const std::string & name, const float volume);
	void 	setSoundAttenuation(const std::string & name, const float attenuation);

	const bool					soundExist(const std::string & name) const;
	const bool 					getSoundLoop(const std::string & name) const;
	const nx::sfx::SFX_STATUS 	getSoundStatus(const std::string & name) const;
	const float 				getSoundVolume(const std::string & name) const;
	const float					getSoundPitch(const std::string & name) const;
	const float 				getSoundAttenuation(const std::string & name) const;

	//Music
	bool	addMusic(const std::string & name);
	void	removeMusic(const std::string & name);
	void	playMusic(const std::string & name);
	void	pauseMusic(const std::string & name);
	void	stopMusic(const std::string & name);

	void 	setMusicLoop(const std::string & name, const bool loop);
	void 	setMusicPitch(const std::string & name, const float pitch);
	void 	setMusicVolume(const std::string & name, const float volume);
	void 	setMusicAttenuation(const std::string & name, const float attenuation);

	const bool					musicExist(const std::string & name) const;
	const bool 					getMusicLoop(const std::string & name) const;
	const nx::sfx::SFX_STATUS 	getMusicStatus(const std::string & name) const;
	const float 				getMusicVolume(const std::string & name) const;
	const float					getMusicPitch(const std::string & name) const;
	const float 				getMusicAttenuation(const std::string & name) const;
	const unsigned int 			getMusicChannelCount(const std::string & name) const;
	const unsigned int 			getMusicSampleRate(const std::string & name) const;

protected:
	nx::Engine	*_engine;

public:
	static sf::Color RGBa_to_sfColor(const nx::env::RGBa&);

private:
	std::shared_ptr<sf::RenderWindow>		_win;
	std::shared_ptr<nx::gui::GUIHandler>	_guiHandler;
	std::shared_ptr<nx::graphics::GraphicsHandler>	_graphicsHandler;
	std::shared_ptr<nx::sfx::SfxHandler>			_sfxHandler;
	nx::env::Keyboard								_keyboard;

	nx::gui::GUIElement		*_getGUIElementFromHandler(std::string const& layerId, std::string const& elemId) const;
	nx::gui::Button			*_getGUIButtonFromHandler(std::string const& layerId, std::string const& buttonId) const;
	nx::gui::Checkbox		*_getGUICheckboxFromHandler(std::string const& layerId, std::string const& checkboxId) const;
	nx::gui::ProgressBar	*_getGUIProgressBarFromHandler(std::string const& layerId, std::string const& progressBarId) const;
	nx::gui::ComboBox		*_getGUIComboBoxFromHandler(std::string const& layerId, std::string const& comboBoxId) const;
	nx::gui::TextInput		*_getGUITextInputFromHandler(std::string const& layerId, std::string const& textInputId) const;
	nx::gui::Text			*_getGUITextFromHandler(std::string const& layerId, std::string const& textId) const;
	nx::gui::Image			*_getGUIImageFromHandler(std::string const& layerId, std::string const& imageId) const;
	nx::gui::Sprite			*_getGUISpriteFromHandler(std::string const& layerId, std::string const& spriteId) const;

	nx::graphics::GraphicsElement	*_getGraphicsElementFromHandler(std::string const& elemId) const;
	nx::graphics::Sprite			*_getGraphicsSpriteFromHandler(std::string const& spriteId) const;
	nx::graphics::CircleShape		*_getGraphicsCircleShapeFromHandler(std::string const& circleShapeId) const;
	nx::graphics::RectShape			*_getGraphicsRectShapeFromHandler(std::string const& rectShapeId) const;
	nx::graphics::ConvexShape		*_getGraphicsConvexShapeFromHandler(std::string const& convexShapeId) const;

	void 	_registerGUIButton(std::vector<nx::env::gui::Button> const& buttons, std::string const& layerName);
	void 	_registerGUICheckbox(std::vector<nx::env::gui::Checkbox> const& checkboxes, std::string const& layerName);
	void 	_registerGUIComboBox(std::vector<nx::env::gui::ComboBox> const& comboboxes, std::string const& layerName);
	void 	_registerGUIImage(std::vector<nx::env::gui::Image> const& images, std::string const& layerName);
	void 	_registerGUIProgressBar(std::vector<nx::env::gui::ProgressBar> const& progressbars, std::string const& layerName);
	void 	_registerGUISprite(std::vector<nx::env::gui::Sprite> const& sprites, std::string const& layerName);
	void 	_registerGUIText(std::vector<nx::env::gui::Text> const& texts, std::string const& layerName);
	void 	_registerGUITextInput(std::vector<nx::env::gui::TextInput> const& textinputs, std::string const& layerName);

};

#if  defined(_MSC_VER)

extern "C"
{
	__declspec(dllexport) FrameworkRendering* CObject(nx::Engine* engine)
	{
		return (new FrameworkRendering(engine));
	}

	__declspec(dllexport) void DObject(FrameworkRendering* obj)
	{
		delete obj;
	}
}

#elif defined(__GNUC__) || defined(__GNUG__)

extern "C"
{
	FrameworkRendering* CObject(nx::Engine* engine)
	{
		return (new FrameworkRendering(engine));
	}

	void DObject(FrameworkRendering* obj)
	{
		delete obj;
	}
}

#endif

#endif
