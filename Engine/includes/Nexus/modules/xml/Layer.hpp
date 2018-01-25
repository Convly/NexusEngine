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
        static std::vector<env::Layer> getLayers(xml_node<>* rootNode, std::string& error){
            std::vector<env::Layer> layers;

            for (xml_node<>* node = rootNode->first_node("Layer"); node; node = node->next_sibling("Layer")){
                
            }
            return layers;
        }
    };

}
}

#endif