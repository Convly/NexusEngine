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
			std::string			_name;
			std::atomic<bool>	_active;

		public:
			EntityInfos(std::string const& name_) : _name(name_), _active(true) {}
			EntityInfos(std::string const& name_, bool const active_) : _name(name_), _active(active_) {}
			EntityInfos() : _name(""), _active(true) {}
			EntityInfos(const EntityInfos &obj) : _name(obj.getName()), _active(obj.getActive()) {}
			~EntityInfos() {}

		public:
			const std::string &	getName() const
			{
				return (_name);
			}
			bool				getActive() const
			{
				return (_active.load());
			}

		public:
			void				setName(const std::string &name)
			{
				this->_name = name;
			}
			void				setActive(const bool active)
			{
				this->_active.store(active);
			}

		public:
			EntityInfos & operator=(const EntityInfos &other)
			{
				if (this != &other)
				{
					this->_name = other.getName();
					this->_active= other.getActive();
				}
				return (*this);
			}
		};
	}
}

#endif /* NEXUS_ENGINE__ENTITYINFOS_HPP_ */