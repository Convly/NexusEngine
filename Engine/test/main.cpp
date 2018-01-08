#include "Nexus/engine.hpp"
#include "Nexus/log.hpp"

void userMainLoop() {
}

int main()
{
  auto& engine = nx::Engine::Instance();

  engine.ping();
  engine.setup();

  try {
    return (engine.run(&userMainLoop));
  } catch (const nx::RunWithoutSetupException& e) {
    nx::Log::error(e.what(), "RUNTIME_ERROR", 1);
    return -1;
  }
}
