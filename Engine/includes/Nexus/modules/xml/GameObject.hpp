#ifndef GAMEOBJECT_HPP_
# define GAMEOBJECT_HPP_

#include <iostream>
#include <unordered_map>

#include "Nexus/modules/environment/Environment.hpp"
#include "rapidxml-1.13/rapidxml.hpp"

using namespace rapidxml;

namespace nx{
namespace xml{

    class GameObject{
    public:
        static std::vector<env::GameObject> getGameObjects(env::Environment& env, xml_node<>* rootNode, std::string& error){
            std::vector<env::GameObject> gameObjects;
            std::unordered_map<std::string, std::string> attributes;

            for (xml_node<>* node = rootNode->first_node("GameObject"); node; node = node->next_sibling("GameObject")){
                if ((error += Util::getAttributes(node->name(), node, attributes)).empty())
                    gameObjects.push_back(GameObject::getGameObject(env, node, error, attributes));
            }
            return gameObjects;
        }

        static env::GameObject getGameObject(env::Environment& env, xml_node<>* rootNode, std::string& error, const std::unordered_map<std::string, std::string>& attributes){
            env::GameObject gameObject(attributes.at("name"));

            for (auto attribute : attributes){
                if (attribute.first == "name");
                else if (attribute.first == "active")
                    gameObject.getEntityInfos().setActive(Integrity::active(attributes.at("active"), error));
                else
                    error += "Error: This attribute can't be created in this GameObject tag \"" + attributes.at("name") + "\"\n";
            }
            // TO DO !!!!!!!!!!!!!!!!!!!!!
            gameObject.getScriptComponent() = Component::getScripts(env, rootNode, error).front();
            gameObject.getTransformComponent() = Component::getTransforms(rootNode, error).front();
            gameObject.getRendererComponent() = Component::getRenderers(env, rootNode, error).front();
            gameObject.getRigidBodyComponent() = Component::getRigidBodies(rootNode, error).front();
            /////////////////////////////
            for (xml_node<>* node = rootNode->first_node(); node; node = node->next_sibling()){
                if (node->name() != "Script" && node->name() != "Transform" && node->name() != "Renderer" && node->name() != "RigidBody")
                    error += "Error: In the GameObject \"" + attributes.at("name") + "\" the tag \"" + std::string(node->name()) + "\" doesn't exist\n";
            }
            return gameObject;
        }
    };

}
}

#endif