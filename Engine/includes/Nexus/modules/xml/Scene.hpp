#ifndef SCENE_HPP_
# define SCENE_HPP_

#include <iostream>
#include <unordered_map>

#include "Nexus/modules/environment/Environment.hpp"
#include "Nexus/modules/xml/Integrity.hpp"
#include "rapidxml-1.13/rapidxml.hpp"

using namespace rapidxml;

namespace nx{
namespace xml{

    class Scene{
    public:
        static std::string fillEnvironment(env::Environment& env, xml_node<>* node, const std::unordered_map<std::string, std::string>& attributes) {
            env::Scene scene(attributes.at("name"));
            std::string error = "";

            //if (attributes.find("active") != attributes.end())
                //scene.getEntityInfos().setActive(Integrity::active(attributes.at("active"), error));
            if (attributes.find("backgroundColor") != attributes.end())
                scene.setBackgroundColor(Integrity::backgroundColor(attributes.at("backgroundColor"), error));
            //getComponents();
            return error;
        }
    };

}
}

#endif