#ifndef IMAGE_XML_HPP_
# define IMAGE_XML_HPP_

#include <iostream>
#include <unordered_map>

#include "Nexus/modules/environment/Environment.hpp"
#include "Nexus/modules/xml/rapidxml-1.13/rapidxml.hpp"

#include "Nexus/modules/xml/Gui/GuiElement.hpp"

using namespace rapidxml;

namespace nx{
namespace xml{
    
    class Image{
    public:
        static void init(std::unordered_map<std::string, std::function<std::string(env::Environment&, env::GUIImageInfos&, const std::string& tag, const std::string& value)>>& autorizedAtt){
            autorizedAtt = std::unordered_map<std::string, std::function<std::string(env::Environment&, env::GUIImageInfos&, const std::string& tag, const std::string& value)>>({
                {"path", &fillImagePath}
            });
        }

        static std::string fillImage(env::Environment& env, env::Layer& layer, xml_node<>* rootNode){
            std::string error = "";
            std::unordered_map<std::string, std::string> attributes;

            if ((error += Util::getAttributes(rootNode->name(), rootNode, attributes)).empty()){
                env::gui::Image image;

                error += GuiElement::fillGuiElementInfos(env, image.getGuiElementInfos(), attributes, false);
                error += fillImageInfo(env, image.getGuiImageInfos(), attributes);
                layer.addImage(image);
            }
            return error;
        }

        static std::string fillImageInfo(env::Environment& env, env::GUIImageInfos& guiImageInfos, std::unordered_map<std::string, std::string>& attributes){
            std::string error = "";
            std::unordered_map<std::string, std::function<std::string(env::Environment&, env::GUIImageInfos&, const std::string& tag, const std::string& value)>> autorizedAtt;

            init(autorizedAtt);
            for (auto attribute : attributes){
                if (autorizedAtt.find(attribute.first) != autorizedAtt.end())
                    autorizedAtt.at(attribute.first)(env, guiImageInfos, attribute.first, attribute.second);
                else
                    error += "Error: This attribute \"" + attribute.first + "\" doesn't exist in a image.\n";
            }
            return error;
        }

        static std::string fillImagePath(env::Environment& env, env::GUIImageInfos& guiImageInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiImageInfos = env::GUIImageInfos(Integrity::path(env, value, error));
            return error; 
        }
    };

}
}

#endif