#ifndef RENDERING_FRAMEWORK_TEMPLATE_HPP_
# define RENDERING_FRAMEWORK_TEMPLATE_HPP_

#include <iostream>

namespace nx {
	class RenderingFrameworkTpl
	{
	protected:
		const std::string 		_name;

	public:
		// This method must be implemented this way
		RenderingFrameworkTpl(const std::string & name) : _name(name) {};
		// This method must be implemented this way
		virtual ~RenderingFrameworkTpl() {};
		// This method must be implemented this way
		const std::string& getName(void) const {return this->_name;}

		// Framework Methods (must be virtual pure)
		virtual void CreateWindow(int x, int y, const std::string& windowTitle) = 0;

	};	
}

#endif /* RENDERING_FRAMEWORK_TEMPLATE_HPP_*/