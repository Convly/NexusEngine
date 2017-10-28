#include "Nexus/engine.hpp"
#include "Nexus/log.hpp"

void lol() {
	std::cout << "Daboudi dabouda" << std::endl;
}

int main()
{
  nx::Engine engine(true);

  engine.ping();
  engine.setup();

  try {
    return (engine.run(&lol));
  } catch (const nx::RunWithoutSetupException& e) {
    nx::Log::error(e.what(), "RUNTIME_ERROR", 1);
    return -1;
  }
}
