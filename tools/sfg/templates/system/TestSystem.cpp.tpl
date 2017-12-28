#include "Nexus/${__NX_LOWER_SYSTEM__}.hpp"
#include "Nexus/engine.hpp"
#include "Nexus/frameworks/FrameworkManager.hpp"

nx::${__NX_BASE_SYSTEM__}System::${__NX_BASE_SYSTEM__}System()
:
	nx::SystemTpl(__NX_${__NX_UPPER_SYSTEM__}_KEY__),
	_framework_m(std::make_shared<nx::FrameworkManager<nx::${__NX_BASE_SYSTEM__}FrameworkTpl>>(__NX_${__NX_UPPER_SYSTEM__}_KEY__, true))
{

}

nx::${__NX_BASE_SYSTEM__}System::~${__NX_BASE_SYSTEM__}System() {

}

 nx::${__NX_BASE_SYSTEM__}FrameworkTpl* nx::${__NX_BASE_SYSTEM__}System::getFramework()
{
	return this->_framework_m->getFramework();
}

void nx::${__NX_BASE_SYSTEM__}System::init()
{

}

void nx::${__NX_BASE_SYSTEM__}System::update()
{
	auto f = this->getFramework();
	if (!f)
		nx::Log::print("Framework is nullptr");
	else
		f->ping${__NX_BASE_SYSTEM__}Framework();
	std::cout << "Update for " << this->getName() << std::endl;
}

bool nx::${__NX_BASE_SYSTEM__}System::checkIntegrity() const
{
	if (this->_framework_m->getFramework()) {
		return true;
	}
	return false;
}