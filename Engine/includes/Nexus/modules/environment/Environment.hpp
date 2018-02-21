#ifndef NEXUS_ENGINE__ENVIRONMENT_HPP_
#define NEXUS_ENGINE__ENVIRONMENT_HPP_

# include <vector>

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
			std::vector<Scene>				_scenes;
			Ressources						_ressources;
			GameInfos						_gameInfos;
			std::vector<nx::env::Keyboard>	_keyboards;

		public:
			template <typename Archive>
			void serialize(Archive& ar, unsigned int version)
			{
				ar & _scenes;
				ar & _ressources;
				ar & _gameInfos;
				ar & _keyboards;
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

			Scene &					getSceneByName(const std::string& name)
			{
				for (auto& scene : _scenes){
					if (scene.getEntityInfos().getName() == name)
						return scene;
				}
				return _scenes.back();
			}

			unsigned long			getScenesSize()
			{
				return _scenes.size();
			}

			Ressources &			getRessources()
			{
                return (this->_ressources);
			}

			GameInfos &				getGameInfos()
			{
				return (this->_gameInfos);
			}

			const int				getConnectedClientConst() const
			{
				return (static_cast<int>(this->_keyboards.size()));
			}

			int						getConnectedClient()
			{
				return (static_cast<int>(this->_keyboards.size()));
			}

			const std::vector<nx::env::Keyboard>& getKeyboardsConst() const
			{
				return (this->_keyboards);
			}

			std::vector<nx::env::Keyboard> getKeyboards()
			{
				return (this->_keyboards);
			}

			nx::env::Keyboard getKeyboardAt(int idx)
			{
				return _keyboards.at(idx);
			}

			void addKeyboard()
			{
				_keyboards.push_back(nx::env::Keyboard());	
			}

			void updateKeyboard(const int idx, const nx::env::Keyboard& board)
			{
				if (idx < 0 || idx >= _keyboards.size())
					return;

				_keyboards[idx] = board;
			}

		};
	}
}

#endif /* NEXUS_ENGINE__ENVIRONMENT_HPP_ */
