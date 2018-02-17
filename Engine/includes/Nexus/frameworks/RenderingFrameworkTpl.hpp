#ifndef RENDERING_FRAMEWORK_TEMPLATE_HPP_
# define RENDERING_FRAMEWORK_TEMPLATE_HPP_

#include <iostream>
#include "Nexus/frameworks/ScriptFrameworkTpl.hpp"
#include "Nexus/modules/maths/maths.hpp"

namespace nx {

	namespace sfx
	{
		enum SFX_STATUS
		{
			UNKNOWN = -1,
			PLAY,
			PAUSE,
			STOP
		};
	}

    namespace rendering {

        class RenderingFrameworkTpl {
        protected:
            const std::string _name;

        public:
            // This method must be implemented this way
            RenderingFrameworkTpl(const std::string &name) : _name(name) {};

            // This method must be implemented this way
            virtual ~RenderingFrameworkTpl() {};

            // This method must be implemented this way
            const std::string &getName(void) const { return this->_name; }

            // Framework Methods (must be virtual pure)
            virtual void
            InitializeWindow(int width, int height, std::string titleWin) = 0;

            virtual void RefreshRendering() = 0;

	    virtual void LoadScene(std::string const& sceneName) = 0;

            // GUI ELEMENTS
            virtual bool addLayer(const std::string &) = 0;

            virtual bool
            addButton(const std::string &, const nx::env::GUIElementInfos &,
                      const nx::env::GUIButtonInfos &) = 0;

            virtual bool
            addCheckbox(const std::string &, const nx::env::GUIElementInfos &,
                        const nx::env::GUICheckboxInfos &) = 0;

            virtual bool addProgressBar(const std::string &,
                                        const nx::env::GUIElementInfos &,
                                        const nx::env::GUIProgressBarInfos &) = 0;

            virtual bool
            addComboBox(const std::string &, const nx::env::GUIElementInfos &,
                        const nx::env::GUIComboBoxInfos &) = 0;

            virtual bool
            addTextInput(const std::string &, const nx::env::GUIElementInfos &,
                         const nx::env::GUITextInputInfos &) = 0;

            virtual bool
            addText(const std::string &, const nx::env::GUIElementInfos &,
                    const nx::env::GUITextInfos &) = 0;

            virtual bool
            addImage(const std::string &, const nx::env::GUIElementInfos &,
                     const nx::env::GUIImageInfos &) = 0;

            virtual bool
            addGUISprite(const std::string &, const nx::env::GUIElementInfos &,
                         const nx::env::GUISpriteInfos &) = 0;

            virtual bool addGraphicsSprite(
                    const nx::env::GraphicsElementInfos &graphicsParams,
                    const nx::env::GraphicsSpriteInfos &spriteParams) = 0;

            virtual bool addGraphicsCirleShape(
                    const nx::env::GraphicsElementInfos &graphicsParams,
                    const nx::env::GraphicsCircleInfos &circleShapeParams) = 0;

            virtual bool addGraphicsRectShape(
                    const nx::env::GraphicsElementInfos &graphicsParams,
                    const nx::env::GraphicsRectInfos &rectShapeParams) = 0;

            virtual bool addGraphicsConvexShape(
                    const nx::env::GraphicsElementInfos &graphicsParams,
                    const nx::env::GraphicsConvexInfos &convexShapeParams) = 0;

            virtual void setVisibleToGUIElement(std::string const &layerId,
                                                std::string const &elemId,
                                                bool const isVisible) = 0;

            virtual void setVisibleToGraphicsElement(std::string const &elemId,
                                                     bool const isVisible) = 0;

            virtual std::string const
            getTypeFromGUIElement(std::string const &layerId,
                                  std::string const &elemId) const = 0;

            virtual nx::maths::Vector2f const
            getPosFromGUIElement(std::string const &layerId,
                                 std::string const &elemId) const = 0;

