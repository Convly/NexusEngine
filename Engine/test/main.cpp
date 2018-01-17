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
  // nx::GameInfosParser resources("build/.nx-game-conf.json");
  // std::string res;
	// nx::Environment env = nx::Environment();

  // resources.dump();

	// if (!(res = nx::XmlParser::fillEnvironment(env, resources.getFields()._ressources)).empty()){
	// 	std::cerr << res;
	// }
  // std::cout << "--> " << env.getScenes()["MyScene"].getComponents().front().getSrc() << std::endl;
  // std::cout << "--> " << env.getLayers()["layer1"].getGuiElements()["monbouton1"].getEvents().front().second.func << std::endl;
  // return 0;
}
