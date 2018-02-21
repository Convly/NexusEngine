#ifndef NEXUS_ENGINE__RENDERERCOMPONENT_HPP_
#define NEXUS_ENGINE__RENDERERCOMPONENT_HPP_

#include "../EnvUtils.hpp"
# include "../EntityInfos.hpp"

namespace nx
{
	namespace env
	{
		enum ShapeType : int
		{
			UNDEFINED = -1,
			RECTSHAPE = 0,
			CIRCLESHAPE = 1,
			CONVEXSHAPE
		};

		class RendererComponent
		{
			EntityInfos				_entityInfos;
			uint8_t					_opacity;
			std::string				_texturePath;
			ShapeType				_shapeType;
			ColorInfo				_color;
			maths::Vector2f 		_sheetGrid;
			maths::Vector2f 		_spriteSize;
			uint8_t				 	_radius;

		public:
			RendererComponent() : _radius(0) {}
			RendererComponent(std::string const& _name)
				: _entityInfos(_name), _opacity(100), _shapeType(ShapeType::UNDEFINED), _radius(0) {}
			RendererComponent(std::string const& _name, std::string const& texturePath)
				: _entityInfos(_name), _opacity(100), _texturePath(texturePath), _shapeType(ShapeType::UNDEFINED), _radius(0) {}
			RendererComponent(std::string const& _name, std::string const& texturePath, ShapeType const shapeType)
				: _entityInfos(_name), _opacity(100), _texturePath(texturePath), _shapeType(shapeType), _radius(0) {}
			RendererComponent(std::string const& _name, uint8_t const opacity, std::string const& texturePath, ShapeType const shapeType)
				: _entityInfos(_name), _opacity(opacity), _texturePath(texturePath), _shapeType(shapeType), _radius(0) {}
			RendererComponent(const RendererComponent & other)
				:	_entityInfos(other.getEntityInfosConst()),
					_opacity(other.getOpacityConst()),
					_texturePath(other.getTexturePathConst()),
					_shapeType(other.getShapeTypeConst()),
					_color(other.getColorInfoConst()),
					_sheetGrid(other.getSheetGridConst()),
					_spriteSize(other.getSpriteSizeConst()),
					_radius(other.getRadiusConst())
				{}
			~RendererComponent() {}

		public:
			template <typename Archive>
			void serialize(Archive& ar, unsigned int version)
			{
				ar & _entityInfos;
				ar & _opacity;
				ar & _texturePath;
				ar & _shapeType;
				ar & _color;
				ar & _sheetGrid;
				ar & _spriteSize;
				ar & _radius;
			}

			bool isModified(){
				if (_entityInfos.getIsModified()){
					return true;
				}
				return false;
			}

			// Setters
			void		setOpacity(uint8_t const opacity)
			{
				this->_opacity = (opacity > 100) ? (100) : (opacity);
				_entityInfos.setIsModified(true);
			}

			void		setTexturePath(std::string const& texturePath)
			{
				this->_texturePath = texturePath;
				_entityInfos.setIsModified(true);
			}

			void		setShapeType(ShapeType const shapeType)
			{
				this->_shapeType = shapeType;
				_entityInfos.setIsModified(true);
			}

			void 		setBackgroundColor(const nx::env::RGBa& backgroundColor){
				this->_color.setBackgroundColor(backgroundColor);
				_entityInfos.setIsModified(true);
			}

			void 		setBorderColor(const nx::env::RGBa& borderColor){
				this->_color.setBorderColor(borderColor);
				_entityInfos.setIsModified(true);
			}

			void 		setBorderThickness(int borderThickness){
				this->_color.setBorderThickness(borderThickness);
				_entityInfos.setIsModified(true);
			}

			void 		setSheetGrid(const maths::Vector2f& vec){
				_entityInfos.setIsModified(true);
				_sheetGrid = vec;
			}

			void 		setSpriteSize(const maths::Vector2f& vec) {
				_entityInfos.setIsModified(true);
				_spriteSize = vec;
			}

			void 		setRadius(int const radius) {
				_entityInfos.setIsModified(true);
				_radius = radius;
			}

		public:
			// Getters
			uint8_t						getOpacity()
			{
				return (this->_opacity);
			}

			uint8_t	const				getOpacityConst() const
			{
				return (this->_opacity);
			}

			std::string const			getTexturePathConst() const
			{
				return (this->_texturePath);
			}

			std::string					getTexturePath()
			{
				return (this->_texturePath);
			}

			ShapeType const				getShapeTypeConst() const
			{
				return (this->_shapeType);
			}

			ShapeType					getShapeType()
			{
				return (this->_shapeType);
			}

			EntityInfos const & getEntityInfosConst() const
			{
				return (this->_entityInfos);
			}

			EntityInfos & getEntityInfos()
			{
				return (this->_entityInfos);
			}

			nx::env::RGBa & getBackgroundColor() {
				return (this->_color.getBackgroundColor());
			}

			nx::env::RGBa const & getBackgroundColorConst() const {
				return (this->_color.getBackgroundColorConst());
			}

			nx::env::RGBa & getBorderColor() {
				return (this->_color.getBorderColor());
			}

			nx::env::RGBa const & getBorderColorConst() const {
				return (this->_color.getBorderColorConst());
			}

			int 		getBorderThickness() {
				return (this->_color.getBorderThickness());
			}

			int const		getBorderThicknessConst() const {
				return (this->_color.getBorderThicknessConst());
			}

			maths::Vector2f & 	getSheetGrid() {
				return (this->_sheetGrid);
			}

			maths::Vector2f const & 	getSheetGridConst() const {
				return (this->_sheetGrid);
			}

			maths::Vector2f & 	getSpriteSize() {
				return (this->_spriteSize);
			}

			maths::Vector2f const & 	getSpriteSizeConst() const {
				return (this->_spriteSize);
			}

			ColorInfo & getColorInfo() {
				return (this->_color);
			}

			ColorInfo const & getColorInfoConst() const {
				return (this->_color);
			}

			uint8_t						getRadius()
			{
				return (this->_radius);
			}

			uint8_t	const				getRadiusConst() const
			{
				return (this->_radius);
			}

		public:
			RendererComponent &		operator=(const RendererComponent & other)
			{
				if (this != &other)
				{
					this->_entityInfos = other.getEntityInfosConst();
					this->_opacity = other.getOpacityConst();
					this->_texturePath = other.getTexturePathConst();
					this->_shapeType = other.getShapeTypeConst();
					this->setBackgroundColor(other.getBackgroundColorConst());
					this->setBorderColor(other.getBorderColorConst());
					this->setBorderThickness(other.getBorderThicknessConst());
					this->_sheetGrid = other.getSheetGridConst();
					this->_spriteSize = other.getSpriteSizeConst();
					this->_radius = other.getRadiusConst();
				}
				return (*this);
			}
		};
	}
}

#endif /* NEXUS_ENGINE__RENDERERCOMPONENT_HPP_ */