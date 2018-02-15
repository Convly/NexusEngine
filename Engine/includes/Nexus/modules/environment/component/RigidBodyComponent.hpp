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
		private:
			EntityInfos			_entityInfos;
			std::atomic<double>	_mass;
			std::atomic<double>	_bounciness;
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
			RigidBodyComponent(const RigidBodyComponent & other)
				: _entityInfos(other.getEntityInfosConst()), _mass(other.getMassConst()), _bounciness(other.getBouncinessConst()), _size(other.getSizeConst()) {}
			~RigidBodyComponent() {}

			bool isModified(){
				if (_entityInfos.getIsModified()){
					return true;
				}
				return false;
			}

			// Setters
			void		setMass(double const mass)
			{
				this->_mass = mass;
				_entityInfos.setIsModified(true);
			}

			void		setBounciness(double const bounciness)
			{
				this->_bounciness = bounciness;
				_entityInfos.setIsModified(true);
			}

			void		setSize(nx::maths::Vector2f const& size)
			{
				this->_size = size;
				_entityInfos.setIsModified(true);
			}

		public:
			// Getters const
			double const				getMassConst() const
			{
				return (this->_mass);
			}

			double						getMass()
			{
				return (this->_mass);
			}

			double const				getBouncinessConst() const
			{
				return (this->_bounciness);
			}

			double						getBounciness()
			{
				return (this->_bounciness);
			}

			nx::maths::Vector2f const&	getSizeConst() const
			{
				return (this->_size);
			}

			nx::maths::Vector2f			getSize()
			{
				return (this->_size);
			}
			
			EntityInfos&				getEntityInfos()
			{
				return (this->_entityInfos);
			}

			EntityInfos const&			getEntityInfosConst() const
			{
				return (this->_entityInfos);
			}

		public:
			RigidBodyComponent & operator=(const RigidBodyComponent & other)
			{
				if (this != &other)
				{
					this->_entityInfos = other.getEntityInfosConst();
					this->_mass.store(other.getMassConst());
					this->_bounciness.store(other.getBouncinessConst());
					this->_size = other.getSizeConst();
				}
				return (*this);
			}
		};
	}
}

#endif /* NEXUS_ENGINE__RIGIDBODYCOMPONENT_HPP_ */