            virtual nx::maths::Vector2f const
            getSizeFromGUIElement(std::string const &layerId,
                                  std::string const &elemId) const = 0;

            virtual std::string const
            getTypeFromGraphicsElement(std::string const &elemId) const = 0;

            virtual nx::maths::Vector2f const
            getPosFromGraphicsElement(std::string const &elemId) const = 0;

            virtual nx::maths::Vector2f const
            getSizeFromGraphicsElement(std::string const &elemId) const = 0;

            //Button
            virtual void setStateToButton(std::string const &layerId,
                                          std::string const &buttonId,
                                          bool const state) = 0;

            virtual void setTextToButton(std::string const &layerId,
                                         std::string const &buttonId,
                                         std::string const &text) = 0;

            virtual void setFontSizeToButton(std::string const &layerId,
                                             std::string const &buttonId,
                                             unsigned int const fontSize) = 0;

            virtual void setColorNotSelectedToButton(std::string const &layerId,
                                                     std::string const &buttonId,
                                                     nx::env::RGBa const &color) = 0;

            virtual void setColorSelectedToButton(std::string const &layerId,
                                                  std::string const &buttonId,
                                                  nx::env::RGBa const &color) = 0;

            virtual void setBorderColorToButton(std::string const &layerId,
                                                std::string const &buttonId,
                                                nx::env::RGBa const &color) = 0;

            virtual void setBorderThicknessToButton(std::string const &layerId,
                                                    std::string const &buttonId,
                                                    int const thickness) = 0;

            virtual void setPosToButton(std::string const &layerId,
                                        std::string const &buttonId,
                                        nx::maths::Vector2f const &pos) = 0;

            virtual void setSizeToButton(std::string const &layerId,
                                         std::string const &buttonId,
                                         nx::maths::Vector2f const &size) = 0;

            virtual bool const getStateFromButton(std::string const &layerId,
                                                  std::string const &buttonId) const = 0;

            virtual std::string const
            getTextFromButton(std::string const &layerId,
                              std::string const &buttonId) const = 0;

            virtual unsigned int const
            getFontSizeFromButton(std::string const &layerId,
                                  std::string const &buttonId) const = 0;

            virtual nx::env::RGBa const
            getColorNotSelectedFromButton(std::string const &layerId,
                                          std::string const &buttonId) const = 0;

            virtual nx::env::RGBa const
            getColorSelectedFromButton(std::string const &layerId,
                                       std::string const &buttonId) const = 0;

            virtual nx::env::RGBa const
            getBorderColorFromButton(std::string const &layerId,
                                     std::string const &buttonId) const = 0;

            virtual int const
            getBorderThicknessFromButton(std::string const &layerId,
                                         std::string const &buttonId) const = 0;

            //Checkbox
            virtual void setStateToCheckbox(std::string const &layerId,
                                            std::string const &checkboxId,
                                            nx::env::CheckboxState const state) = 0;

            virtual void
            setBackgroundColorToCheckbox(std::string const &layerId,
                                         std::string const &checkboxId,
                                         nx::env::RGBa const &color) = 0;

            virtual void setBorderColorToCheckbox(std::string const &layerId,
                                                  std::string const &checkboxId,
                                                  nx::env::RGBa const &color) = 0;

            virtual void
            setBorderThicknessToCheckbox(std::string const &layerId,
                                         std::string const &checkboxId,
                                         int const thickness) = 0;

            virtual void setPosToCheckbox(std::string const &layerId,
                                          std::string const &checkboxId,
                                          nx::maths::Vector2f const &pos) = 0;

            virtual void setSizeToCheckbox(std::string const &layerId,
                                           std::string const &checkboxId,
                                           nx::maths::Vector2f const &size) = 0;

            virtual nx::env::CheckboxState const
            getStateFromCheckbox(std::string const &layerId,
                                 std::string const &checkboxId) const = 0;

            virtual nx::env::RGBa const
            getBackgroundColorFromCheckbox(std::string const &layerId,
                                           std::string const &checkboxId) const = 0;

