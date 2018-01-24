#ifndef COMPONENT_HPP_
# define COMPONENT_HPP_

#include <iostream>
#include <unordered_map>

#include "Nexus/modules/environment/Environment.hpp"
#include "rapidxml-1.13/rapidxml.hpp"

using namespace rapidxml;

namespace nx{
namespace xml{

    class Component{
    public:
        static std::string fillEnvironment(env::Environment& env, xml_node<>* rootNode, const std::unordered_map<std::string, std::string>& attributes) {
            std::string error = "";

            return error;
        }

        static std::vector<env::ScriptComponent> getScripts(xml_node<>* rootNode, std::string& error){
            std::vector<env::ScriptComponent> scriptsComponent;

            for (xml_node<>* node = rootNode->first_node(); node; node = node->next_sibling()){
                
            }
            return scriptsComponent;
        }
    };

}
}

#endif