#include "Nexus/engine.hpp"
#include "Nexus/log.hpp"
#include "Nexus/modules/physics/physics.hpp"

void userMainLoop() {

}

int main()
{
  //auto& engine = nx::Engine::Instance();
  nx::physics::Collider col1(nx::maths::Vector2f(20, 20), nx::maths::Vector2f(6, 6));
  nx::physics::Collider col2(nx::maths::Vector2f(25, 25), nx::maths::Vector2f(30, 30));

  nx::Log::inform("IsCollided: " + std::to_string(nx::physics::Collider::isCollided(col1, col2)));

  /*while (1)
  {
	  col2.setPosition(nx::maths::Vector2f(col2.getPosition().x - 1, col2.getPosition().y));
	  nx::Log::inform("Col1 => Pos.X: " + std::to_string(col1.getPosition().x) + " | Pos.Y: " + std::to_string(col1.getPosition().y));
	  nx::Log::inform("Col1 => Size.X: " + std::to_string(col1.getSize().x) + " | Size.Y: " + std::to_string(col1.getSize().y));
	  nx::Log::inform("Col2 => Pos.X: " + std::to_string(col2.getPosition().x) + " | Pos.Y: " + std::to_string(col2.getPosition().y));
	  nx::Log::inform("Col2 => Size.X: " + std::to_string(col2.getSize().x) + " | Size.Y: " + std::to_string(col2.getSize().y));
	  if (nx::physics::Collider::isCollided(col1, col2))
		nx::Log::inform("IsCollided: " + std::to_string(nx::physics::Collider::isCollided(col1, col2)));
	  nx::Log::inform("");
  }*/
  /*engine.startup(true);
  engine.ping();
  engine.setup();

  try {
    return (engine.run(&userMainLoop));
  } catch (const nx::RunWithoutSetupException& e) {
    nx::Log::error(e.what(), "RUNTIME_ERROR", 1);
    return -1;
  }*/
	
}