            virtual nx::env::RGBa const
            getBorderColorFromCheckbox(std::string const &layerId,
                                       std::string const &checkboxId) const = 0;

            virtual int const
            getBorderThicknessFromCheckbox(std::string const &layerId,
                                           std::string const &checkboxId) const = 0;

            //CircleShape
            virtual void
            setBackgroundColorToCircleShape(std::string const &circleShapeId,
                                            nx::env::RGBa const &color) = 0;

            virtual void
            setBorderColorToCircleShape(std::string const &circleShapeId,
                                        nx::env::RGBa const &color) = 0;

            virtual void
            setBorderThicknessToCircleShape(std::string const &circleShapeId,
                                            int const thickness) = 0;

            virtual void
            setRotationToCircleShape(std::string const &circleShapeId,
                                     float const angle) = 0;

            virtual void
            setRadiusToCircleShape(std::string const &circleShapeId,
                                   float const radius) = 0;

            virtual void setPosToCircleShape(std::string const &circleShapeId,
                                             nx::maths::Vector2f const &pos) = 0;

            virtual void setSizeToCircleShape(std::string const &circleShapeId,
                                              nx::maths::Vector2f const &size) = 0;

            virtual void
            setPointCountToCircleShape(std::string const &circleShapeId,
                                       size_t const count) = 0;

            virtual void setScaleToCircleShape(std::string const &circleShapeId,
                                               nx::maths::Vector2f const &factor) = 0;

            virtual void
            setOriginToCircleShape(std::string const &circleShapeId,
                                   nx::maths::Vector2f const &origin) = 0;

            virtual void moveToCircleShape(std::string const &circleShapeId,
                                           nx::maths::Vector2f const &offset) = 0;

            virtual void rotateToCircleShape(std::string const &circleShapeId,
                                             float const angle) = 0;

            virtual void scaleToCircleShape(std::string const &circleShapeId,
                                            nx::maths::Vector2f const &factor) = 0;

            virtual void
            setTextureToCircleShape(std::string const &circleShapeId,
                                    std::string const &texturePath,
                                    bool const resetRect = false) = 0;

            virtual void
            setTextureRectToCircleShape(std::string const &circleShapeId,
                                        nx::maths::Rect const &rect) = 0;

            virtual nx::env::RGBa const getBackgroundColorFromCircleShape(
                    std::string const &circleShapeId) const = 0;

            virtual nx::env::RGBa const getBorderColorFromCircleShape(
                    std::string const &circleShapeId) const = 0;

            virtual int const getBorderThicknessFromCircleShape(
                    std::string const &circleShapeId) const = 0;

            virtual float const getRotationFromCircleShape(
                    std::string const &circleShapeId) const = 0;

            virtual float const getRadiusFromCircleShape(
                    std::string const &circleShapeId) const = 0;

            virtual size_t const getPointCountFromCircleShape(
                    std::string const &circleShapeId) const = 0;

            virtual nx::maths::Vector2f const
            getPointFromCircleShape(std::string const &circleShapeId,
                                    size_t const index) const = 0;

            virtual nx::maths::Rect const getTextureRectFromCircleShape(
                    std::string const &circleShapeId) const = 0;

            virtual nx::maths::Vector2f const
            getScaleFromCircleShape(std::string const &circleShapeId) const = 0;

            virtual nx::maths::Vector2f const getOriginFromCircleShape(
                    std::string const &circleShapeId) const = 0;

            //ComboBox
            virtual void
            setBackgroundColorToComboBox(std::string const &layerId,
                                         std::string const &comboBoxId,
                                         nx::env::RGBa const &color) = 0;

            virtual void setBorderColorToComboBox(std::string const &layerId,
                                                  std::string const &comboBoxId,
                                                  nx::env::RGBa const &color) = 0;

            virtual void
            setBorderThicknessToComboBox(std::string const &layerId,
                                         std::string const &comboBoxId,
                                         int const thickness) = 0;

