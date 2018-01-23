#ifndef NEXUS_ENGINE__GAMEOBJECT_HPP_
#define NEXUS_ENGINE__GAMEOBJECT_HPP_

# include "EntityInfos.hpp"
# include "./component/ScriptComponent.hpp"
# include "./component/TransformComponent.hpp"
# include "./component/RendererComponent.hpp"
# include "./component/RigidBodyComponent.hpp"

namespace nx
{
	namespace env
	{
		class GameObject
		{
			EntityInfos			_entityInfos;
			ScriptComponent		_scriptComponent;
			TransformComponent	_transformComponent;
			RendererComponent	_rendererComponent;
			RigidBodyComponent	_rigidBodyComponent;

		public:
			GameObject(std::string const& _name) : _entityInfos(_name), _scriptComponent(_name), _transformComponent(_name), _rendererComponent(_name), _rigidBodyComponent(_name) {}
			GameObject(std::string const& _name, bool const _active) : _entityInfos(_name, _active), _scriptComponent(_name), _transformComponent(_name), _rendererComponent(_name), _rigidBodyComponent(_name) {}
			~GameObject() {}

			// Setters
			void		setScriptComponent(ScriptComponent const& scriptComponent)
			{
				this->_scriptComponent = scriptComponent;
			}

			void		setTransformComponent(TransformComponent const& transformComponent)
			{
				this->_transformComponent = transformComponent;
			}

			void		setRendererComponent(RendererComponent const& rendererComponent)
			{
				this->_rendererComponent = rendererComponent;
			}

			void		setRigidBodyComponent(RigidBodyComponent const& rigidBodyComponent)
			{
				this->_rigidBodyComponent = rigidBodyComponent;
			}


			// Getters
			EntityInfos &			getEntityInfos()
			{
				return (this->_entityInfos);
			}

			ScriptComponent &		getScriptComponent()
			{
				return (this->_scriptComponent);
			}

			TransformComponent &	getTransformComponent()
			{
				return (this->_transformComponent);
			}

			RendererComponent &		getRendererComponent()
			{
				return (this->_rendererComponent);
			}

			RigidBodyComponent &	getRigidBodyComponent()
			{
				return (this->_rigidBodyComponent);
			}
		};
	}
}

#endif /* NEXUS_ENGINE__GAMEOBJECT_HPP_ */