#ifndef TEST_FRAMEWORK_TEMPLATE_HPP_
# define TEST_FRAMEWORK_TEMPLATE_HPP_

#include <iostream>

namespace nx {
	class TestFrameworkTpl
	{
	protected:
		const std::string 		_name;

	public:
		// This method must be implemented this way
		TestFrameworkTpl(const std::string & name) : _name(name) {};
		// This method must be implemented this way
		virtual ~TestFrameworkTpl() {};
		// This method must be implemented this way
		const std::string& getName(void) const {return this->_name;}

		// Framework Methods (must be virtual pure)
		virtual void TriggerTestEvent() = 0;

	};	
}

#endif /* TEST_FRAMEWORK_TEMPLATE_HPP_*/