            virtual void setFontSizeToComboBox(std::string const &layerId,
                                               std::string const &comboBoxId,
                                               unsigned int const fontSize) = 0;

            virtual void addSelectionToComboBox(std::string const &layerId,
                                                std::string const &comboBoxId,
                                                std::string const &selection) = 0;

            virtual void removeSelectionToComboBox(std::string const &layerId,
                                                   std::string const &comboBoxId,
                                                   std::string const &selection,
                                                   uint16_t const nbTimes) = 0;

            virtual void removeSelectionToComboBox(std::string const &layerId,
                                                   std::string const &comboBoxId,
                                                   uint16_t const idx,
                                                   uint16_t const nbTimes) = 0;

            virtual void clearSelectionsToComboBox(std::string const &layerId,
                                                   std::string const &comboBoxId) = 0;

            virtual void setPosToComboBox(std::string const &layerId,
                                          std::string const &comboBoxId,
                                          nx::maths::Vector2f const &pos) = 0;

            virtual void setSizeToComboBox(std::string const &layerId,
                                           std::string const &comboBoxId,
                                           nx::maths::Vector2f const &size) = 0;

            virtual nx::env::RGBa const
            getBackgroundColorFromComboBox(std::string const &layerId,
                                           std::string const &comboBoxId) const = 0;

            virtual nx::env::RGBa const
            getBorderColorFromComboBox(std::string const &layerId,
                                       std::string const &comboBoxId) const = 0;

            virtual int const
            getBorderThicknessFromComboBox(std::string const &layerId,
                                           std::string const &comboBoxId) const = 0;

            virtual unsigned int const
            getFontSizeFromComboBox(std::string const &layerId,
                                    std::string const &comboBoxId) const = 0;

            virtual std::string const
            getSelectedFromComboBox(std::string const &layerId,
                                    std::string const &comboBoxId) const = 0;

            virtual uint16_t const
            getIdxSelectedFromComboBox(std::string const &layerId,
                                       std::string const &comboBoxId) const = 0;

            //ConvexShape
            virtual void
            setBackgroundColorToConvexShape(std::string const &convexShapeId,
                                            nx::env::RGBa const &color) = 0;

            virtual void
            setBorderColorToConvexShape(std::string const &convexShapeId,
                                        nx::env::RGBa const &color) = 0;

            virtual void
            setBorderThicknessToConvexShape(std::string const &convexShapeId,
                                            int const thickness) = 0;

            virtual void
            setRotationToConvexShape(std::string const &convexShapeId,
                                     float const angle) = 0;

            virtual void
            setPointCountToConvexShape(std::string const &convexShapeId,
                                       size_t const pointCount) = 0;

            virtual void setPointToConvexShape(std::string const &convexShapeId,
                                               size_t const index,
                                               nx::maths::Vector2f const &point) = 0;

            virtual void setScaleToConvexShape(std::string const &convexShapeId,
                                               nx::maths::Vector2f const &factor) = 0;

            virtual void
            setOriginToConvexShape(std::string const &convexShapeId,
                                   nx::maths::Vector2f const &origin) = 0;

            virtual void moveToConvexShape(std::string const &convexShapeId,
                                           nx::maths::Vector2f const &offset) = 0;

            virtual void rotateToConvexShape(std::string const &convexShapeId,
                                             float const angle) = 0;

            virtual void scaleToConvexShape(std::string const &convexShapeId,
                                            nx::maths::Vector2f const &factor) = 0;

            virtual void
            setTextureToConvexShape(std::string const &convexShapeId,
                                    std::string const &texturePath,
                                    bool const resetRect = false) = 0;

            virtual void
            setTextureRectToConvexShape(std::string const &convexShapeId,
                                        nx::maths::Rect const &rect) = 0;

            virtual void setPosToConvexShape(std::string const &convexShapeId,
                                             nx::maths::Vector2f const &pos) = 0;

