#ifndef NEXUS_ENGINE__ENVUTILS_HPP_
#define NEXUS_ENGINE__ENVUTILS_HPP_

# include <vector>
# include "Nexus/modules/maths/maths.hpp"

namespace nx
{
	namespace script {
		struct ScriptInfos {
			ScriptInfos(const std::string& file_, const std::string& func_)
				: file(file_), func(func_) {}

			ScriptInfos(const nx::script::ScriptInfos& other)
				: file(other.file), func(other.func) {}

			std::string file;
			std::string func;
		};
	};

	namespace env
	{
		typedef std::vector<std::pair<std::string, nx::script::ScriptInfos> > MouseEventsContainer;

		enum CheckboxState : int
		{
			UNCHECKED = 0,
			PARTIAL = 1,
			CHECKED
		};

		class RGBa {
			std::atomic<uint32_t> _red;
			std::atomic<uint32_t> _green;
			std::atomic<uint32_t> _blue;
			std::atomic<uint32_t> _alpha;

		public:
			RGBa() : _red(0), _green(0), _blue(0), _alpha(255) {}
			RGBa(const uint32_t red_, const uint32_t green_, const uint32_t blue_, const uint32_t alpha_)
				: _red(red_), _green(green_), _blue(blue_), _alpha(alpha_) {}

			RGBa(const RGBa& other)
				: _red(other.getRed()), _green(other.getGreen()), _blue(other.getBlue()), _alpha(other.getAlpha()) {}

		public:
			// Setters
			void		setRed(const uint32_t red)
			{
				this->_red = red;
			}

			void		setGreen(const uint32_t green)
			{
				this->_green = green;
			}

			void		setBlue(const uint32_t blue)
			{
				this->_blue = blue;
			}

			void		setAlpha(const uint32_t alpha)
			{
				this->_alpha = alpha;
			}

		public:
			// Getters
			uint32_t	getRed() const
			{
				return (this->_red);
			}

			uint32_t	getGreen() const
			{
				return (this->_green);
			}

			uint32_t	getBlue() const
			{
				return (this->_blue);
			}

			uint32_t	getAlpha() const
			{
				return (this->_alpha);
			}

		public:
			RGBa const & operator=(const RGBa & other)
			{
				if (this != &other)
				{
					this->_red = other.getRed();
					this->_green = other.getGreen();
					this->_blue = other.getBlue();
					this->_alpha = other.getAlpha();
				}
				return (*this);
			}

		};

		struct ColorInfo {
			ColorInfo(const nx::env::RGBa& backgroundColor_, const nx::env::RGBa& borderColor_, const unsigned int borderThickness_)
				: backgroundColor(backgroundColor_), borderColor(borderColor_), borderThickness(borderThickness_) {}

			ColorInfo(const nx::env::ColorInfo& other)
				: backgroundColor(other.backgroundColor), borderColor(other.borderColor), borderThickness(other.borderThickness) {}

			nx::env::RGBa	backgroundColor;
			nx::env::RGBa	borderColor;
			unsigned int		borderThickness;
		};

		struct TextInfo {
			TextInfo(const std::string& fontPath_, const std::string& textLabel_, const unsigned int fontSize_, const nx::env::RGBa& textColor_, const uint32_t textStyle_)
				: fontPath(fontPath_), textLabel(textLabel_), fontSize(fontSize_), textColor(textColor_), textStyle(textStyle_) {}

			TextInfo(const nx::env::TextInfo& other)
				: fontPath(other.fontPath), textLabel(other.textLabel), fontSize(other.fontSize), textColor(other.textColor), textStyle(other.textStyle) {}

			std::string			fontPath;
			std::string			textLabel;
			unsigned int		fontSize;
			nx::env::RGBa		textColor;
			uint32_t			textStyle;
		};

		struct GUIElementInfos {
			GUIElementInfos(const nx::maths::Vector2f& _pos, const nx::maths::Vector2f& _size, const std::string& _identifier, const nx::env::MouseEventsContainer& events_)
				: pos(_pos), size(_size), identifier(_identifier), events(events_) {}

			GUIElementInfos(const GUIElementInfos& other)
				: pos(other.pos), size(other.size), identifier(other.identifier), events(other.events) {}

			nx::maths::Vector2f pos;
			nx::maths::Vector2f size;
			std::string identifier;
			nx::env::MouseEventsContainer events;
		};

		struct GUIButtonInfos {
			GUIButtonInfos(bool const isPushButton_, nx::env::ColorInfo const& colorInfo_, nx::env::TextInfo const& textInfo_) : isPushButton(isPushButton_), colorInfo(colorInfo_), textInfo(textInfo_) {}
			GUIButtonInfos(const GUIButtonInfos& other) : isPushButton(other.isPushButton), colorInfo(other.colorInfo), textInfo(other.textInfo) {}

			bool isPushButton;
			nx::env::ColorInfo colorInfo;
			nx::env::TextInfo textInfo;
		};

		struct GUICheckboxInfos {
			GUICheckboxInfos(nx::env::ColorInfo const& colorInfo_) : colorInfo(colorInfo_) {}
			GUICheckboxInfos(GUICheckboxInfos const& other) : colorInfo(other.colorInfo) {}

