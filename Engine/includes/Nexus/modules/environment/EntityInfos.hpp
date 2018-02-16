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
			bool 			  	_isModified;

		public:
			template <typename Archive>
			void serialize(Archive& ar, unsigned int version)
			{
				bool active = _active.load();
				ar & _name;
				ar & active;
				ar & _isModified;
			}

		public:
			EntityInfos(std::string const& name_) : _name(name_), _active(true), _isModified(true) {}
			EntityInfos(std::string const& name_, bool const active_) : _name(name_), _active(active_), _isModified(true) {}
			EntityInfos() : _name(""), _active(true), _isModified(true) {}
			EntityInfos(const EntityInfos& other) : _name(other.getNameConst()), _active(other.getActiveConst()), _isModified(true) {}
			~EntityInfos() {}

		public:
			//Setters
			void 				setIsModified(const bool isModified){
				_isModified = isModified;
			}

			void				setName(const std::string &name)
			{
				this->_name = name;
				_isModified = true;
			}
			
			void				setActive(const bool active)
			{
				this->_active = active;
				_isModified = true;
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

			const std::string&	getName()
			{
				return (this->_name);
			}

			bool			getActive()
			{
				return (this->_active);
			}

			bool const 			getIsModified() const{
				return _isModified;
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