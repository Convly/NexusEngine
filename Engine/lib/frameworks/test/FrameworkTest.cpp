//
// Made by Marco
//

#include "FrameworkTest.hpp"

FrameworkTest::FrameworkTest(nx::Engine* engine)
:
	nx::TestFrameworkTpl("FrameworkTest"),
	_engine(engine)
{
	std::cout << "New UI Framework created" << std::endl;
}

FrameworkTest::~FrameworkTest()
{
	std::cout << "New UI Framework deleted" << std::endl;
}

void FrameworkTest::TriggerTestEvent()
{
	this->_engine->emit("TestEventKey", "TestEventValue");
}