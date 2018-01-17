#ifndef RENDERING_FRAMEWORK_TEMPLATE_HPP_
# define RENDERING_FRAMEWORK_TEMPLATE_HPP_

#include <iostream>
#include "Nexus/frameworks/ScriptFrameworkTpl.hpp"
#include "Nexus/modules/maths.hpp"

namespace nx {

	namespace rendering {
		//
		// GUI
		//

		typedef std::vector<std::pair<std::string, nx::script::ScriptInfos> > MouseEventsContainer;

		enum CheckboxState : int
		{
			UNCHECKED = 0,
			PARTIAL = 1,
			CHECKED
		};

		struct RGBa {
			RGBa(const uint32_t red_, const uint32_t green_, const uint32_t blue_, const uint32_t alpha_)
			: red(red_), green(green_), blue(blue_), alpha(alpha_) {}

			RGBa(const RGBa& other)
			: red(other.red), green(other.green), blue(other.blue), alpha(other.alpha) {}

			uint32_t red;
			uint32_t green;
			uint32_t blue;
			uint32_t alpha;
		};

		struct ColorInfo {
			ColorInfo(const nx::rendering::RGBa& backgroundColor_, const nx::rendering::RGBa& borderColor_, const unsigned int borderThickness_) 
			: backgroundColor(backgroundColor_), borderColor(borderColor_), borderThickness(borderThickness_) {}
			
			ColorInfo(const nx::rendering::ColorInfo& other)
			: backgroundColor(other.backgroundColor), borderColor(other.borderColor), borderThickness(other.borderThickness) {}

			nx::rendering::RGBa	backgroundColor;
			nx::rendering::RGBa	borderColor;
			unsigned int		borderThickness;
		};

		struct TextInfo {
			TextInfo(const std::string& fontPath_, const std::string& textLabel_, const unsigned int fontSize_, const nx::rendering::RGBa& textColor_, const uint32_t textStyle_)
			: fontPath(fontPath_), textLabel(textLabel_), fontSize(fontSize_), textColor(textColor_), textStyle(textStyle_) {}

			TextInfo(const nx::rendering::TextInfo& other)
			: fontPath(other.fontPath), textLabel(other.textLabel), fontSize(other.fontSize), textColor(other.textColor), textStyle(other.textStyle) {}

			std::string			fontPath;
			std::string			textLabel;
			unsigned int		fontSize;
			nx::rendering::RGBa	textColor;
			uint32_t			textStyle;
		};

		struct GUIElementInfos {
			GUIElementInfos(const nx::Vector2f& _pos, const nx::Vector2f& _size, const std::string& _identifier, const nx::rendering::MouseEventsContainer& events_)
			: pos(_pos), size(_size), identifier(_identifier), events(events_) {}
			
			GUIElementInfos(const GUIElementInfos& other)
			: pos(other.pos), size(other.size), identifier(other.identifier), events(other.events) {}

			nx::Vector2f pos;
			nx::Vector2f size;
			std::string identifier;
			nx::rendering::MouseEventsContainer events;
		};

		struct GUIButtonInfos {
			GUIButtonInfos(bool const isPushButton_, nx::rendering::ColorInfo const& colorInfo_, nx::rendering::TextInfo const& textInfo_) : isPushButton(isPushButton_), colorInfo(colorInfo_), textInfo(textInfo_) {}
			GUIButtonInfos(const GUIButtonInfos& other) : isPushButton(other.isPushButton), colorInfo(other.colorInfo), textInfo(other.textInfo) {}

			bool isPushButton;
			nx::rendering::ColorInfo colorInfo;
			nx::rendering::TextInfo textInfo;
		};

		struct GUICheckboxInfos {
			GUICheckboxInfos(nx::rendering::ColorInfo const& colorInfo_) : colorInfo(colorInfo_) {}
			GUICheckboxInfos(GUICheckboxInfos const& other) : colorInfo(other.colorInfo) {}

			nx::rendering::ColorInfo colorInfo;
		};

		struct GUIProgressBarInfos {
			GUIProgressBarInfos(nx::rendering::ColorInfo const& colorInfo_, nx::rendering::TextInfo const& textInfo_) : colorInfo(colorInfo_), textInfo(textInfo_) {}
			GUIProgressBarInfos(const GUIProgressBarInfos& other) : colorInfo(other.colorInfo), textInfo(other.textInfo) {}