            virtual void setSizeToConvexShape(std::string const &convexShapeId,
                                              nx::maths::Vector2f const &size) = 0;

            virtual nx::env::RGBa const getBackgroundColorFromConvexShape(
                    std::string const &convexShapeId) const = 0;

            virtual nx::env::RGBa const getBorderColorFromConvexShape(
                    std::string const &convexShapeId) const = 0;

            virtual int const getBorderThicknessFromConvexShape(
                    std::string const &convexShapeId) const = 0;

            virtual float const getRotationFromConvexShape(
                    std::string const &convexShapeId) const = 0;

            virtual size_t const getPointCountFromConvexShape(
                    std::string const &convexShapeId) const = 0;

            virtual nx::maths::Vector2f const
            getPointFromConvexShape(std::string const &convexShapeId,
                                    size_t const index) const = 0;

            virtual nx::maths::Rect const getTextureRectFromConvexShape(
                    std::string const &convexShapeId) const = 0;

            virtual nx::maths::Vector2f const
            getScaleFromConvexShape(std::string const &convexShapeId) const = 0;

            virtual nx::maths::Vector2f const getOriginFromConvexShape(
                    std::string const &convexShapeId) const = 0;

            //Image
            virtual void setImagePathToImage(std::string const &layerId,
                                             std::string const &imageId,
                                             std::string const &spritePath) = 0;

            virtual void setPosToImage(std::string const &layerId,
                                       std::string const &imageId,
                                       nx::maths::Vector2f const &pos) = 0;

            virtual void setSizeToImage(std::string const &layerId,
                                        std::string const &imageId,
                                        nx::maths::Vector2f const &size) = 0;

            virtual std::string const
            getImagePathFromImage(std::string const &layerId,
                                  std::string const &imageId) const = 0;

            //ProgressBar
            virtual void
            setBackgroundColorToProgressBar(std::string const &layerId,
                                            std::string const &progressBarId,
                                            nx::env::RGBa const &color) = 0;

            virtual void setBorderColorToProgressBar(std::string const &layerId,
                                                     std::string const &progressBarId,
                                                     nx::env::RGBa const &color) = 0;

            virtual void
            setBorderThicknessToProgressBar(std::string const &layerId,
                                            std::string const &progressBarId,
                                            int const thickness) = 0;

            virtual void setFilledToProgressBar(std::string const &layerId,
                                                std::string const &progressBarId,
                                                int const percentage) = 0;

            virtual void setFontSizeToProgressBar(std::string const &layerId,
                                                  std::string const &progressBarId,
                                                  unsigned int const fontSize) = 0;

            virtual void setPosToProgressBar(std::string const &layerId,
                                             std::string const &progressBarId,
                                             nx::maths::Vector2f const &pos) = 0;

            virtual void setSizeToProgressBar(std::string const &layerId,
                                              std::string const &progressBarId,
                                              nx::maths::Vector2f const &size) = 0;

            virtual nx::env::RGBa const
            getBackgroundColorFromProgressBar(std::string const &layerId,
                                              std::string const &progressBarId) const = 0;

            virtual nx::env::RGBa const
            getBorderColorFromProgressBar(std::string const &layerId,
                                          std::string const &progressBarId) const = 0;

            virtual int const
            getBorderThicknessFromProgressBar(std::string const &layerId,
                                              std::string const &progressBarId) const = 0;

            virtual int const
            getFilledFromProgressBar(std::string const &layerId,
                                     std::string const &progressBarId) const = 0;

            virtual unsigned int const
            getFontSizeFromProgressBar(std::string const &layerId,
                                       std::string const &progressBarId) const = 0;

            //RectShape
            virtual void
            setBackgroundColorToRectShape(std::string const &rectShapeId,
                                          nx::env::RGBa const &color) = 0;

            virtual void
            setBorderColorToRectShape(std::string const &rectShapeId,
                                      nx::env::RGBa const &color) = 0;

