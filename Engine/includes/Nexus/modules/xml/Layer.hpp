#ifndef LAYER_HPP_
# define LAYER_HPP_

#include <iostream>
#include <unordered_map>

#include "Nexus/modules/environment/Environment.hpp"
#include "rapidxml-1.13/rapidxml.hpp"

using namespace rapidxml;

namespace nx{
namespace xml{

    class Layer{
    public:
        static std::string fillEnvironment(env::Environment& env, xml_node<>* node, const std::unordered_map<std::string, std::string>& attributes) {
            std::string error = "";

            return error;
        }
    };

}
}

#endif