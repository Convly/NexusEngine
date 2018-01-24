#ifndef XML_HPP_
# define XML_HPP_

#include <iostream>
#include <unordered_map>
#include <functional>

#include "rapidxml-1.13/rapidxml.hpp"
#include "Nexus/modules/environment/Environment.hpp"

#include "Nexus/modules/xml/Scene.hpp"
#include "Nexus/modules/xml/Component.hpp"
#include "Nexus/modules/xml/Layer.hpp"
#include "Nexus/modules/xml/GameObject.hpp"

namespace nx{
namespace xml{

    static std::unordered_map<std::string, std::function<std::string(env::Environment&, xml_node<>*, const std::unordered_map<std::string, std::string>&)>> _fctByTag = std::unordered_map<std::string, std::function<std::string(env::Environment&, xml_node<>*, const std::unordered_map<std::string, std::string>&)>>({
            {"Scene", &Scene::fillEnvironment},
            {"GameObject", &GameObject::fillEnvironment},
            {"Layer", &Layer::fillEnvironment},
            {"Script", &Component::fillEnvironment},
            {"Transform", &Component::fillEnvironment},
            {"Renderer", &Component::fillEnvironment},
            {"RigidBody", &Component::fillEnvironment},
            {"Button", &Layer::fillEnvironment},
            {"CheckBox", &Layer::fillEnvironment},
            {"ComboBox", &Layer::fillEnvironment},
            {"Image", &Layer::fillEnvironment},
            {"ProgressBar", &Layer::fillEnvironment},
            {"Sprite", &Layer::fillEnvironment},
            {"Text", &Layer::fillEnvironment},
            {"TextInput", &Layer::fillEnvironment}
        });

    class Util{
    public:
        static std::string getAttributes(const std::string& tagName, xml_node<>* rootNode, std::unordered_map<std::string, std::string>& attributes){
            std::string error = "";

            for (auto node = rootNode->first_attribute(); node; node = node->next_attribute()){
                std::string key = node->name();
                std::string value = node->value();
                if (attributes.find(key) == attributes.end())
                    attributes[key] = value;
                else{
                    if (attributes.find("name") != attributes.end())
                        error += "Error: this attribute \"" + key + "\" already exist in the " + tagName + " named \"" + attributes.at("name") + "\"\n";
                    else
                        error += "Error: A \"" + tagName + "\" tag doesn't have a name\n";
                }
            }
            return error;
        }
    };

    class Xml{
    public:
        static std::string fillEnvironment(env::Environment& env, xml_node<>* rootNode) {
            std::unordered_map<std::string, std::string> attributes;
            std::string error = "";
            const std::string test = "bob";

            for (xml_node<>* node = rootNode->first_node(); node; node = node->next_sibling()){
                if ((error = Util::getAttributes(node->name(), node, attributes)).empty())
                    error += _fctByTag[node->name()](env, node, attributes);
            }
            return error;
        }
    };
}
}

#endif