			nx::rendering::ColorInfo colorInfo;
			nx::rendering::TextInfo textInfo;
		};

		struct GUIComboBoxInfos {
			GUIComboBoxInfos(nx::rendering::ColorInfo const& colorInfo_, nx::rendering::TextInfo const& textInfo_) : colorInfo(colorInfo_), textInfo(textInfo_) {}
			GUIComboBoxInfos(const GUIComboBoxInfos& other) : colorInfo(other.colorInfo), textInfo(other.textInfo) {}

			nx::rendering::ColorInfo colorInfo;
			nx::rendering::TextInfo textInfo;
		};

		struct GUITextInputInfos {
			GUITextInputInfos(nx::rendering::ColorInfo const& colorInfo_, nx::rendering::TextInfo const& textInfo_) : colorInfo(colorInfo_), textInfo(textInfo_) {}
			GUITextInputInfos(const GUITextInputInfos& other) : colorInfo(other.colorInfo), textInfo(other.textInfo) {}

			nx::rendering::ColorInfo colorInfo;
			nx::rendering::TextInfo textInfo;
		};

		struct GUITextInfos {
			GUITextInfos(nx::rendering::TextInfo const& textInfo_) : textInfo(textInfo_) {}
			GUITextInfos(const GUITextInfos& other) : textInfo(other.textInfo) {}

			nx::rendering::TextInfo textInfo;
		};

		struct GUIImageInfos {
			GUIImageInfos(std::string const& imagePath_) : imagePath(imagePath_) {}
			GUIImageInfos(const GUIImageInfos& other) : imagePath(other.imagePath) {}

			std::string imagePath;
		};

		struct GUISpriteInfos {
			GUISpriteInfos(std::string const& spritesheetPath_, nx::Vector2f const& sheetGrid_, nx::Vector2f const& spriteSize_) : spritesheetPath(spritesheetPath_), sheetGrid(sheetGrid_), spriteSize(spriteSize_) {}
			GUISpriteInfos(const GUISpriteInfos& other) : spritesheetPath(other.spritesheetPath), sheetGrid(other.sheetGrid), spriteSize(other.spriteSize) {}

			std::string spritesheetPath;
			nx::Vector2f sheetGrid;
			nx::Vector2f spriteSize;
		};


		struct GraphicsElementInfos {
			GraphicsElementInfos(const nx::Vector2f& _pos, const nx::Vector2f& _size, const std::string& _identifier, const nx::rendering::MouseEventsContainer& events_)
				: pos(_pos), size(_size), identifier(_identifier), events(events_) {}

			GraphicsElementInfos(const GUIElementInfos& other)
				: pos(other.pos), size(other.size), identifier(other.identifier), events(other.events) {}

			nx::Vector2f pos;
			nx::Vector2f size;
			std::string identifier;
			nx::rendering::MouseEventsContainer events;
		};

		struct GraphicsSpriteInfos {
			GraphicsSpriteInfos(std::string const& spritesheetPath_, nx::Vector2f const& sheetGrid_, nx::Vector2f const& spriteSize_) : spritesheetPath(spritesheetPath_), sheetGrid(sheetGrid_), spriteSize(spriteSize_) {}
			GraphicsSpriteInfos(const GUISpriteInfos& other) : spritesheetPath(other.spritesheetPath), sheetGrid(other.sheetGrid), spriteSize(other.spriteSize) {}

			std::string spritesheetPath;
			nx::Vector2f sheetGrid;
			nx::Vector2f spriteSize;
		};

		struct GraphicsCircleInfos {
			GraphicsCircleInfos(float const radius_, nx::rendering::ColorInfo const& colorInfo_) : radius(radius_), colorInfo(colorInfo_) {}
			GraphicsCircleInfos(const GraphicsCircleInfos& other) : colorInfo(other.colorInfo) {}

			float radius;
			nx::rendering::ColorInfo colorInfo;
		};

		struct GraphicsRectInfos {
			GraphicsRectInfos(nx::rendering::ColorInfo const& colorInfo_) : colorInfo(colorInfo_) {}
			GraphicsRectInfos(const GraphicsRectInfos& other) : colorInfo(other.colorInfo) {}

