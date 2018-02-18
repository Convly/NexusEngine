#ifndef NEXUS_ENGINE__SCENE_HPP_
#define NEXUS_ENGINE__SCENE_HPP_

# include "./component/ScriptComponent.hpp"
# include "EntityInfos.hpp"
# include "GameObject.hpp"
# include "EnvUtils.hpp"
# include "Layer.hpp"
# include "Sfx.hpp"

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
			std::vector<Sfx>				_sfx;

		public:
			template <typename Archive>
			void serialize(Archive& ar, unsigned int version)
			{
				ar & _entityInfos;
				ar & _scriptComponents;
				ar & _gameObjects;
				ar & _backgroundColor;
				ar & _layers;
				ar & _sfx;
			}

		public:
			Scene() {}
			Scene(std::string const& _name) : _entityInfos(_name) {}
			Scene(std::string const& _name, bool const _active) : _entityInfos(_name, _active) {}

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
				for (auto& sfx : _sfx)
					if (sfx.isModified())
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
				for (auto& sfx : _sfx)
					sfx.resetModified();
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

			void setBackgroundColor(nx::env::RGBa const& backgroundColor)
			{
				this->_backgroundColor = backgroundColor;
			}

			void addLayer(Layer const& layer)
			{
				this->_layers.push_back(layer);
			}

			void addSfx(Sfx const & sfx)
			{
				this->_sfx.push_back(sfx);
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

			std::vector<Sfx> &				getSfx()
			{
				return (this->_sfx);
			}

			Sfx &							getSfxAt(int idx)
			{
				return (this->_sfx.at(idx));
			}
		};
	}
}

#endif /* NEXUS_ENGINE__SCENE_HPP_ */