            virtual void
            setBorderThicknessToRectShape(std::string const &rectShapeId,
                                          int const thickness) = 0;

            virtual void setRotationToRectShape(std::string const &rectShapeId,
                                                float const angle) = 0;

            virtual void setScaleToRectShape(std::string const &rectShapeId,
                                             nx::maths::Vector2f const &factor) = 0;

            virtual void setOriginToRectShape(std::string const &rectShapeId,
                                              nx::maths::Vector2f const &origin) = 0;

            virtual void moveToRectShape(std::string const &rectShapeId,
                                         nx::maths::Vector2f const &offset) = 0;

            virtual void rotateToRectShape(std::string const &rectShapeId,
                                           float const angle) = 0;

            virtual void scaleToRectShape(std::string const &rectShapeId,
                                          nx::maths::Vector2f const &factor) = 0;

            virtual void setTextureToRectShape(std::string const &rectShapeId,
                                               std::string const &texturePath,
                                               bool const resetRect = false) = 0;

            virtual void
            setTextureRectToRectShape(std::string const &rectShapeId,
                                      nx::maths::Rect const &rect) = 0;

            virtual void setPosToRectShape(std::string const &rectShapeId,
                                           nx::maths::Vector2f const &pos) = 0;

            virtual void setSizeToRectShape(std::string const &rectShapeId,
                                            nx::maths::Vector2f const &size) = 0;

            virtual nx::env::RGBa const getBackgroundColorFromRectShape(
                    std::string const &rectShapeId) const = 0;

            virtual nx::env::RGBa const getBorderColorFromRectShape(
                    std::string const &rectShapeId) const = 0;

            virtual int const getBorderThicknessFromRectShape(
                    std::string const &rectShapeId) const = 0;

            virtual float const
            getRotationFromRectShape(std::string const &rectShapeId) const = 0;

            virtual size_t const getPointCountFromRectShape(
                    std::string const &rectShapeId) const = 0;

            virtual nx::maths::Vector2f const
            getPointFromRectShape(std::string const &rectShapeId,
                                  size_t const index) const = 0;

            virtual nx::maths::Rect const getTextureRectFromRectShape(
                    std::string const &rectShapeId) const = 0;

            virtual nx::maths::Vector2f const
            getScaleFromRectShape(std::string const &rectShapeId) const = 0;

            virtual nx::maths::Vector2f const
            getOriginFromRectShape(std::string const &rectShapeId) const = 0;

            //GraphicsSprite
            virtual void
            setSpritesheetPathToGraphicsSprite(std::string const &spriteId,
                                               std::string const &spritesheetPath) = 0;

            virtual void
            setSpriteIdxToGraphicsSprite(std::string const &spriteId,
                                         uint16_t const spriteIdx) = 0;

            virtual void
            setSlownessToGraphicsSprite(std::string const &spriteId,
                                        uint16_t const slowness) = 0;

            virtual void setAnimateToGraphicsSprite(std::string const &spriteId,
                                                    bool const animate) = 0;

            virtual void
            setSpritesAnimatedToGraphicsSprite(std::string const &spriteId,
                                               std::vector<uint16_t> const &spritesAnimated) = 0;

            virtual void
            setAnimationIdxToGraphicsSprite(std::string const &spriteId,
                                            uint16_t const animationIdx) = 0;

            virtual void setPosToGraphicsSprite(std::string const &spriteId,
                                                nx::maths::Vector2f const &pos) = 0;

            virtual void setSizeToGraphicsSprite(std::string const &spriteId,
                                                 nx::maths::Vector2f const &size) = 0;

            virtual std::string const &getSpritesheetPathFromGraphicsSprite(
                    std::string const &spriteId) const = 0;

            virtual uint16_t const getSpriteIdxFromGraphicsSprite(
                    std::string const &spriteId) const = 0;

            virtual uint16_t const getSlownessFromGraphicsSprite(
                    std::string const &spriteId) const = 0;

