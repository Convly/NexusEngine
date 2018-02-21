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
			template <typename Archive>
			void serialize(Archive& ar, unsigned int version)
			{
				ar & _entityInfos;
				ar & _scriptComponents;
				ar & _gameObjects;
				ar & _backgroundColor;
				ar & _layers;
			}

		public:
			Scene() {}
			Scene(std::string const& _name) : _entityInfos(_name) {}
			Scene(std::string const& _name, bool const _active) : _entityInfos(_name, _active) {}
			Scene(const nx::env::Scene& other)
			:
				_entityInfos(other.getEntityInfosConst()),
				_scriptComponents(other.getScriptComponentsConst()),
				_gameObjects(other.getGameObjectsConst()),
				_backgroundColor(other.getBackgroundColorConst()),
				_layers(other.getLayersConst())
			{}

			~Scene() {}

			bool isModified(){
				if (_entityInfos.getIsModified())
					return true;
				for (auto& scriptComponent : _scriptComponents)
					if (scriptComponent.isModified())
						return true;
				for (auto& gameObject : _gameObjects)
					if (gameObject.isModified())
						return true;
				for (auto& layer : _layers)
					if (layer.isModified())
						return true;
				return false;
			}

			void resetModified(){
				_entityInfos.setIsModified(false);
				for (auto& scriptComponent : _scriptComponents)
					scriptComponent.resetModified();
				for (auto& gameObject : _gameObjects)
					gameObject.resetModified();
				for (auto& layer : _layers)
					layer.resetModified();
			}

			// Setters
			void addScriptComponent(std::string const& scriptName, std::string const& scriptPath)
			{
				this->_scriptComponents.push_back(ScriptComponent(scriptName, scriptPath));
			}

			void addGameObject(std::string const& gameObjectName)
			{
				this->_gameObjects.push_back(GameObject(gameObjectName));
			}

			void addGameObjectCopy(GameObject const& gameObject)
			{
				this->_gameObjects.push_back(gameObject);
			}

			bool removeGameObject(std::string const& gameObjectId)
			{
				bool found = false;
				std::remove_if(this->_gameObjects.begin(), this->_gameObjects.end(),
					[&](nx::env::GameObject gameObject)
				{
					if (gameObject.getEntityInfos().getName() == gameObjectId)
						found = true;
					return (gameObject.getEntityInfos().getName() == gameObjectId);
				});
				return (found);
			}

			void setBackgroundColor(nx::env::RGBa const& backgroundColor)
			{
				this->_backgroundColor = backgroundColor;
			}

			void addLayer(Layer const& layer)
			{
				this->_layers.push_back(layer);
			}

			bool removeLayer(std::string const& layerId)
			{
				bool found = false;
				std::remove_if(this->_layers.begin(), this->_layers.end(),
							   [&](nx::env::Layer layer)
							   {
									if (layer.getEntityInfos().getName() == layerId)
										found = true;
									return (layer.getEntityInfos().getName() == layerId);
							   });
				return (found);
			}

			
			// Getters
			EntityInfos &					getEntityInfos()
			{
				return (this->_entityInfos);
			}

			const EntityInfos& getEntityInfosConst() const
			{
				return _entityInfos;
			}
 
			std::vector<ScriptComponent> &	getScriptComponents()
			{
				return (this->_scriptComponents);
			}

			const std::vector<ScriptComponent>& getScriptComponentsConst() const
			{
				return _scriptComponents;
			}

			ScriptComponent &					getScriptComponentByName(const std::string& name)
			{
				for (auto& script : _scriptComponents){
					if (script.getEntityInfos().getName() == name)
						return script;
				}
				return _scriptComponents.back();
			}

			unsigned long					getScriptComponentsSize()
			{
				return _scriptComponents.size();
			}

            ScriptComponent &               getScriptComponentAt(int idx)
            {
                return (this->_scriptComponents.at(idx));
            }

			std::vector<GameObject> &		getGameObjects()
			{
				return (this->_gameObjects);
			}

			const std::vector<GameObject>& getGameObjectsConst() const
			{
				return _gameObjects;
			}
			GameObject &					getGameObjectByName(const std::string& name)
			{
				for (auto& gameObject : _gameObjects){
					if (gameObject.getEntityInfos().getName() == name)
						return gameObject;
				}
				return _gameObjects.back();
			}

			unsigned long					getGameObjectsSize()
			{
				return _scriptComponents.size();
			}

            GameObject &               getGameObjectAt(int idx)
            {
                return (this->_gameObjects.at(idx));
            }

			nx::env::RGBa &					getBackgroundColor()
			{
				return (this->_backgroundColor);
			}

			const nx::env::RGBa& getBackgroundColorConst() const
			{
				return _backgroundColor;
			}

			std::vector<Layer> &			getLayers()
			{
				return (this->_layers);
			}

			const std::vector<Layer>& getLayersConst() const 
			{
				return _layers;
			}

			Layer &					getLayerByName(const std::string& name)
			{
				for (auto& layer : _layers){
					if (layer.getEntityInfos().getName() == name)
						return layer;
				}
				return _layers.back();
			}

			unsigned long					getLayersSize()
			{
				return _layers.size();
			}

            Layer &               getLayerAt(int idx)
            {
                return (this->_layers.at(idx));
            }
		};
	}
}

#endif /* NEXUS_ENGINE__SCENE_HPP_ */