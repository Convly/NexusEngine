#ifndef NEXUS_ENGINE__TRANSFORMCOMPONENT_HPP_
#define NEXUS_ENGINE__TRANSFORMCOMPONENT_HPP_

# include "../EntityInfos.hpp"
# include "Nexus/modules/maths/maths.hpp"
# include "Nexus/modules/physics/physics.hpp"

namespace nx
{
	namespace env
	{
		class TransformComponent
		{
		private:
			EntityInfos				_entityInfos;
			nx::maths::Vector2f		_pos;
			std::atomic<uint16_t>	_rotation;
			nx::maths::Vector2f		_size;
			nx::physics::Force2d	_direction;

		public:
			TransformComponent(std::string const& _name)
				: _entityInfos(_name), _rotation(0) {}
			TransformComponent(std::string const& _name, nx::maths::Vector2f const& pos)
				: _entityInfos(_name), _pos(pos), _rotation(0) {}
			TransformComponent(std::string const& _name, nx::maths::Vector2f const& pos, uint8_t const rotation)
				: _entityInfos(_name), _pos(pos), _rotation(rotation) {}
			TransformComponent(std::string const& _name, nx::maths::Vector2f const& pos, uint8_t const rotation, nx::maths::Vector2f const& size)
				: _entityInfos(_name), _pos(pos), _rotation(rotation), _size(size) {}
			TransformComponent(std::string const& _name, nx::maths::Vector2f const& pos, uint8_t const rotation, nx::maths::Vector2f const& size, nx::physics::Force2d const& direction)
				: _entityInfos(_name), _pos(pos), _rotation(rotation), _size(size), _direction(direction) {}
			TransformComponent(const TransformComponent& other) 
				: _entityInfos(other.getEntityInfosConst()), _pos(other.getPos()), _rotation(other.getRotationConst()), _size(other.getSize()), _direction(other.getDirection()) {}
			~TransformComponent() {}

		public:
			bool isModified(){
				if (_entityInfos.getIsModified()){
					return true;
				}
				return false;
			}

			// Setters
			void					setPos(nx::maths::Vector2f const& pos)
			{
				this->_pos = pos;
				_entityInfos.setIsModified(true);
			}

			void					setRotation(uint16_t const rotation)
			{
				this->_rotation = (rotation >= 360) ? (rotation - 360) : (rotation);
				_entityInfos.setIsModified(true);
			}

			void					setSize(nx::maths::Vector2f const& size)
			{
				this->_size = size;
				_entityInfos.setIsModified(true);
			}

			void					setDirection(nx::physics::Force2d const& direction)
			{
				this->_direction = direction;
				_entityInfos.setIsModified(true);
			}

		public:
			// Getters
			const nx::maths::Vector2f&	getPos() const
			{
				return (this->_pos);
			}

			uint16_t				getRotation()
			{
				return (this->_rotation.load());
			}

			const uint16_t				getRotationConst() const
			{
				return (this->_rotation.load());
			}

			const nx::maths::Vector2f&	getSize() const
			{
				return (this->_size);
			}

			const nx::physics::Force2d&	getDirection() const
			{
				return (this->_direction);
			}

		public:
			EntityInfos& getEntityInfos()
			{
				return (this->_entityInfos);
			}

			const EntityInfos& getEntityInfosConst() const
			{
				return (this->_entityInfos);
			}

		public:
			TransformComponent& operator=(const TransformComponent& other)
			{
				if (this != &other)
				{
					this->_entityInfos = other.getEntityInfosConst();
					this->_pos = other.getPos();
					this->_rotation = other.getRotationConst();
					this->_size = other.getSize();
					this->_direction = other.getDirection();
				}
				return (*this);
			}
		};
	}
}

#endif /* NEXUS_ENGINE__TRANSFORMCOMPONENT_HPP_ */