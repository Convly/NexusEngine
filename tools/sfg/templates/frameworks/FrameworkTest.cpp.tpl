#include "Framework${__NX_BASE_SYSTEM__}.hpp"

Framework${__NX_BASE_SYSTEM__}::Framework${__NX_BASE_SYSTEM__}(nx::Engine* engine)
:
	nx::${__NX_BASE_SYSTEM__}FrameworkTpl("Framework${__NX_BASE_SYSTEM__}"),
	_engine(engine)
{
	nx::Log::inform("New ${__NX_BASE_SYSTEM__} Framework created");
}

Framework${__NX_BASE_SYSTEM__}::~Framework${__NX_BASE_SYSTEM__}()
{
	nx::Log::inform("New ${__NX_BASE_SYSTEM__} Framework deleted");
}

void Framework${__NX_BASE_SYSTEM__}::Trigger${__NX_BASE_SYSTEM__}Event()
{
	this->_engine->emit("${__NX_BASE_SYSTEM__}EventKey", {'4', '2'});
}