#ifndef NEXUS_ENGINE__MODULE_PHYSICS_COLLIDER_HPP_
# define NEXUS_ENGINE__MODULE_PHYSICS_COLLIDER_HPP_

# include "Nexus/modules/maths/maths.hpp"

namespace nx
{
	namespace physics
	{
		class Collider : public nx::maths::Rect
		{

		public:
			Collider() {}
			Collider(nx::maths::Vector2f const& pos) : Rect(pos) {}
			Collider(nx::maths::Vector2f const& pos, nx::maths::Vector2f const& size) : Rect(pos, size) {}
			~Collider() {}

			// Setters
			void	setPosition(nx::maths::Vector2f const& pos)
			{
				nx::maths::Rect::setPosition(pos);
			}

			void	setSize(nx::maths::Vector2f const& size)
			{
				nx::maths::Rect::setSize(size);
			}

			void	setWidth(float const width)
			{
				nx::maths::Rect::setWidth(width);
			}

			void	setHeight(float const height)
			{
				nx::maths::Rect::setHeight(height);
			}

			// Getters
			nx::maths::Vector2f const&	getPosition() const
			{
				return (nx::maths::Rect::position());
			}

			nx::maths::Vector2f const&	getSize() const
			{
				return (nx::maths::Rect::size());
			}

			float const					getWidth() const
			{
				return (nx::maths::Rect::width());
			}

			float const					getHeight() const
			{
				return (nx::maths::Rect::height());
			}

			// Comparison methods
			static bool const isCollided(Collider const& collider1, Collider const& collider2)
			{
				return (
					(collider1.getPosition().x < collider2.getPosition().x + collider2.getWidth()) &&
					(collider1.getPosition().x + collider1.getWidth() > collider2.getPosition().x) &&
					(collider1.getPosition().y < collider2.getPosition().y + collider2.getHeight()) &&
					(collider1.getPosition().y + collider1.getHeight()> collider2.getPosition().y)
					);
			}

			bool const isCollided(Collider const& other)
			{
				return (this->isCollided(*this, other));
			}

			static bool const isNotCollided(Collider const& collider1, Collider const& collider2)
			{
				return (!nx::physics::Collider::isCollided(collider1, collider2));
			}

			bool const isNotCollided(Collider const& other)
			{
				return (this->isNotCollided(*this, other));
			}

			//Operators
			bool operator==(Collider const& other) const
			{
				return (this->getPosition() == other.getPosition() && this->getSize() == other.getSize());
			}
			bool operator!=(Collider const& other) const
			{
				return !(*this == other);
			}

		};
	}
}

#endif /* NEXUS_ENGINE__MODULE_PHYSICS_COLLIDER_HPP_ */