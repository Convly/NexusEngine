#ifndef NETWORKCLIENT_FRAMEWORK_TEMPLATE_HPP_
# define NETWORKCLIENT_FRAMEWORK_TEMPLATE_HPP_

#include <iostream>

namespace nx {
	class NetworkClientFrameworkTpl
	{
	protected:
		const std::string 		_name;

	public:
		// This method must be implemented this way
		NetworkClientFrameworkTpl(const std::string & name) : _name(name) {};
		// This method must be implemented this way
		virtual ~NetworkClientFrameworkTpl() {};
		// This method must be implemented this way
		const std::string& getName(void) const {return this->_name;}
	};	
}

#endif /* NETWORKCLIENT_FRAMEWORK_TEMPLATE_HPP_*/