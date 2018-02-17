#ifndef NEXUS_ENGINE__ENVIRONMENT_HPP_
#define NEXUS_ENGINE__ENVIRONMENT_HPP_

# include "Scene.hpp"
# include "Ressources.hpp"
# include "GameInfos.hpp"
# include "Keyboard.hpp"

namespace nx
{
	namespace env
	{
		class Environment
		{
		private:
			std::vector<Scene>			_scenes;
			Ressources					_ressources;
			GameInfos					_gameInfos;

		public:
			template <typename Archive>
			void serialize(Archive& ar, unsigned int version)
			{
				ar & _scenes;
				ar & _ressources;
				ar & _gameInfos;
			}

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

            Scene &                 getSceneAt(int idx)
            {
                return (this->_scenes.at(idx));
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