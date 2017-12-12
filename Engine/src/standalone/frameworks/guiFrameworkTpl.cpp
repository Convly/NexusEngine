#include "Nexus/frameworks/guiFrameworkTpl.hpp"

nx::GuiFrameworkTpl::GuiFrameworkTpl(const std::string& name)
:
	_name(name)
{

}

const std::string& nx::GuiFrameworkTpl::getName() const
{
	return this->_name;
}