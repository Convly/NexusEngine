#ifndef COMBOBOX_XML_HPP_
# define COMBOBOX_XML_HPP_

#include <iostream>
#include <unordered_map>

#include "Nexus/modules/environment/Environment.hpp"
#include "Nexus/modules/xml/rapidxml-1.13/rapidxml.hpp"

#include "Nexus/modules/xml/Gui/GuiElement.hpp"

using namespace rapidxml;

namespace nx{
namespace xml{
    
    class ComboBox{
    public:
        static void init(std::unordered_map<std::string, std::function<std::string(env::Environment&, env::GUIComboBoxInfos&, const std::string& tag, const std::string& value)>>& autorizedAtt){
            autorizedAtt = std::unordered_map<std::string, std::function<std::string(env::Environment&, env::GUIComboBoxInfos&, const std::string& tag, const std::string& value)>>({
                {"backgroundColor", &fillBackgroundColor},
                {"borderColor", &fillBorderColor},
                {"borderThickness", &fillBorderThickness},
                {"fontPath", &fillFontPath},
                {"fontSize", &fillFontSize},
                {"textColor", &fillTextColor}
            });
        }

        static std::string fillComboBox(env::Environment& env, env::Layer& layer, xml_node<>* rootNode){
            std::string error = "";
            std::unordered_map<std::string, std::string> attributes;

            if ((error += Util::getAttributes(rootNode->name(), rootNode, attributes)).empty()){
                env::gui::ComboBox comboBox;

                error += GuiElement::fillGuiElementInfos(env, comboBox.getGuiElementInfos(), attributes, false);
                error += fillComboBoxInfo(env, comboBox.getGuiComboBoxInfos(), attributes);
                layer.addComboBox(comboBox);
            }
            return error;
        }

        static std::string fillComboBoxInfo(env::Environment& env, env::GUIComboBoxInfos& guiComboBoxInfos, std::unordered_map<std::string, std::string>& attributes){
            std::string error = "";
            std::unordered_map<std::string, std::function<std::string(env::Environment&, env::GUIComboBoxInfos&, const std::string& tag, const std::string& value)>> autorizedAtt;

            init(autorizedAtt);
            for (auto attribute : attributes){
                if (autorizedAtt.find(attribute.first) != autorizedAtt.end())
                    autorizedAtt.at(attribute.first)(env, guiComboBoxInfos, attribute.first, attribute.second);
                else
                    error += "Error: This attribute \"" + attribute.first + "\" doesn't exist in a ComboBox.\n";
            }
            return error;
        }

        static std::string fillBackgroundColor(env::Environment& env, env::GUIComboBoxInfos& guiComboBoxInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiComboBoxInfos.getColorInfo().setBackgroundColor(Integrity::color(value, error));
            return error; 
        }

        static std::string fillBorderColor(env::Environment& env, env::GUIComboBoxInfos& guiComboBoxInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiComboBoxInfos.getColorInfo().setBorderColor(Integrity::color(value, error));
            return error; 
        }

        static std::string fillBorderThickness(env::Environment& env, env::GUIComboBoxInfos& guiComboBoxInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiComboBoxInfos.getColorInfo().setBorderThickness(Integrity::intValue(value, error));
            return error; 
        }
        
        static std::string fillFontPath(env::Environment& env, env::GUIComboBoxInfos& guiComboBoxInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiComboBoxInfos.getTextInfo().setFontPath(Integrity::path(env, value, error));
            return error; 
        }

        static std::string fillFontSize(env::Environment& env, env::GUIComboBoxInfos& guiComboBoxInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiComboBoxInfos.getTextInfo().setFontSize(Integrity::intValue(value, error));
            return error; 
        }

        static std::string fillTextColor(env::Environment& env, env::GUIComboBoxInfos& guiComboBoxInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiComboBoxInfos.getTextInfo().setTextColor(Integrity::color(value, error));
            return error; 
        }
    };

}
}

#endif