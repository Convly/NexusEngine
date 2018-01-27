#ifndef SCENE_HPP_
# define SCENE_HPP_

#include <iostream>
#include <unordered_map>

#include "rapidxml-1.13/rapidxml.hpp"
#include "Nexus/modules/environment/Environment.hpp"

#include "Nexus/modules/xml/Integrity.hpp"
#include "Nexus/modules/xml/Component.hpp"
#include "Nexus/modules/xml/GameObject.hpp"
#include "Nexus/modules/xml/Layer.hpp"

using namespace rapidxml;

namespace nx{
namespace xml{

    class Scene{
    public:
        static std::string fillEnvironment(env::Environment& env, xml_node<>* rootNode, const std::unordered_map<std::string, std::string>& attributes) {
            env::Scene scene(attributes.at("name"));
            std::string error = "";

            for (auto attribute : attributes){
                if (attribute.first == "name");
                else if (attribute.first == "active")
                    scene.getEntityInfos().setActive(Integrity::boolValue(attributes.at("active"), error));
                else if (attribute.first == "backgroundColor")
                    scene.setBackgroundColor(Integrity::color(attributes.at("backgroundColor"), error));
                else
                    error += "Error: This attribute can't be created in this Scene tag \"" + attributes.at("name") + "\"\n";
            }
            scene.getScriptComponents() = Component::getScripts(env, rootNode, error, false);
            scene.getGameObjects() = GameObject::getGameObjects(env, rootNode, error);
            scene.getLayers() = Layer::getLayers(env, rootNode, error);
            for (xml_node<>* node = rootNode->first_node(); node; node = node->next_sibling()){
                if (std::string(node->name()) != "Script" && std::string(node->name()) != "GameObject" && std::string(node->name()) != "Layer")
                    error += "Error: In the scene \"" + attributes.at("name") + "\" the tag \"" + std::string(node->name()) + "\" doesn't exist\n";
            }
            env.getScenes().push_back(scene);
            return error;
        }
    };

}
}

#endif