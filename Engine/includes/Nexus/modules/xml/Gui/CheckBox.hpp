#ifndef CHECKBOX_XML_HPP_
# define CHECKBOX_XML_HPP_

#include <iostream>
#include <unordered_map>

#include "Nexus/modules/environment/Environment.hpp"
#include "Nexus/modules/xml/rapidxml-1.13/rapidxml.hpp"

#include "Nexus/modules/xml/Gui/GuiElement.hpp"

using namespace rapidxml;

namespace nx{
namespace xml{
    
    class CheckBox{
    public:
        static void init(std::unordered_map<std::string, std::function<std::string(env::Environment&, env::GUICheckboxInfos&, const std::string& tag, const std::string& value)>>& autorizedAtt){
            autorizedAtt = std::unordered_map<std::string, std::function<std::string(env::Environment&, env::GUICheckboxInfos&, const std::string& tag, const std::string& value)>>({
                {"backgroundColor", &fillBackgroundColor},
                {"borderColor", &fillBorderColor},
                {"borderThickness", &fillBorderThickness},
            });
        }

        static std::string fillCheckBox(env::Environment& env, env::Layer& layer, xml_node<>* rootNode){
            std::string error = "";
            std::unordered_map<std::string, std::string> attributes;

            if ((error += Util::getAttributes(rootNode->name(), rootNode, attributes)).empty()){
                env::gui::Checkbox checkBox;

                error += GuiElement::fillGuiElementInfos(env, checkBox.getGuiElementInfos(), attributes, false);
                error += fillCheckBoxesInfo(env, checkBox.getGuiCheckBoxInfos(), attributes);
                layer.addCheckbox(checkBox);
            }
            return error;
        }

        static std::string fillCheckBoxesInfo(env::Environment& env, env::GUICheckboxInfos& guiCheckboxInfos, std::unordered_map<std::string, std::string>& attributes){
            std::string error = "";
            std::unordered_map<std::string, std::function<std::string(env::Environment&, env::GUICheckboxInfos&, const std::string& tag, const std::string& value)>> autorizedAtt;

            init(autorizedAtt);
            for (auto attribute : attributes){
                if (autorizedAtt.find(attribute.first) != autorizedAtt.end())
                    autorizedAtt.at(attribute.first)(env, guiCheckboxInfos, attribute.first, attribute.second);
                else
                    error += "Error: This attribute \"" + attribute.first + "\" doesn't exist in a button.\n";
            }
            return error;
        }

        static std::string fillBackgroundColor(env::Environment& env, env::GUICheckboxInfos& guiCheckboxInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiCheckboxInfos.getColorInfo().setBackgroundColor(Integrity::color(value, error));
            return error; 
        }

        static std::string fillBorderColor(env::Environment& env, env::GUICheckboxInfos& guiCheckboxInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiCheckboxInfos.getColorInfo().setBorderColor(Integrity::color(value, error));
            return error; 
        }

        static std::string fillBorderThickness(env::Environment& env, env::GUICheckboxInfos& guiCheckboxInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiCheckboxInfos.getColorInfo().setBorderThickness(Integrity::intValue(value, error));
            return error; 
        }
    };

}
}

#endif