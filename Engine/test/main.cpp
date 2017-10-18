#include "Nexus/engine.hpp"

void lol() {
	std::cout << "Daboudi dabouda" << std::endl;
}

int main()
{
  nx::Engine engine(true);

  engine.ping();
  engine.setup();
  return (engine.run(&lol));
}