			nx::rendering::ColorInfo colorInfo;
		};

		struct GraphicsConvexInfos {
			GraphicsConvexInfos(nx::rendering::ColorInfo const& colorInfo_) : colorInfo(colorInfo_) {}
			GraphicsConvexInfos(const GraphicsConvexInfos& other) : colorInfo(other.colorInfo) {}

			nx::rendering::ColorInfo colorInfo;
		};
	}

	class RenderingFrameworkTpl
	{
	protected:
		const std::string 		_name;

	public:
		// This method must be implemented this way
		RenderingFrameworkTpl(const std::string & name) : _name(name) {};
		// This method must be implemented this way
		virtual ~RenderingFrameworkTpl() {};
		// This method must be implemented this way
		const std::string& getName(void) const {return this->_name;}

		// Framework Methods (must be virtual pure)
		virtual void InitializeWindow(int width, int height, std::string titleWin) = 0;
		virtual void RefreshRendering() = 0;
		// GUI ELEMENTS
		virtual bool addLayer(const std::string&) = 0;
		virtual bool addButton(const std::string&, const nx::rendering::GUIElementInfos&, const nx::rendering::GUIButtonInfos&) = 0;
		virtual bool addCheckbox(const std::string&, const nx::rendering::GUIElementInfos&, const nx::rendering::GUICheckboxInfos&) = 0;
		virtual bool addProgressBar(const std::string&, const nx::rendering::GUIElementInfos&, const nx::rendering::GUIProgressBarInfos&) = 0;
		virtual bool addComboBox(const std::string&, const nx::rendering::GUIElementInfos&, const nx::rendering::GUIComboBoxInfos&) = 0;
		virtual bool addTextInput(const std::string&, const nx::rendering::GUIElementInfos&, const nx::rendering::GUITextInputInfos&) = 0;
		virtual bool addText(const std::string&, const nx::rendering::GUIElementInfos&, const nx::rendering::GUITextInfos&) = 0;
		virtual bool addImage(const std::string&, const nx::rendering::GUIElementInfos&, const nx::rendering::GUIImageInfos&) = 0;
		virtual bool addGUISprite(const std::string&, const nx::rendering::GUIElementInfos&, const nx::rendering::GUISpriteInfos&) = 0;

		virtual bool addGraphicsSprite(const nx::rendering::GraphicsElementInfos& graphicsParams, const nx::rendering::GraphicsSpriteInfos& spriteParams) = 0;
		virtual bool addGraphicsCirleShape(const nx::rendering::GraphicsElementInfos& graphicsParams, const nx::rendering::GraphicsCircleInfos& circleShapeParams) = 0;
		virtual bool addGraphicsRectShape(const nx::rendering::GraphicsElementInfos& graphicsParams, const nx::rendering::GraphicsRectInfos& rectShapeParams) = 0;
		virtual bool addGraphicsConvexShape(const nx::rendering::GraphicsElementInfos& graphicsParams, const nx::rendering::GraphicsConvexInfos& convexShapeParams) = 0;

		virtual std::string const	getTypeFromElement(std::string const& layerId, std::string const& elemId) const = 0;

		//Button
		virtual void setStateToButton(std::string const& layerId, std::string const& buttonId, bool const state) = 0;
		virtual void setTextToButton(std::string const& layerId, std::string const& buttonId, std::string const& text) = 0;
		virtual void setFontSizeToButton(std::string const& layerId, std::string const& buttonId, unsigned int const fontSize) = 0;
		virtual void setColorNotSelectedToButton(std::string const& layerId, std::string const& buttonId, nx::rendering::RGBa const& color) = 0;
		virtual void setColorSelectedToButton(std::string const& layerId, std::string const& buttonId, nx::rendering::RGBa const& color) = 0;
		virtual void setBorderColorToButton(std::string const& layerId, std::string const& buttonId, nx::rendering::RGBa const& color) = 0;
		virtual void setBorderThicknessToButton(std::string const& layerId, std::string const& buttonId, int const thickness) = 0;
		virtual void setPosToButton(std::string const& layerId, std::string const& buttonId, nx::Vector2f const& pos) = 0;
		virtual void setSizeToButton(std::string const& layerId, std::string const& buttonId, nx::Vector2f const& size) = 0;

