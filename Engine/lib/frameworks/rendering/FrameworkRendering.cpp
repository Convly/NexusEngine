#include "FrameworkRendering.hpp"

FrameworkRendering::FrameworkRendering(nx::Engine* engine)
:
	nx::RenderingFrameworkTpl("FrameworkRendering"),
	_engine(engine)
{
	std::cout << "New UI Framework created" << std::endl;
}

FrameworkRendering::~FrameworkRendering()
{
	std::cout << "New UI Framework deleted" << std::endl;
}

void FrameworkRendering::TriggerRenderingEvent()
{
	this->_engine->emit("RenderingEventKey", "RenderingEventValue");
}