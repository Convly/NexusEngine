#ifndef NEXUS_ENGINE__SCENE_HPP_
#define NEXUS_ENGINE__SCENE_HPP_

# include "EntityInfos.hpp"
# include "./component/ScriptComponent.hpp"
# include "GameObject.hpp"
# include "EnvUtils.hpp"
# include "Layer.hpp"

namespace nx
{
	namespace env
	{
		class Scene
		{
		private:
			EntityInfos						_entityInfos;
			std::vector<ScriptComponent>	_scriptComponents;
			std::vector<GameObject>			_gameObjects;
			nx::env::RGBa					_backgroundColor;
			std::vector<Layer>				_layers;

		public:
			Scene(std::string const& _name) : _entityInfos(_name) {}
			Scene(std::string const& _name, bool const _active) : _entityInfos(_name, _active) {}
			~Scene() {}

			// Setters
			void addScriptComponent(std::string const& scriptName, std::string const& scriptPath)
			{
				this->_scriptComponents.push_back(ScriptComponent(scriptName, scriptPath));
			}

			void addGameObject(std::string const& gameObjectName)
			{
				this->_gameObjects.push_back(GameObject(gameObjectName));
			}

			void setBackgroundColor(nx::env::RGBa const& backgroundColor)
			{
				this->_backgroundColor = backgroundColor;
			}

			void addLayer(Layer const& layer)
			{
				this->_layers.push_back(layer);
			}

			
			// Getters
			EntityInfos &					getEntityInfos()
			{
				return (this->_entityInfos);
			}

			std::vector<ScriptComponent> &	getScriptComponents()
			{
				return (this->_scriptComponents);
			}

            ScriptComponent &               getScriptComponentAt(int idx)
            {
                return (this->_scriptComponents.at(idx));
            }

			std::vector<GameObject> &		getGameObjects()
			{
				return (this->_gameObjects);
			}

            GameObject &               getGameObjectAt(int idx)
            {
                return (this->_gameObjects.at(idx));
            }

			nx::env::RGBa &					getBackgroundColor()
			{
				return (this->_backgroundColor);
			}

			std::vector<Layer> &			getLayers()
			{
				return (this->_layers);
			}

            Layer &               getLayerAt(int idx)
            {
                return (this->_layers.at(idx));
            }
		};
	}
}

#endif /* NEXUS_ENGINE__SCENE_HPP_ */