		virtual bool const					getStateFromButton(std::string const& layerId, std::string const& buttonId) const = 0;
		virtual std::string const			getTextFromButton(std::string const& layerId, std::string const& buttonId) const = 0;
		virtual unsigned int const			getFontSizeFromButton(std::string const& layerId, std::string const& buttonId) const = 0;
		virtual nx::rendering::RGBa const	getColorNotSelectedFromButton(std::string const& layerId, std::string const& buttonId) const = 0;
		virtual nx::rendering::RGBa const	getColorSelectedFromButton(std::string const& layerId, std::string const& buttonId) const = 0;
		virtual nx::rendering::RGBa const	getBorderColorFromButton(std::string const& layerId, std::string const& buttonId) const = 0;
		virtual int const					getBorderThicknessFromButton(std::string const& layerId, std::string const& buttonId) const = 0;

		//Checkbox
		virtual void	setStateToCheckbox(std::string const& layerId, std::string const& checkboxId, nx::rendering::CheckboxState const state) = 0;
		virtual void	setBackgroundColorToCheckbox(std::string const& layerId, std::string const& checkboxId, nx::rendering::RGBa const& color) = 0;
		virtual void	setBorderColorToCheckbox(std::string const& layerId, std::string const& checkboxId, nx::rendering::RGBa const& color) = 0;
		virtual void	setBorderThicknessToCheckbox(std::string const& layerId, std::string const& checkboxId, int const thickness) = 0;
		virtual void	setPosToCheckbox(std::string const& layerId, std::string const& checkboxId, nx::Vector2f const& pos) = 0;
		virtual void	setSizeToCheckbox(std::string const& layerId, std::string const& checkboxId, nx::Vector2f const& size) = 0;

		virtual nx::rendering::CheckboxState const	getStateFromCheckbox(std::string const& layerId, std::string const& checkboxId) const = 0;
		virtual nx::rendering::RGBa const			getBackgroundColorFromCheckbox(std::string const& layerId, std::string const& checkboxId) const = 0;
		virtual nx::rendering::RGBa const			getBorderColorFromCheckbox(std::string const& layerId, std::string const& checkboxId) const = 0;
		virtual int const							getBorderThicknessFromCheckbox(std::string const& layerId, std::string const& checkboxId) const = 0;

		//CircleShape
		virtual void	setBackgroundColorToCircleShape(std::string const& circleShapeId, nx::rendering::RGBa const& color) = 0;
		virtual void	setBorderColorToCircleShape(std::string const& circleShapeId, nx::rendering::RGBa const& color) = 0;
		virtual void	setBorderThicknessToCircleShape(std::string const& circleShapeId, int const thickness) = 0;
		virtual void	setRotationToCircleShape(std::string const& circleShapeId, float const angle) = 0;
		virtual void	setRadiusToCircleShape(std::string const& circleShapeId, float const radius) = 0;
		virtual void	setPosToCircleShape(std::string const& circleShapeId, nx::Vector2f const& pos) = 0;
		virtual void	setSizeToCircleShape(std::string const& circleShapeId, nx::Vector2f const& size) = 0;

		virtual nx::rendering::RGBa const	getBackgroundColorFromCircleShape(std::string const& circleShapeId) const = 0;
		virtual nx::rendering::RGBa const	getBorderColorFromCircleShape(std::string const& circleShapeId) const = 0;
		virtual int const					getBorderThicknessFromCircleShape(std::string const& circleShapeId) const = 0;
		virtual float const					getRotationFromCircleShape(std::string const& circleShapeId) const = 0;
		virtual float const					getRadiusFromCircleShape(std::string const& circleShapeId) const = 0;

