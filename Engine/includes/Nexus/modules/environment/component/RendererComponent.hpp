#ifndef NEXUS_ENGINE__RENDERERCOMPONENT_HPP_
#define NEXUS_ENGINE__RENDERERCOMPONENT_HPP_

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

		public:
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

			// Setters
			void		setOpacity(uint8_t const opacity)
			{
				this->_opacity = (opacity > 100) ? (100) : (opacity);
			}

			void		setTexturePath(std::string const& texturePath)
			{
				this->_texturePath = texturePath;
			}

			void		setShapeType(ShapeType const shapeType)
			{
				this->_shapeType = shapeType;
			}


			// Getters
			EntityInfos &			getEntityInfos()
			{
				return (this->_entityInfos);
			}

			uint8_t					getOpacity()
			{
				return (this->_opacity);
			}

			std::string &			getTexturePath()
			{
				return (this->_texturePath);
			}

			ShapeType &				getShapeType()
			{
				return (this->_shapeType);
			}

		public:
			// Getters const
			EntityInfos const & getEntityInfosConst() const
			{
				return (this->_entityInfos);
			}

			uint8_t	const				getOpacityConst() const
			{
				return (this->_opacity);
			}

			std::string const &			getTexturePathConst() const
			{
				return (this->_texturePath);
			}

			ShapeType const &				getShapeTypeConst() const
			{
				return (this->_shapeType);
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