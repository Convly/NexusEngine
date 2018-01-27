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

		private:
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
			RGBa & operator=(const RGBa & other)
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

		private:
			nx::env::RGBa				_backgroundColor;
			nx::env::RGBa				_borderColor;
			std::atomic<unsigned int>	_borderThickness;

		public:
			ColorInfo() : _borderThickness(0){}
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
			ColorInfo & operator=(const ColorInfo & other)
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

		private:
			std::string					_fontPath;
			std::string					_textLabel;
			std::atomic<unsigned int>	_fontSize;
			nx::env::RGBa				_textColor;
			std::atomic<uint32_t>		_textStyle;

		public:
			TextInfo() : _fontSize(0), _textStyle(0){}
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
			std::string		getFontPath()
			{
				return (this->_fontPath);
			}

			std::string		getTextLabel()
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
			TextInfo & operator=(const TextInfo & other)
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

		class GUIElementInfos {
		public:
			GUIElementInfos() : _active(true), _isModified(true) {}
			GUIElementInfos(const nx::maths::Vector2f& pos, const nx::maths::Vector2f& size, const std::string& identifier, const nx::env::MouseEventsContainer& events)
				: _active(true), _pos(pos), _size(size), _identifier(identifier), _events(events), _isModified(true) {}

			GUIElementInfos(const GUIElementInfos& other)
				: _active(other.getActive()), _pos(other.getPos()), _size(other.getSize()), _identifier(other.getIdentifier()), _events(other.getEvents()), _isModified(true) {}

		private:
			bool _active;
			nx::maths::Vector2f _pos;
			nx::maths::Vector2f _size;
			std::string _identifier;
			nx::env::MouseEventsContainer _events;
			bool _isModified;

		public:
			const bool getActive() const{
				return _active;
			}

			const nx::maths::Vector2f& getPos() const{
				return _pos;
			}

			const nx::maths::Vector2f& getSize() const{
				return _size;
			}

			const std::string& getIdentifier() const{
				return _identifier;
			}

			const nx::env::MouseEventsContainer& getEvents() const{
				return _events;
			}

			nx::env::MouseEventsContainer& getEvents(){
				_isModified = true;
				return _events;
			}

			const bool getIsModified() const{
				return _isModified;
			}

		public:
			void setActive(const bool active){
				_active = active;
				_isModified = true;
			}

			void setPos(const nx::maths::Vector2f& pos){
				_pos = pos;
				_isModified = true;
			}

			void setSize(const nx::maths::Vector2f& size){
				_size = size;
				_isModified = true;
			}

			void setIdentifier(const std::string& identifier){
				_identifier = identifier;
				_isModified = true;
			}

			void setEvents(const nx::env::MouseEventsContainer& events){
				_events = events;
				_isModified = true;
			}

			void setIsModified(const bool isModified){
				_isModified = isModified;
			}
		};

		class GUIButtonInfos {

		private:
			std::atomic<bool>	_isPushButton;
			nx::env::ColorInfo	_colorInfo;
			nx::env::TextInfo	_textInfo;
			bool 				_isModified;

		public:
			GUIButtonInfos()  : _isPushButton(true), _isModified(true){}
			GUIButtonInfos(bool const isPushButton_, nx::env::ColorInfo const& colorInfo_, nx::env::TextInfo const& textInfo_) : _isPushButton(isPushButton_), _colorInfo(colorInfo_), _textInfo(textInfo_), _isModified(true) {}
			GUIButtonInfos(const GUIButtonInfos& other) : _isPushButton(other.getIsPushButtonConst()), _colorInfo(other.getColorInfoConst()), _textInfo(other.getTextInfoConst()), _isModified(true) {}

		public:
			//Setters
			void	setIsPushButton(bool const isPushButton)
			{
				this->_isPushButton = isPushButton;
				_isModified = true;
			}

			void	setColorInfo(const nx::env::ColorInfo & colorInfo)
			{
				this->_colorInfo = colorInfo;
				_isModified = true;
			}

			void	setTextInfo(const nx::env::TextInfo & textInfo)
			{
				this->_textInfo = textInfo;
				_isModified = true;
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
			GUIButtonInfos & operator=(const GUIButtonInfos & other)
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

		class GUICheckboxInfos {
		public:
			GUICheckboxInfos() : _isModified(true){}
			GUICheckboxInfos(nx::env::ColorInfo const& colorInfo) : _colorInfo(_colorInfo), _isModified(true) {}
			GUICheckboxInfos(GUICheckboxInfos const& other) : _colorInfo(other.getColorInfo()), _isModified(true) {}

		private:
			nx::env::ColorInfo _colorInfo;
			bool _isModified;
		
		public:
			void setIsModified(const bool isModified){
				_isModified = isModified;
			}

			void setColorInfo(const nx::env::ColorInfo& colorInfo){
				_colorInfo = colorInfo;
				_isModified = true;
			}

		public:
			const bool getIsModified() const{
				return _isModified;
			}

			const nx::env::ColorInfo& getColorInfo() const{
				return _colorInfo;
			}

			nx::env::ColorInfo& getColorInfo(){
				_isModified = true;
				return _colorInfo;
			}
		};

		class GUIProgressBarInfos {
		public:
			GUIProgressBarInfos() : _isModified(true){}
			GUIProgressBarInfos(nx::env::ColorInfo const& colorInfo, nx::env::TextInfo const& textInfo) : _colorInfo(colorInfo), _textInfo(textInfo), _isModified(true) {}
			GUIProgressBarInfos(const GUIProgressBarInfos& other) : _colorInfo(other.getColorInfo()), _textInfo(other.getTextInfo()), _isModified(true) {}

		private:
			nx::env::ColorInfo _colorInfo;
			nx::env::TextInfo _textInfo;
			bool _isModified;
		
		public:
			void setIsModified(const bool isModified){
				_isModified = isModified;
			}

			void setTextInfo(const nx::env::TextInfo& textInfo){
				_textInfo = textInfo;
				_isModified = true;
			}

			void setColorInfo(const nx::env::ColorInfo& colorInfo){
				_colorInfo = colorInfo;
				_isModified = true;
			}

		public:
			const bool getIsModified() const{
				return _isModified;
			}

			const nx::env::ColorInfo& getColorInfo() const{
				return _colorInfo;
			}

			const nx::env::TextInfo& getTextInfo() const{
				return _textInfo;
			}

		 	nx::env::ColorInfo& getColorInfo(){
				_isModified = true;
				return _colorInfo;
			}

		 	nx::env::TextInfo& getTextInfo(){
				_isModified = true;
				return _textInfo;
			}
		};

		class GUIComboBoxInfos {
		public:
			GUIComboBoxInfos() : _isModified(true){}
			GUIComboBoxInfos(nx::env::ColorInfo const& colorInfo, nx::env::TextInfo const& textInfo) : _colorInfo(colorInfo), _textInfo(textInfo), _isModified(true) {}
			GUIComboBoxInfos(const GUIComboBoxInfos& other) : _colorInfo(other.getColorInfo()), _textInfo(other.getTextInfo()), _isModified(true) {}

		private:
			nx::env::ColorInfo _colorInfo;
			nx::env::TextInfo _textInfo;
			bool _isModified;
		
		public:
			void setIsModified(const bool isModified){
				_isModified = isModified;
			}

			void setTextInfo(const nx::env::TextInfo& textInfo){
				_textInfo = textInfo;
				_isModified = true;
			}

			void setColorInfo(const nx::env::ColorInfo& colorInfo){
				_colorInfo = colorInfo;
				_isModified = true;
			}

		public:
			const bool getIsModified() const{
				return _isModified;
			}

			const nx::env::ColorInfo& getColorInfo() const{
				return _colorInfo;
			}

			nx::env::ColorInfo& getColorInfo(){
				_isModified = true;
				return _colorInfo;
			}

			const nx::env::TextInfo& getTextInfo() const{
				return _textInfo;
			}

			nx::env::TextInfo& getTextInfo(){
				_isModified = true;
				return _textInfo;
			}
		};

		class GUITextInputInfos {
		public:
			GUITextInputInfos() : _isModified(true){}
			GUITextInputInfos(nx::env::ColorInfo const& colorInfo, nx::env::TextInfo const& textInfo) : _colorInfo(colorInfo), _textInfo(textInfo), _isModified(true) {}
			GUITextInputInfos(const GUITextInputInfos& other) : _colorInfo(other.getColorInfo()), _textInfo(other.getTextInfo()), _isModified(true) {}

		private:
			nx::env::ColorInfo _colorInfo;
			nx::env::TextInfo _textInfo;
			bool _isModified;
		
		public:
			void setIsModified(const bool isModified){
				_isModified = isModified;
			}

			void setTextInfo(const nx::env::TextInfo& textInfo){
				_textInfo = textInfo;
				_isModified = true;
			}

			void setColorInfo(const nx::env::ColorInfo& colorInfo){
				_colorInfo = colorInfo;
				_isModified = true;
			}

		public:
			const bool getIsModified() const{
				return _isModified;
			}

			const nx::env::ColorInfo& getColorInfo() const{
				return _colorInfo;
			}

			const nx::env::TextInfo& getTextInfo() const{
				return _textInfo;
			}

			nx::env::ColorInfo& getColorInfo(){
				_isModified = true;
				return _colorInfo;
			}

			nx::env::TextInfo& getTextInfo(){
				_isModified = true;
				return _textInfo;
			}
		};

		class GUITextInfos {
		public:
			GUITextInfos() : _isModified(true){}
			GUITextInfos(nx::env::TextInfo const& textInfo) : _textInfo(textInfo), _isModified(true) {}
			GUITextInfos(const GUITextInfos& other) : _textInfo(other.getTextInfo()), _isModified(true) {}

		private:
			nx::env::TextInfo _textInfo;
			bool _isModified;
		
		public:
			void setIsModified(const bool isModified){
				_isModified = isModified;
			}

			void setTextInfo(const nx::env::TextInfo& textInfo){
				_textInfo = textInfo;
				_isModified = true;
			}

		public:
			const bool getIsModified() const{
				return _isModified;
			}

			const nx::env::TextInfo& getTextInfo() const{
				return _textInfo;
			}

		 	nx::env::TextInfo& getTextInfo(){
				_isModified = true;
				return _textInfo;
			}
		};

		class GUIImageInfos {
		public:
			GUIImageInfos() : _isModified(true){}
			GUIImageInfos(std::string const& imagePath) : _imagePath(imagePath), _isModified(true) {}
			GUIImageInfos(const GUIImageInfos& other) : _imagePath(other.getImagePath()), _isModified(true) {}

		private:
			std::string _imagePath;
			bool _isModified;
		
		public:
			void setIsModified(const bool isModified){
				_isModified = isModified;
			}

			void setImagePath(const std::string& imagePath){
				_imagePath = imagePath;
				_isModified = true;
			}

		public:
			const bool getIsModified() const{
				return _isModified;
			}

			const std::string& getImagePath() const{
				return _imagePath;
			}
		};

		class GUISpriteInfos {
		public:
			GUISpriteInfos() : _isModified(true){}
			GUISpriteInfos(std::string const& spritesheetPath, nx::maths::Vector2f const& sheetGrid, nx::maths::Vector2f const& spriteSize) : _spritesheetPath(spritesheetPath), _sheetGrid(sheetGrid), _spriteSize(spriteSize), _isModified(true) {}
			GUISpriteInfos(const GUISpriteInfos& other) : _spritesheetPath(other.getSpritesheetPath()), _sheetGrid(other.getSheetGrid()), _spriteSize(other.getSpriteSize()), _isModified(true) {}

		private:
			std::string _spritesheetPath;
			nx::maths::Vector2f _sheetGrid;
			nx::maths::Vector2f _spriteSize;
			bool _isModified;
		
		public:
			void setIsModified(const bool isModified){
				_isModified = isModified;
			}

			void setSheetGrid(const nx::maths::Vector2f& sheetGrid){
				_sheetGrid = sheetGrid;
				_isModified = true;
			}

			void setSpriteSize(const nx::maths::Vector2f& spriteSize){
				_spriteSize = spriteSize;
				_isModified = true;
			}

			void setSpritesheetPath(const std::string& spritesheetPath){
				_spritesheetPath = spritesheetPath;
				_isModified = true;
			}

		public:
			const bool getIsModified() const{
				return _isModified;
			}

			const nx::maths::Vector2f& getSheetGrid() const{
				return _sheetGrid;
			}

			const nx::maths::Vector2f& getSpriteSize() const{
				return _spriteSize;
			}

			const std::string& getSpritesheetPath() const{
				return _spritesheetPath;
			}
		};

		/////////////////////////////////////////////
		/*               	Graphic				   */
		/////////////////////////////////////////////

		struct GraphicsElementInfos {
			GraphicsElementInfos(const nx::maths::Vector2f& _pos, const nx::maths::Vector2f& _size, const std::string& _identifier, const nx::env::MouseEventsContainer& events_)
				: pos(_pos), size(_size), identifier(_identifier), events(events_) {}

			GraphicsElementInfos(const GUIElementInfos& other)
				: pos(other.getPos()), size(other.getSize()), identifier(other.getIdentifier()), events(other.getEvents()) {}

			nx::maths::Vector2f pos;
			nx::maths::Vector2f size;
			std::string identifier;
			nx::env::MouseEventsContainer events;
		};

		struct GraphicsSpriteInfos {
			GraphicsSpriteInfos(std::string const& spritesheetPath_, nx::maths::Vector2f const& sheetGrid_, nx::maths::Vector2f const& spriteSize_) : spritesheetPath(spritesheetPath_), sheetGrid(sheetGrid_), spriteSize(spriteSize_) {}
			GraphicsSpriteInfos(const GraphicsSpriteInfos& other) : spritesheetPath(other.spritesheetPath), sheetGrid(other.sheetGrid), spriteSize(other.spriteSize) {}

			std::string spritesheetPath;
			nx::maths::Vector2f sheetGrid;
			nx::maths::Vector2f spriteSize;
		};

		class GraphicsCircleInfos {

		private:
			std::atomic<float>	_radius;
			nx::env::ColorInfo	_colorInfo;

		public:
			GraphicsCircleInfos(float const radius_, nx::env::ColorInfo const& colorInfo_) : _radius(radius_), _colorInfo(colorInfo_) {}
			GraphicsCircleInfos(const GraphicsCircleInfos& other) : _radius(other.getRadiusConst()), _colorInfo(other.getColorInfoConst()) {}

		public:
			//Setters
			void	setRadius(const float radius)
			{
				this->_radius = radius;
			}

			void	setColorInfo(const nx::env::ColorInfo & colorInfo)
			{
				this->_colorInfo = colorInfo;
			}

		public:
			//Getters
			float					getRadius()
			{
				return (this->_radius);
			}

			nx::env::ColorInfo &	getColorInfo()
			{
				return (this->_colorInfo);
			}

		public:
			//Getters const
			float const					getRadiusConst() const
			{
				return (this->_radius);
			}

			nx::env::ColorInfo const &	getColorInfoConst() const
			{
				return (this->_colorInfo);
			}

		public:
			GraphicsCircleInfos & operator=(const GraphicsCircleInfos & other)
			{
				if (this != &other)
				{
					this->_colorInfo = other.getColorInfoConst();
					this->_radius = other.getRadiusConst();
				}
				return (*this);
			}
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