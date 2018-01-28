#include "Nexus/engine.hpp"
#include "Nexus/log.hpp"

void userMainLoop() {
}

int main(int ac, char** av)
{
	if (ac != 2)
		return -1;

	auto& engine = nx::Engine::Instance();

	engine.setup(av[1], true);
	engine.ping();
	try {
		return (engine.run(&userMainLoop));
	} catch (const nx::RunWithoutSetupException& e) {
		nx::Log::error(e.what(), "RUNTIME_ERROR", 1);
		return -1;
	}
}