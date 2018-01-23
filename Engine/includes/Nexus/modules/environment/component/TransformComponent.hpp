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
			EntityInfos				_entityInfos;
			nx::maths::Vector2f		_pos;
			uint16_t				_rotation;
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
			~TransformComponent() {}

			// Setters
			void					setPos(nx::maths::Vector2f const& pos)
			{
				this->_pos = pos;
			}

			void					setRotation(uint16_t const rotation)
			{
				this->_rotation = (rotation >= 360) ? (rotation - 360) : (rotation);
			}

			void					setSize(nx::maths::Vector2f const& size)
			{
				this->_size = size;
			}

			void					setDirection(nx::physics::Force2d const& direction)
			{
				this->_direction = direction;
			}

			// Getters
			EntityInfos &			getEntityInfos()
			{
				return (this->_entityInfos);
			}

			nx::maths::Vector2f &	getPos()
			{
				return (this->_pos);
			}

			uint16_t				getRotation()
			{
				return (this->_rotation);
			}

			nx::maths::Vector2f &	getSize()
			{
				return (this->_size);
			}

			nx::physics::Force2d &	getDirection()
			{
				return (this->_direction);
			}
		};
	}
}

#endif /* NEXUS_ENGINE__TRANSFORMCOMPONENT_HPP_ */