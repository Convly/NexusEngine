#ifndef NEXUS_ENGINE__ENVIRONMENT_HPP_
#define NEXUS_ENGINE__ENVIRONMENT_HPP_

# include "Scene.hpp"
# include "Ressources.hpp"
# include "GameInfos.hpp"

namespace nx
{
	namespace env
	{
		struct Environment
		{
			std::vector<Scene>			_scenes;
			Ressources					_ressources;
			GameInfos					_gameInfos;

		public:
			Environment() {}
			~Environment() {}

			// Setters
			void addScene(std::string const& sceneName)
			{
                std::cout << _ressources.getImagePaths().size();
                std::cout << "adding scene" << std::endl;
				this->_scenes.push_back(Scene(sceneName));
			}


			// Getters
			std::vector<Scene> &	getScenes()
			{
				return (this->_scenes);
			}

			Ressources &			getRessources()
			{
                return (this->_ressources);
			}

			GameInfos &				getGameInfos()
			{
				return (this->_gameInfos);
			}
		};
	}
}

#endif /* NEXUS_ENGINE__ENVIRONMENT_HPP_ */