#ifndef NEXUS_ENGINE__SFX_HPP_
#define NEXUS_ENGINE__SFX_HPP_

# include "EntityInfos.hpp"
# include "EnvUtils.hpp"

namespace nx
{
	namespace env
	{
		class Sfx
		{
		public: 
			enum SFX_TYPE
			{
				SOUND,
				MUSIC
			};

		private:
			EntityInfos			_entityInfos;
			std::string			_path;
			SFX_TYPE			_type;
			bool				_isModified;
			bool				_isPlay;

		public:
			template <typename Archive>
			void serialize(Archive& ar, unsigned int version)
			{
				ar & _entityInfos;
				ar & _path;
				ar & _type;
				ar & _isModified;
				ar & _isPlay;
			}

		public:
			Sfx() {}
			Sfx(std::string const& _name) : _entityInfos(_name), _path(_name), _type(SFX_TYPE::SOUND), _isPlay(false), _isModified(false) {}
			Sfx(std::string const& _name, SFX_TYPE type) : _entityInfos(_name), _path(_name), _type(type), _isPlay(false), _isModified(false) {}
			Sfx(std::string const& _name, SFX_TYPE, bool const _active) : _entityInfos(_name, _active), _path(_name), _type(_type), _isPlay(false), _isModified(false) {}
			~Sfx() {}

			bool				isModified()
			{
				if (_entityInfos.getIsModified() || _isModified)
					return true;
				return false;
			}

			void				resetModified()
			{
				_entityInfos.setIsModified(false);
				_isModified = false;
			}

			bool		isPlay()
			{
				return _isPlay;
			}

			// Setters
			void				setPath(std::string & path)
			{
				this->_path = path;
				this->_isModified = true;
			}

			void				setType(SFX_TYPE & type)
			{
				this->_type = type;
				this->_isModified = true;
			}

			void				setIsPlay(const bool status)
			{
				this->_isPlay = true;
				this->_isModified = true;
			}

			void				setIsModified(const bool isModified)
			{
				this->_isModified = isModified;
			}

			// Getters
			EntityInfos &		getEntityInfos()
			{
				return (this->_entityInfos);
			}

			std::string &		getPath()
			{
				return (this->_path);
			}

			SFX_TYPE &			getType()
			{
				return (this->_type);
			}

			// Getters const
			EntityInfos const &	getEntityInfosConst() const
			{
				return (this->_entityInfos);
			}

			std::string const &	getPathConst()
			{
				return (this->_path);
			}

			SFX_TYPE const &	getTypeConst()
			{
				return (this->_type);
			}
		};
	}
}

#endif // NEXUS_ENGINE__SFX_HPP_