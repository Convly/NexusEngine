#ifndef ${__NX_UPPER_SYSTEM__}_FRAMEWORK_TEMPLATE_HPP_
# define ${__NX_UPPER_SYSTEM__}_FRAMEWORK_TEMPLATE_HPP_

#include <iostream>

namespace nx {
	class ${__NX_BASE_SYSTEM__}FrameworkTpl
	{
	protected:
		const std::string 		_name;

	public:
		// This method must be implemented this way
		${__NX_BASE_SYSTEM__}FrameworkTpl(const std::string & name) : _name(name) {};
		// This method must be implemented this way
		virtual ~${__NX_BASE_SYSTEM__}FrameworkTpl() {};
		// This method must be implemented this way
		const std::string& getName(void) const {return this->_name;}

		// Framework Methods (must be virtual pure)
		virtual void Trigger${__NX_BASE_SYSTEM__}Event() = 0;

	};	
}

#endif /* ${__NX_UPPER_SYSTEM__}_FRAMEWORK_TEMPLATE_HPP_*/