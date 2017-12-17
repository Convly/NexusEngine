#include "Framework${__NX_BASE_SYSTEM__}.hpp"

Framework${__NX_BASE_SYSTEM__}::Framework${__NX_BASE_SYSTEM__}(nx::Engine* engine)
:
	nx::${__NX_BASE_SYSTEM__}FrameworkTpl("Framework${__NX_BASE_SYSTEM__}"),
	_engine(engine)
{
	std::cout << "New ${__NX_BASE_SYSTEM__} Framework created" << std::endl;
}

Framework${__NX_BASE_SYSTEM__}::~Framework${__NX_BASE_SYSTEM__}()
{
	std::cout << "New ${__NX_BASE_SYSTEM__} Framework deleted" << std::endl;
}

void Framework${__NX_BASE_SYSTEM__}::Trigger${__NX_BASE_SYSTEM__}Event()
{
	this->_engine->emit("${__NX_BASE_SYSTEM__}EventKey", "${__NX_BASE_SYSTEM__}EventValue");
}