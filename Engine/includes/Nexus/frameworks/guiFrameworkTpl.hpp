/**
*	@file guiFrameworkTpl.hpp
*	@author Marc-Antoine Leconte
*
*	This file contain the class template GuiFrameworkTpl.
*/

#ifndef GUI_FRAMEWORK_TEMPLATE_HPP_
# define GUI_FRAMEWORK_TEMPLATE_HPP_

#include <iostream>

/**
*	This class is the common part of all the frameworks of the GUI system in the engine.
*/

namespace nx {
	class GuiFrameworkTpl
	{
	protected:
		const std::string 		_name;

	public:
		GuiFrameworkTpl(const std::string & name);
		virtual ~GuiFrameworkTpl() {};

		virtual void displaySquare(int x, int y, int size) = 0;

		const std::string& getName(void) const;
	};	
}

#endif /* GUI_FRAMEWORK_TEMPLATE_HPP_*/