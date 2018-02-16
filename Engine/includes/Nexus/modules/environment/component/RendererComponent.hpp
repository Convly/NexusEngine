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
			std::atomic<uint8_t>	_opacity;
			std::string				_texturePath;
			ShapeType				_shapeType;
			ColorInfo		_color;
			maths::Vector2f 	_sheetGrid;
			maths::Vector2f 	_spriteSize;

		public:
			RendererComponent() {}
			RendererComponent(std::string const& _name)
				: _entityInfos(_name), _opacity(100), _shapeType(ShapeType::UNDEFINED) {}
			RendererComponent(std::string const& _name, std::string const& texturePath)
				: _entityInfos(_name), _opacity(100), _texturePath(texturePath), _shapeType(ShapeType::UNDEFINED) {}
			RendererComponent(std::string const& _name, std::string const& texturePath, ShapeType const shapeType)
				: _entityInfos(_name), _opacity(100), _texturePath(texturePath), _shapeType(shapeType) {}
			RendererComponent(std::string const& _name, uint8_t const opacity, std::string const& texturePath, ShapeType const shapeType)
				: _entityInfos(_name), _opacity(opacity), _texturePath(texturePath), _shapeType(shapeType) {}
			RendererComponent(const RendererComponent & other)
				: _entityInfos(other.getEntityInfosConst()), _opacity(other.getOpacityConst()), _texturePath(other.getTexturePathConst()), _shapeType(other.getShapeTypeConst()) {}
			~RendererComponent() {}

		public:
			template <typename Archive>
			void serialize(Archive& ar, unsigned int version)
			{
				uint8_t opacity = _opacity.load();
				ar & _entityInfos;
				ar & opacity;
				ar & _texturePath;
				ar & _shapeType;
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

			void 		setSpriteSize(const maths::Vector2f& vec){
				_entityInfos.setIsModified(true);
				_spriteSize = vec;
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

		public:
			RendererComponent &		operator=(const RendererComponent & other)
			{
				if (this != &other)
				{
					this->_entityInfos = other.getEntityInfosConst();
					this->_opacity = other.getOpacityConst();
					this->_texturePath = other.getTexturePathConst();
					this->_shapeType = other.getShapeTypeConst();
				}
				return (*this);
			}
		};
	}
}

#endif /* NEXUS_ENGINE__RENDERERCOMPONENT_HPP_ */