            virtual bool const
            getAnimateFromGraphicsSprite(std::string const &spriteId) const = 0;

            virtual std::vector<uint16_t> const &
            getSpritesAnimatedFromGraphicsSprite(
                    std::string const &spriteId) const = 0;

            virtual uint16_t const getAnimationIdxFromGraphicsSprite(
                    std::string const &spriteId) const = 0;

            //GUISprite
            virtual void
            setSpritesheetPathToGUISprite(std::string const &layerId,
                                          std::string const &spriteId,
                                          std::string const &spritesheetPath) = 0;

            virtual void setSpriteIdxToGUISprite(std::string const &layerId,
                                                 std::string const &spriteId,
                                                 uint16_t const spriteIdx) = 0;

            virtual void setSlownessToGUISprite(std::string const &layerId,
                                                std::string const &spriteId,
                                                uint16_t const slowness) = 0;

            virtual void setAnimateToGUISprite(std::string const &layerId,
                                               std::string const &spriteId,
                                               bool const animate) = 0;

            virtual void
            setSpritesAnimatedToGUISprite(std::string const &layerId,
                                          std::string const &spriteId,
                                          std::vector<uint16_t> const &spritesAnimated) = 0;

            virtual void setAnimationIdxToGUISprite(std::string const &layerId,
                                                    std::string const &spriteId,
                                                    uint16_t const animationIdx) = 0;

            virtual void setPosToGUISprite(std::string const &layerId,
                                           std::string const &spriteId,
                                           nx::maths::Vector2f const &pos) = 0;

            virtual void setSizeToGUISprite(std::string const &layerId,
                                            std::string const &spriteId,
                                            nx::maths::Vector2f const &size) = 0;

            virtual std::string const &
            getSpritesheetPathFromGUISprite(std::string const &layerId,
                                            std::string const &spriteId) const = 0;

            virtual uint16_t const
            getSpriteIdxFromGUISprite(std::string const &layerId,
                                      std::string const &spriteId) const = 0;

            virtual uint16_t const
            getSlownessFromGUISprite(std::string const &layerId,
                                     std::string const &spriteId) const = 0;

            virtual bool const
            getAnimateFromGUISprite(std::string const &layerId,
                                    std::string const &spriteId) const = 0;

            virtual std::vector<uint16_t> const &
            getSpritesAnimatedFromGUISprite(std::string const &layerId,
                                            std::string const &spriteId) const = 0;

            virtual uint16_t const
            getAnimationIdxFromGUISprite(std::string const &layerId,
                                         std::string const &spriteId) const = 0;

            //Text
            virtual void
            setTextToText(std::string const &layerId, std::string const &textId,
                          std::string const &text) = 0;

            virtual void setFontSizeToText(std::string const &layerId,
                                           std::string const &textId,
                                           unsigned int const fontSize) = 0;

            virtual void
            setPosToText(std::string const &layerId, std::string const &textId,
                         nx::maths::Vector2f const &pos) = 0;

            virtual void
            setSizeToText(std::string const &layerId, std::string const &textId,
                          nx::maths::Vector2f const &size) = 0;

            virtual std::string const
            getTextFromText(std::string const &layerId,
                            std::string const &textId) const = 0;

            virtual unsigned int const
            getFontSizeFromText(std::string const &layerId,
                                std::string const &textId) const = 0;

            //TextInput
            virtual void setStateToTextInput(std::string const &layerId,
                                             std::string const &textInputId,
                                             bool const state) = 0;

            virtual void
            setBackgroundColorToTextInput(std::string const &layerId,
                                           std::string const &textInputId,
                                           nx::env::RGBa const &color) = 0;

            virtual void setBorderColorToTextInput(std::string const &layerId,
                                                   std::string const &textInputId,
                                                   nx::env::RGBa const &color) = 0;

            virtual void
            setBorderThicknessToTextInput(std::string const &layerId,
                                          std::string const &textInputId,
                                          int const thickness) = 0;

