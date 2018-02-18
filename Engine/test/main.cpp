#include "Nexus/engine.hpp"
#include "Nexus/log.hpp"

 #include <X11/Xlib.h>  

void userMainLoop() {
}


int main(int ac, char** av)
{
	XInitThreads();
	if (ac != 2)
		return -1;

	auto& engine = nx::Engine::Instance();

	engine.setup(av[1], false);
	engine.ping();
	try {
		return (engine.run(&userMainLoop));
	} catch (const nx::RunWithoutSetupException& e) {
		nx::Log::error(e.what(), "RUNTIME_ERROR", 1);
		return -1;
	}
}