		//ComboBox
		virtual void	setBackgroundColorToComboBox(std::string const& layerId, std::string const& comboBoxId, nx::rendering::RGBa const& color) = 0;
		virtual void	setBorderColorToComboBox(std::string const& layerId, std::string const& comboBoxId, nx::rendering::RGBa const& color) = 0;
		virtual void	setBorderThicknessToComboBox(std::string const& layerId, std::string const& comboBoxId, int const thickness) = 0;
		virtual void	setFontSizeToComboBox(std::string const& layerId, std::string const& comboBoxId, unsigned int const fontSize) = 0;
		virtual void	addSelectionToComboBox(std::string const& layerId, std::string const& comboBoxId, std::string const& selection) = 0;
		virtual void	removeSelectionToComboBox(std::string const& layerId, std::string const& comboBoxId, std::string const& selection, uint16_t const nbTimes) = 0;
		virtual void	removeSelectionToComboBox(std::string const& layerId, std::string const& comboBoxId, uint16_t const idx, uint16_t const nbTimes) = 0;
		virtual void	clearSelectionsToComboBox(std::string const& layerId, std::string const& comboBoxId) = 0;
		virtual void	setPosToComboBox(std::string const& layerId, std::string const& comboBoxId, nx::Vector2f const& pos) = 0;
		virtual void	setSizeToComboBox(std::string const& layerId, std::string const& comboBoxId, nx::Vector2f const& size) = 0;

		virtual nx::rendering::RGBa const	getBackgroundColorFromComboBox(std::string const& layerId, std::string const& comboBoxId) const = 0;
		virtual nx::rendering::RGBa const	getBorderColorFromComboBox(std::string const& layerId, std::string const& comboBoxId) const = 0;
		virtual int const					getBorderThicknessFromComboBox(std::string const& layerId, std::string const& comboBoxId) const = 0;
		virtual unsigned int const			getFontSizeFromComboBox(std::string const& layerId, std::string const& comboBoxId) const = 0;
		virtual std::string const			getSelectedFromComboBox(std::string const& layerId, std::string const& comboBoxId) const = 0;
		virtual uint16_t const				getIdxSelectedFromComboBox(std::string const& layerId, std::string const& comboBoxId) const = 0;

		//ConvexShape
		virtual void	setBackgroundColorToConvexShape(std::string const& convexShapeId, nx::rendering::RGBa const& color) = 0;
		virtual void	setBorderColorToConvexShape(std::string const& convexShapeId, nx::rendering::RGBa const& color) = 0;
		virtual void	setBorderThicknessToConvexShape(std::string const& convexShapeId, int const thickness) = 0;
		virtual void	setRotationToConvexShape(std::string const& convexShapeId, float const angle) = 0;
		virtual void	setPointCountToConvexShape(std::string const& convexShapeId, size_t const pointCount) = 0;
		virtual void	setPointToConvexShape(std::string const& convexShapeId, size_t const index, nx::Vector2f const& point) = 0;
		virtual void	setPosToConvexShape(std::string const& convexShapeId, nx::Vector2f const& pos) = 0;
		virtual void	setSizeToConvexShape(std::string const& convexShapeId, nx::Vector2f const& size) = 0;

		virtual nx::rendering::RGBa const	getBackgroundColorFromConvexShape(std::string const& convexShapeId) const = 0;
		virtual nx::rendering::RGBa const	getBorderColorFromConvexShape(std::string const& convexShapeId) const = 0;
		virtual int const					getBorderThicknessFromConvexShape(std::string const& convexShapeId) const = 0;
		virtual float const					getRotationFromConvexShape(std::string const& convexShapeId) const = 0;
		virtual size_t const				getPointCountFromConvexShape(std::string const& convexShapeId) const = 0;
		virtual nx::Vector2f const			getPointFromConvexShape(std::string const& convexShapeId, size_t const index) const = 0;

		//Image
		virtual void	setImagePathToImage(std::string const& layerId, std::string const& imageId, std::string const& spritePath) = 0;
		virtual void	setPosToImage(std::string const& layerId, std::string const& imageId, nx::Vector2f const& pos) = 0;
		virtual void	setSizeToImage(std::string const& layerId, std::string const& imageId, nx::Vector2f const& size) = 0;

		virtual std::string const	getImagePathFromImage(std::string const& layerId, std::string const& imageId) const = 0;

		//ProgressBar
		virtual void		setBackgroundColorToProgressBar(std::string const& layerId, std::string const& progressBarId, nx::rendering::RGBa const& color) = 0;
		virtual void		setBorderColorToProgressBar(std::string const& layerId, std::string const& progressBarId, nx::rendering::RGBa const& color) = 0;
		virtual void		setBorderThicknessToProgressBar(std::string const& layerId, std::string const& progressBarId, int const thickness) = 0;
		virtual void		setFilledToProgressBar(std::string const& layerId, std::string const& progressBarId, int const percentage) = 0;
		virtual void		setFontSizeToProgressBar(std::string const& layerId, std::string const& progressBarId, unsigned int const fontSize) = 0;
		virtual void		setPosToProgressBar(std::string const& layerId, std::string const& progressBarId, nx::Vector2f const& pos) = 0;
		virtual void		setSizeToProgressBar(std::string const& layerId, std::string const& progressBarId, nx::Vector2f const& size) = 0;

