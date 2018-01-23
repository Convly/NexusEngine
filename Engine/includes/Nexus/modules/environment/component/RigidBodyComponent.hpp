#ifndef NEXUS_ENGINE__RIGIDBODYCOMPONENT_HPP_
#define NEXUS_ENGINE__RIGIDBODYCOMPONENT_HPP_

# include "../EntityInfos.hpp"
# include "Nexus/modules/maths/maths.hpp"

namespace nx
{
	namespace env
	{
		class RigidBodyComponent
		{
			EntityInfos			_entityInfos;
			double				_mass;
			double				_bounciness;
			nx::maths::Vector2f	_size;

		public:
			RigidBodyComponent(std::string const& _name)
				: _entityInfos(_name), _mass(0), _bounciness(0) {}
			RigidBodyComponent(std::string const& _name, double const mass)
				: _entityInfos(_name), _mass(mass), _bounciness(0) {}
			RigidBodyComponent(std::string const& _name, double const mass, double const bouciness)
				: _entityInfos(_name), _mass(mass), _bounciness(bouciness) {}
			RigidBodyComponent(std::string const& _name, double const mass, double const bouciness, nx::maths::Vector2f const& size)
				: _entityInfos(_name), _mass(mass), _bounciness(bouciness), _size(size) {}
			~RigidBodyComponent() {}

			// Setters
			void		setMass(double const mass)
			{
				this->_mass = mass;
			}

			void		setBounciness(double const bounciness)
			{
				this->_bounciness = bounciness;
			}

			void		setSize(nx::maths::Vector2f const& size)
			{
				this->_size = size;
			}

			// Getters
			EntityInfos &			getEntityInfos()
			{
				return (this->_entityInfos);
			}

			double					getMass()
			{
				return (this->_mass);
			}

			double					getBounciness()
			{
				return (this->_bounciness);
			}

			nx::maths::Vector2f &	getSize()
			{
				return (this->_size);
			}
		};
	}
}

#endif /* NEXUS_ENGINE__RIGIDBODYCOMPONENT_HPP_ */