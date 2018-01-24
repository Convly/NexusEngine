#ifndef NEXUS_ENGINE__ENTITYINFOS_HPP_
#define NEXUS_ENGINE__ENTITYINFOS_HPP_

# include <string>
# include <atomic>

namespace nx
{
	namespace env
	{
		class EntityInfos
		{
		private:
			std::string			_name;
			std::atomic<bool>	_active;

		public:
			EntityInfos(std::string const& name_) : _name(name_), _active(true) {}
			EntityInfos(std::string const& name_, bool const active_) : _name(name_), _active(active_) {}
			EntityInfos() : _name(""), _active(true) {}
			EntityInfos(const EntityInfos & other) : _name(other.getNameConst()), _active(other.getActiveConst()) {}
			~EntityInfos() {}

		public:
			//Setters
			void				setName(const std::string &name)
			{
				this->_name = name;
			}
			
			void				setActive(const bool active)
			{
				this->_active = active;
			}

		public:
			//Getters
			std::string &	getName()
			{
				return (this->_name);
			}

			bool			getActive()
			{
				return (this->_active);
			}

		public:
			//Getters Const
			const std::string &	getNameConst() const
			{
				return (this->_name);
			}

			bool const			getActiveConst() const
			{
				return (this->_active);
			}

		public:
			EntityInfos & operator=(const EntityInfos &other)
			{
				if (this != &other)
				{
					this->_name = other.getNameConst();
					this->_active= other.getActiveConst();
				}
				return (*this);
			}
		};
	}
}

#endif /* NEXUS_ENGINE__ENTITYINFOS_HPP_ */