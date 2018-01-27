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
				: _entityInfos(other.getEntityInfos()), _opacity(other.getOpacity()), _texturePath(other.getTexturePath()), _shapeType(other.getShapeType()) {}
			~RendererComponent() {}

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

		public:
			// Getters
			uint8_t	const				getOpacity() const
			{
				return (this->_opacity);
			}

			std::string const &			getTexturePath() const
			{
				return (this->_texturePath);
			}

			ShapeType const &				getShapeType() const
			{
				return (this->_shapeType);
			}

			EntityInfos const & getEntityInfos() const
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
					this->_entityInfos = other.getEntityInfos();
					this->_opacity = other.getOpacity();
					this->_texturePath = other.getTexturePath();
					this->_shapeType = other.getShapeType();
				}
				return (*this);
			}
		};
	}
}

#endif /* NEXUS_ENGINE__RENDERERCOMPONENT_HPP_ */