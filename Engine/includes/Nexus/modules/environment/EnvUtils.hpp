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
				: _red(other.getRedConst()), _green(other.getGreenConst()), _blue(other.getBlueConst()), _alpha(other.getAlphaConst()) {}

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
			uint32_t	getRed()
			{
				return (this->_red);
			}

			uint32_t	getGreen()
			{
				return (this->_green);
			}

			uint32_t	getBlue()
			{
				return (this->_blue);
			}

			uint32_t	getAlpha()
			{
				return (this->_alpha);
			}

		public:
			// Getters const
			uint32_t const	getRedConst() const
			{
				return (this->_red);
			}

			uint32_t const	getGreenConst() const
			{
				return (this->_green);
			}

			uint32_t const	getBlueConst() const
			{
				return (this->_blue);
			}

			uint32_t const	getAlphaConst() const
			{
				return (this->_alpha);
			}

		public:
			RGBa const & operator=(const RGBa & other)
			{
				if (this != &other)
				{
					this->_red = other.getRedConst();
					this->_green = other.getGreenConst();
					this->_blue = other.getBlueConst();
					this->_alpha = other.getAlphaConst();
				}
				return (*this);
			}

		};

		class ColorInfo {

			nx::env::RGBa				_backgroundColor;
			nx::env::RGBa				_borderColor;
			std::atomic<unsigned int>	_borderThickness;

		public:
			ColorInfo(const nx::env::RGBa& backgroundColor_, const nx::env::RGBa& borderColor_, const unsigned int borderThickness_)
				: _backgroundColor(backgroundColor_), _borderColor(borderColor_), _borderThickness(borderThickness_) {}

			ColorInfo(const nx::env::ColorInfo& other)
				: _backgroundColor(other.getBackgroundColorConst()), _borderColor(other.getBorderColorConst()), _borderThickness(other.getBorderThicknessConst()) {}

		public:
			// Setter
			void	setBackgroundColor(const nx::env::RGBa & backgroundColor)
			{
				this->_backgroundColor = backgroundColor;
			}

			void	setBorderColor(const ::nx::env::RGBa & borderColor)
			{
				this->_borderColor = borderColor;
			}

			void 	setBorderThickness(const unsigned int borderThickness)
			{
				this->_borderThickness = borderThickness;
			}

		public:
			// Getter
			nx::env::RGBa &		getBackgroundColor()
			{
				return (this->_backgroundColor);
			}

			nx::env::RGBa &		getBorderColor()
			{
				return (this->_borderColor);
			}

			unsigned int 		getBorderThickness()
			{
				return (this->_borderThickness.load());
			}

		public:
			// Getter const
			nx::env::RGBa const &	getBackgroundColorConst() const
			{
				return (this->_backgroundColor);
			}

			nx::env::RGBa const &	getBorderColorConst() const
			{
				return (this->_borderColor);
			}

			unsigned int const 		getBorderThicknessConst() const
			{
				return (this->_borderThickness.load());
			}

		public:
			ColorInfo const & operator=(const ColorInfo & other)
			{
				if (this != &other)
				{
					this->_backgroundColor = other.getBackgroundColorConst();
					this->_borderColor = other.getBorderColorConst();
					this->_borderThickness = other.getBorderThicknessConst();
				}
				return (*this);
			}
		};

		class TextInfo {

			std::string					_fontPath;
			std::string					_textLabel;
			std::atomic<unsigned int>	_fontSize;
			nx::env::RGBa				_textColor;
			std::atomic<uint32_t>		_textStyle;

		public:
			TextInfo(const std::string& fontPath_, const std::string& textLabel_, const unsigned int fontSize_, const nx::env::RGBa& textColor_, const uint32_t textStyle_)
				: _fontPath(fontPath_), _textLabel(textLabel_), _fontSize(fontSize_), _textColor(textColor_), _textStyle(textStyle_) {}

			TextInfo(const nx::env::TextInfo& other)
				: _fontPath(other.getFontPathConst()), _textLabel(other.getTextLabelConst()), _fontSize(other.getFontSizeConst()), _textColor(other.getTextColorConst()), _textStyle(other.getTextStyleConst()) {}

		public:
			//Setters
			void	setFontPath(const std::string & fontPath)
			{
				this->_fontPath = fontPath;
			}

			void	setTextLabel(const std::string & textLabel)
			{
				this->_textLabel = textLabel;
			}

			void	setFontSize(unsigned int fontSize)
			{
				this->_fontSize = fontSize;
			}

			void	setTextColor(const nx::env::RGBa & textColor)
			{
				this->_textColor = textColor;
			}

			void	setTextStyle(const uint32_t textStyle)
			{
				this->_textStyle = textStyle;
			}

		public:
			// Getters
			std::string	&	getFontPath()
			{
				return (this->_fontPath);
			}

			std::string	&	getTextLabel()
			{
				return (this->_textLabel);
			}

			unsigned int	getFontSize()
			{
				return (this->_fontSize);
			}

			nx::env::RGBa &	getTextColor()
			{
				return (this->_textColor);
			}

			uint32_t		getTextStyle()
			{
				return (this->_textStyle);
			}

		public:
			// Getters const
			std::string	const &	getFontPathConst() const
			{
				return (this->_fontPath);
			}

			std::string	const &	getTextLabelConst() const
			{
				return (this->_textLabel);
			}

			unsigned int const	getFontSizeConst() const
			{
				return (this->_fontSize);
			}

			nx::env::RGBa const	getTextColorConst() const
			{
				return (this->_textColor);
			}

			uint32_t const		getTextStyleConst() const
			{
				return (this->_textStyle);
			}

		public:
			const TextInfo & operator=(const TextInfo & other)
			{
				if (this != &other)
				{
					this->_fontPath = other.getFontPathConst();
					this->_textLabel = other.getTextLabelConst();
					this->_fontSize = other.getFontSizeConst();
					this->_textColor = other.getTextColorConst();
					this->_textStyle = other.getTextStyleConst();
				}
				return (*this);
			}

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

		class GUIButtonInfos {
			std::atomic<bool>	_isPushButton;
			nx::env::ColorInfo	_colorInfo;
			nx::env::TextInfo	_textInfo;

		public:
			GUIButtonInfos(bool const isPushButton_, nx::env::ColorInfo const& colorInfo_, nx::env::TextInfo const& textInfo_) : _isPushButton(isPushButton_), _colorInfo(colorInfo_), _textInfo(textInfo_) {}
			GUIButtonInfos(const GUIButtonInfos& other) : _isPushButton(other.getIsPushButtonConst()), _colorInfo(other.getColorInfoConst()), _textInfo(other.getTextInfoConst()) {}

		public:
			//Setters
			void	setIsPushButton(bool const isPushButton)
			{
				this->_isPushButton = isPushButton;
			}

			void	setColorInfo(const nx::env::ColorInfo & colorInfo)
			{
				this->_colorInfo = colorInfo;
			}

			void	setTextInfo(const nx::env::TextInfo & textInfo)
			{
				this->_textInfo = textInfo;
			}

		public:
			//Getters
			bool					getIsPushButton()
			{
				return (this->_isPushButton);
			}

			nx::env::ColorInfo &	getColorInfo()
			{
				return (this->_colorInfo);
			}

			nx::env::TextInfo &		getTextInfo()
			{
				return (this->_textInfo);
			}

		public:
			//Getters const
			bool const					getIsPushButtonConst() const
			{
				return (this->_isPushButton);
			}

			nx::env::ColorInfo const &	getColorInfoConst() const
			{
				return (this->_colorInfo);
			}

			nx::env::TextInfo const &	getTextInfoConst() const
			{
				return (this->_textInfo);
			}

		public:
			GUIButtonInfos const & operator=(const GUIButtonInfos & other)
			{
				if (this != &other)
				{
					this->_isPushButton = other.getIsPushButtonConst();
					this->_colorInfo = other.getColorInfoConst();
					this->_textInfo = other.getTextInfoConst();
				}
				return (*this);
			}
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