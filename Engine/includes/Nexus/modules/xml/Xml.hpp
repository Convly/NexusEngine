#ifndef XML_HPP_
# define XML_HPP_

#include <iostream>
#include <unordered_map>
#include <functional>

#include "rapidxml-1.13/rapidxml.hpp"
#include "Nexus/modules/environment/Environment.hpp"

#include "Nexus/modules/xml/Integrity.hpp"

#include "Nexus/modules/xml/Scene.hpp"
#include "Nexus/modules/xml/Component.hpp"
#include "Nexus/modules/xml/Layer.hpp"
#include "Nexus/modules/xml/GameObject.hpp"

namespace nx{
namespace xml{

    class Xml{
    public:
        static std::string fillEnvironment(env::Environment& env, xml_node<>* rootNode) {
            std::unordered_map<std::string, std::string> attributes;
            std::string error = "";

            for (xml_node<>* node = rootNode->first_node(); node; node = node->next_sibling()){
                if (std::string(node->name()) != "Scene")
                    error += "Error: You can't create a \"" + std::string(node->name()) + "\" outside of a Scene tag\n";
                else if ((error += Util::getAttributes(node->name(), node, attributes)).empty())
                    error += Scene::fillEnvironment(env, node, attributes);
                attributes.clear();
            }
            return error;
        }
    };
    
}
}

#endif