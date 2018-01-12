#ifndef SCRIPT_FRAMEWORK_TEMPLATE_HPP_
# define SCRIPT_FRAMEWORK_TEMPLATE_HPP_

#include <iostream>

namespace nx {
	namespace script {
		struct ScriptInfos {
			ScriptInfos(const std::string& file_, const std::string& func_)
			: file(file_), func(func_) {}

			ScriptInfos(const nx::script::ScriptInfos& other)
			: file(other.file), func(other.func) {}

			std::string file;
			std::string func;
		};
	};

	class ScriptFrameworkTpl
	{
	protected:
		const std::string 		_name;

	public:
		// This method must be implemented this way
		ScriptFrameworkTpl(const std::string & name) : _name(name) {};
		// This method must be implemented this way
		virtual ~ScriptFrameworkTpl() {};
		// This method must be implemented this way
		const std::string& getName(void) const {return this->_name;}

		// Framework Methods (must be virtual pure)
		virtual void runFile(const std::string& scriptPath) = 0;
		virtual void execFunction(const std::string& scriptPath, const std::string& funcName) = 0;
		virtual void loadFile(const std::string& scriptPath) = 0;
		virtual void update(const std::string& scriptPath) = 0;
		virtual void init(const std::string& scriptPath) = 0;

	};	
}

#endif /* SCRIPT_FRAMEWORK_TEMPLATE_HPP_*/