			nx::env::ColorInfo colorInfo;
		};

		struct GUIProgressBarInfos {
			GUIProgressBarInfos(nx::env::ColorInfo const& colorInfo_, nx::env::TextInfo const& textInfo_) : colorInfo(colorInfo_), textInfo(textInfo_) {}
			GUIProgressBarInfos(const GUIProgressBarInfos& other) : colorInfo(other.colorInfo), textInfo(other.textInfo) {}

			nx::env::ColorInfo colorInfo;
			nx::env::TextInfo textInfo;
		};

		struct GUIComboBoxInfos {
			GUIComboBoxInfos(nx::env::ColorInfo const& colorInfo_, nx::env::TextInfo const& textInfo_) : colorInfo(colorInfo_), textInfo(textInfo_) {}
			GUIComboBoxInfos(const GUIComboBoxInfos& other) : colorInfo(other.colorInfo), textInfo(other.textInfo) {}

			nx::env::ColorInfo colorInfo;
			nx::env::TextInfo textInfo;
		};

		struct GUITextInputInfos {
			GUITextInputInfos(nx::env::ColorInfo const& colorInfo_, nx::env::TextInfo const& textInfo_) : colorInfo(colorInfo_), textInfo(textInfo_) {}
			GUITextInputInfos(const GUITextInputInfos& other) : colorInfo(other.colorInfo), textInfo(other.textInfo) {}

			nx::env::ColorInfo colorInfo;
			nx::env::TextInfo textInfo;
		};

		struct GUITextInfos {
			GUITextInfos(nx::env::TextInfo const& textInfo_) : textInfo(textInfo_) {}
			GUITextInfos(const GUITextInfos& other) : textInfo(other.textInfo) {}

			nx::env::TextInfo textInfo;
		};

		struct GUIImageInfos {
			GUIImageInfos(std::string const& imagePath_) : imagePath(imagePath_) {}
			GUIImageInfos(const GUIImageInfos& other) : imagePath(other.imagePath) {}

			std::string imagePath;
		};

		struct GUISpriteInfos {
			GUISpriteInfos(std::string const& spritesheetPath_, nx::maths::Vector2f const& sheetGrid_, nx::maths::Vector2f const& spriteSize_) : spritesheetPath(spritesheetPath_), sheetGrid(sheetGrid_), spriteSize(spriteSize_) {}
			GUISpriteInfos(const GUISpriteInfos& other) : spritesheetPath(other.spritesheetPath), sheetGrid(other.sheetGrid), spriteSize(other.spriteSize) {}

			std::string spritesheetPath;
			nx::maths::Vector2f sheetGrid;
			nx::maths::Vector2f spriteSize;
		};


		struct GraphicsElementInfos {
			GraphicsElementInfos(const nx::maths::Vector2f& _pos, const nx::maths::Vector2f& _size, const std::string& _identifier, const nx::env::MouseEventsContainer& events_)
				: pos(_pos), size(_size), identifier(_identifier), events(events_) {}

			GraphicsElementInfos(const GUIElementInfos& other)
				: pos(other.pos), size(other.size), identifier(other.identifier), events(other.events) {}

			nx::maths::Vector2f pos;
			nx::maths::Vector2f size;
			std::string identifier;
			nx::env::MouseEventsContainer events;
		};

		struct GraphicsSpriteInfos {
			GraphicsSpriteInfos(std::string const& spritesheetPath_, nx::maths::Vector2f const& sheetGrid_, nx::maths::Vector2f const& spriteSize_) : spritesheetPath(spritesheetPath_), sheetGrid(sheetGrid_), spriteSize(spriteSize_) {}
			GraphicsSpriteInfos(const GUISpriteInfos& other) : spritesheetPath(other.spritesheetPath), sheetGrid(other.sheetGrid), spriteSize(other.spriteSize) {}

			std::string spritesheetPath;
			nx::maths::Vector2f sheetGrid;
			nx::maths::Vector2f spriteSize;
		};

		struct GraphicsCircleInfos {
			GraphicsCircleInfos(float const radius_, nx::env::ColorInfo const& colorInfo_) : radius(radius_), colorInfo(colorInfo_) {}
			GraphicsCircleInfos(const GraphicsCircleInfos& other) : colorInfo(other.colorInfo) {}

			float radius;
			nx::env::ColorInfo colorInfo;
		};

		struct GraphicsRectInfos {
			GraphicsRectInfos(nx::env::ColorInfo const& colorInfo_) : colorInfo(colorInfo_) {}
			GraphicsRectInfos(const GraphicsRectInfos& other) : colorInfo(other.colorInfo) {}

			nx::env::ColorInfo colorInfo;
		};

		struct GraphicsConvexInfos {
			GraphicsConvexInfos(nx::env::ColorInfo const& colorInfo_) : colorInfo(colorInfo_) {}
			GraphicsConvexInfos(const GraphicsConvexInfos& other) : colorInfo(other.colorInfo) {}

			nx::env::ColorInfo colorInfo;
		};
	}
}

#endif /* NEXUS_ENGINE__ENVUTILS_HPP_ */