            virtual void setTextToTextInput(std::string const &layerId,
                                            std::string const &textInputId,
                                            std::string const &text) = 0;

            virtual void setCursorIdxToTextInput(std::string const &layerId,
                                                 std::string const &textInputId,
                                                 unsigned int idx) = 0;

            virtual void setPosToTextInput(std::string const &layerId,
                                           std::string const &textInputId,
                                           nx::maths::Vector2f const &pos) = 0;

            virtual void setSizeToTextInput(std::string const &layerId,
                                            std::string const &textInputId,
                                            nx::maths::Vector2f const &size) = 0;

            virtual bool const getStateFromTextInput(std::string const &layerId,
                                                     std::string const &textInputId) const = 0;

            virtual nx::env::RGBa const
            getBackgroundColorFromTextInput(std::string const &layerId,
                                            std::string const &textInputId) const = 0;

            virtual nx::env::RGBa const
            getBorderColorFromTextInput(std::string const &layerId,
                                        std::string const &textInputId) const = 0;

            virtual int const
            getBorderThicknessFromTextInput(std::string const &layerId,
                                            std::string const &textInputId) const = 0;

            virtual std::string const &
            getTextFromTextInput(std::string const &layerId,
                                 std::string const &textInputId) const = 0;

            virtual unsigned int const
            getCursorIdxFromTextInput(std::string const &layerId,
                                      std::string const &textInputId) const = 0;

			//Sound
			virtual bool	addSound(const std::string & name) = 0;
			virtual void	removeSound(const std::string & name) = 0;
			virtual void	playSound(const std::string & name) = 0;
			virtual void	pauseSound(const std::string & name) = 0;
			virtual void	stopSound(const std::string & name) = 0;

			virtual void 	setSoundLoop(const std::string & name, const bool loop) = 0;
			virtual void 	setSoundPitch(const std::string & name, const float pitch) = 0;
			virtual void 	setSoundVolume(const std::string & name, const float volume) = 0;
			virtual void 	setSoundAttenuation(const std::string & name, const float attenuation) = 0;

			virtual const bool					soundExist(const std::string & name) const = 0;
			virtual const bool 					getSoundLoop(const std::string & name) const = 0;
			virtual const nx::sfx::SFX_STATUS 	getSoundStatus(const std::string & name) const = 0;
			virtual const float 				getSoundVolume(const std::string & name) const = 0;
			virtual const float					getSoundPitch(const std::string & name) const = 0;
			virtual const float 				getSoundAttenuation(const std::string & name) const = 0;

			//Music
			virtual bool	addMusic(const std::string & name) = 0;
			virtual void	removeMusic(const std::string & name) = 0;
			virtual void	playMusic(const std::string & name) = 0;
			virtual void	pauseMusic(const std::string & name) = 0;
			virtual void	stopMusic(const std::string & name) = 0;

			virtual void 	setMusicLoop(const std::string & name, const bool loop) = 0;
			virtual void 	setMusicPitch(const std::string & name, const float pitch) = 0;
			virtual void 	setMusicVolume(const std::string & name, const float volume) = 0;
			virtual void 	setMusicAttenuation(const std::string & name, const float attenuation) = 0;

			virtual const bool					musicExist(const std::string & name) const = 0;
			virtual const bool 					getMusicLoop(const std::string & name) const = 0;
			virtual const nx::sfx::SFX_STATUS 	getMusicStatus(const std::string & name) const = 0;
			virtual const float 				getMusicVolume(const std::string & name) const = 0;
			virtual const float					getMusicPitch(const std::string & name) const = 0;
			virtual const float 				getMusicAttenuation(const std::string & name) const = 0;
			virtual const unsigned int 			getMusicChannelCount(const std::string & name) const = 0;
			virtual const unsigned int 			getMusicSampleRate(const std::string & name) const = 0;
        };
    }
}

#endif /* RENDERING_FRAMEWORK_TEMPLATE_HPP_*/