		virtual nx::rendering::RGBa const	getBackgroundColorFromProgressBar(std::string const& layerId, std::string const& progressBarId) const = 0;
		virtual nx::rendering::RGBa const	getBorderColorFromProgressBar(std::string const& layerId, std::string const& progressBarId) const = 0;
		virtual int const					getBorderThicknessFromProgressBar(std::string const& layerId, std::string const& progressBarId) const = 0;
		virtual int const					getFilledFromProgressBar(std::string const& layerId, std::string const& progressBarId) const = 0;
		virtual unsigned int const			getFontSizeFromProgressBar(std::string const& layerId, std::string const& progressBarId) const = 0;

		//RectShape
		virtual void	setBackgroundColorToRectShape(std::string const& rectShapeId, nx::rendering::RGBa const& color) = 0;
		virtual void	setBorderColorToRectShape(std::string const& rectShapeId, nx::rendering::RGBa const& color) = 0;
		virtual void	setBorderThicknessToRectShape(std::string const& rectShapeId, int const thickness) = 0;
		virtual void	setRotationToRectShape(std::string const& rectShapeId, float const angle) = 0;
		virtual void	setPosToRectShape(std::string const& rectShapeId, nx::Vector2f const& pos) = 0;
		virtual void	setSizeToRectShape(std::string const& rectShapeId, nx::Vector2f const& size) = 0;

		virtual nx::rendering::RGBa const	getBackgroundColorFromRectShape(std::string const& rectShapeId) const = 0;
		virtual nx::rendering::RGBa const	getBorderColorFromRectShape(std::string const& rectShapeId) const = 0;
		virtual int const					getBorderThicknessFromRectShape(std::string const& rectShapeId) const = 0;
		virtual float const					getRotationFromRectShape(std::string const& rectShapeId) const = 0;

		//GraphicsSprite
		virtual void	setSpritesheetPathToGraphicsSprite(std::string const& spriteId, std::string const& spritesheetPath) = 0;
		virtual void	setSpriteIdxToGraphicsSprite(std::string const& spriteId, uint16_t const spriteIdx) = 0;
		virtual void	setSlownessToGraphicsSprite(std::string const& spriteId, uint16_t const slowness) = 0;
		virtual void	setAnimateToGraphicsSprite(std::string const& spriteId, bool const animate) = 0;
		virtual void	setSpritesAnimatedToGraphicsSprite(std::string const& spriteId, std::vector<uint16_t> const& spritesAnimated) = 0;
		virtual void	setAnimationIdxToGraphicsSprite(std::string const& spriteId, uint16_t const animationIdx) = 0;
		virtual void	setPosToGraphicsSprite(std::string const& spriteId, nx::Vector2f const& pos) = 0;
		virtual void	setSizeToGraphicsSprite(std::string const& spriteId, nx::Vector2f const& size) = 0;

		virtual std::string const &				getSpritesheetPathFromGraphicsSprite(std::string const& spriteId) const = 0;
		virtual uint16_t const					getSpriteIdxFromGraphicsSprite(std::string const& spriteId) const = 0;
		virtual uint16_t const					getSlownessFromGraphicsSprite(std::string const& spriteId) const = 0;
		virtual bool const						getAnimateFromGraphicsSprite(std::string const& spriteId) const = 0;
		virtual std::vector<uint16_t> const &	getSpritesAnimatedFromGraphicsSprite(std::string const& spriteId) const = 0;
		virtual uint16_t const					getAnimationIdxFromGraphicsSprite(std::string const& spriteId) const = 0;

