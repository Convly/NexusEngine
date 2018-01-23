#ifndef NEXUS_ENGINE__SCRIPTCOMPONENT_HPP_
#define NEXUS_ENGINE__SCRIPTCOMPONENT_HPP_

# include "../EntityInfos.hpp"

namespace nx
{
	namespace env
	{
		class ScriptComponent
		{
			EntityInfos		_entityInfos;
			std::string		_scriptPath;

		public:
			ScriptComponent(std::string const& _name)
				: _entityInfos(_name) {}
			ScriptComponent(std::string const& _name, std::string const& scriptPath)
				: _entityInfos(_name), _scriptPath(scriptPath) {}
			~ScriptComponent() {}

			// Setters
			void		setScriptPath(std::string const& scriptPath)
			{
				this->_scriptPath = scriptPath;
			}


			// Getters
			std::string &	getScriptPath()
			{
				return (this->_scriptPath);
			}
		};
	}
}

#endif /* NEXUS_ENGINE__SCRIPTCOMPONENT_HPP_ */