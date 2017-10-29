#include "Nexus/engine.hpp"
#include "Nexus/log.hpp"

void userMainLoop() {
	std::cout << "User MainLoop called" << std::endl;
}

int main()
{
  nx::Engine engine(true);

  engine.ping();
  engine.setup();

  try {
    return (engine.run(&userMainLoop));
  } catch (const nx::RunWithoutSetupException& e) {
    nx::Log::error(e.what(), "RUNTIME_ERROR", 1);
    return -1;
  }
}