		//GUISprite
		virtual void	setSpritesheetPathToGUISprite(std::string const& layerId, std::string const& spriteId, std::string const& spritesheetPath) = 0;
		virtual void	setSpriteIdxToGUISprite(std::string const& layerId, std::string const& spriteId, uint16_t const spriteIdx) = 0;
		virtual void	setSlownessToGUISprite(std::string const& layerId, std::string const& spriteId, uint16_t const slowness) = 0;
		virtual void	setAnimateToGUISprite(std::string const& layerId, std::string const& spriteId, bool const animate) = 0;
		virtual void	setSpritesAnimatedToGUISprite(std::string const& layerId, std::string const& spriteId, std::vector<uint16_t> const& spritesAnimated) = 0;
		virtual void	setAnimationIdxToGUISprite(std::string const& layerId, std::string const& spriteId, uint16_t const animationIdx) = 0;
		virtual void	setPosToGUISprite(std::string const& layerId, std::string const& spriteId, nx::Vector2f const& pos) = 0;
		virtual void	setSizeToGUISprite(std::string const& layerId, std::string const& spriteId, nx::Vector2f const& size) = 0;

		virtual std::string const &				getSpritesheetPathFromGUISprite(std::string const& layerId, std::string const& spriteId) const = 0;
		virtual uint16_t const					getSpriteIdxFromGUISprite(std::string const& layerId, std::string const& spriteId) const = 0;
		virtual uint16_t const					getSlownessFromGUISprite(std::string const& layerId, std::string const& spriteId) const = 0;
		virtual bool const						getAnimateFromGUISprite(std::string const& layerId, std::string const& spriteId) const = 0;
		virtual std::vector<uint16_t> const &	getSpritesAnimatedFromGUISprite(std::string const& layerId, std::string const& spriteId) const = 0;
		virtual uint16_t const					getAnimationIdxFromGUISprite(std::string const& layerId, std::string const& spriteId) const = 0;

		//Text
		virtual void setTextToText(std::string const& layerId, std::string const& textId, std::string const& text) = 0;
		virtual void setFontSizeToText(std::string const& layerId, std::string const& textId, unsigned int const fontSize) = 0;
		virtual void setPosToText(std::string const& layerId, std::string const& textId, nx::Vector2f const& pos) = 0;
		virtual void setSizeToText(std::string const& layerId, std::string const& textId, nx::Vector2f const& size) = 0;

		virtual std::string const	getTextFromText(std::string const& layerId, std::string const& textId) const = 0;
		virtual unsigned int const	getFontSizeFromText(std::string const& layerId, std::string const& textId) const = 0;

		//TextInput
		virtual void	setStateToTextInput(std::string const& layerId, std::string const& textInputId, bool const state) = 0;
		virtual void	setBackgroundColorToTextInput(std::string const& layerId, std::string const& textInputId, nx::rendering::RGBa const& color) = 0;
		virtual void	setBorderColorToTextInput(std::string const& layerId, std::string const& textInputId, nx::rendering::RGBa const& color) = 0;
		virtual void	setBorderThicknessToTextInput(std::string const& layerId, std::string const& textInputId, int const thickness) = 0;
		virtual void	setTextToTextInput(std::string const& layerId, std::string const& textInputId, std::string const& text) = 0;
		virtual void	setCursorIdxToTextInput(std::string const& layerId, std::string const& textInputId, unsigned int idx) = 0;
		virtual void	setPosToTextInput(std::string const& layerId, std::string const& textInputId, nx::Vector2f const& pos) = 0;
		virtual void	setSizeToTextInput(std::string const& layerId, std::string const& textInputId, nx::Vector2f const& size) = 0;

		virtual bool const					getStateFromTextInput(std::string const& layerId, std::string const& textInputId) const = 0;
		virtual nx::rendering::RGBa const	getBackgroundColorFromTextInput(std::string const& layerId, std::string const& textInputId) const = 0;
		virtual nx::rendering::RGBa const	getBorderColorFromTextInput(std::string const& layerId, std::string const& textInputId) const = 0;
		virtual int const					getBorderThicknessFromTextInput(std::string const& layerId, std::string const& textInputId) const = 0;
		virtual std::string const &			getTextFromTextInput(std::string const& layerId, std::string const& textInputId) const = 0;
		virtual unsigned int const			getCursorIdxFromTextInput(std::string const& layerId, std::string const& textInputId) const = 0;
	};	
}

#endif /* RENDERING_FRAMEWORK_TEMPLATE_HPP_*/