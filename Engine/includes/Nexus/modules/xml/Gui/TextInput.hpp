#ifndef TEXTINPUT_XML_HPP_
# define TEXTINPUT_XML_HPP_

#include <iostream>
#include <unordered_map>

#include "Nexus/modules/environment/Environment.hpp"
#include "Nexus/modules/xml/rapidxml-1.13/rapidxml.hpp"

#include "Nexus/modules/xml/Gui/GuiElement.hpp"

using namespace rapidxml;

namespace nx{
namespace xml{
    
    class TextInput{
    public:
        static void init(std::unordered_map<std::string, std::function<std::string(env::Environment&, env::GUITextInputInfos&, const std::string& tag, const std::string& value)>>& autorizedAtt){
            autorizedAtt = std::unordered_map<std::string, std::function<std::string(env::Environment&, env::GUITextInputInfos&, const std::string& tag, const std::string& value)>>({
                {"backgroundColor", &fillBackgroundColor},
                {"borderColor", &fillBorderColor},
                {"borderThickness", &fillBorderThickness},
                {"fontPath", &fillFontPath},
                {"text", &fillText},
                {"fontSize", &fillFontSize},
                {"textColor", &fillTextColor}
            });
        }

        static std::string fillTextInput(env::Environment& env, env::Layer& layer, xml_node<>* rootNode){
            std::string error = "";
            std::unordered_map<std::string, std::string> attributes;

            if ((error += Util::getAttributes(rootNode->name(), rootNode, attributes)).empty()){
                env::gui::TextInput textInput;

                error += GuiElement::fillGuiElementInfos(env, textInput.getGuiElementInfos(), attributes, false);
                error += fillTextInputInfo(env, textInput.getGuiTextInputInfos(), attributes);
                layer.addTextInput(textInput);
            }
            return error;
        }

        static std::string fillTextInputInfo(env::Environment& env, env::GUITextInputInfos& guiTextInputInfos, std::unordered_map<std::string, std::string>& attributes){
            std::string error = "";
            std::unordered_map<std::string, std::function<std::string(env::Environment&, env::GUITextInputInfos&, const std::string& tag, const std::string& value)>> autorizedAtt;

            init(autorizedAtt);
            for (auto attribute : attributes){
                if (autorizedAtt.find(attribute.first) != autorizedAtt.end())
                    autorizedAtt.at(attribute.first)(env, guiTextInputInfos, attribute.first, attribute.second);
                else
                    error += "Error: This attribute \"" + attribute.first + "\" doesn't exist in a textInput.\n";
            }
            return error;
        }

        static std::string fillBackgroundColor(env::Environment& env, env::GUITextInputInfos& guiTextInputInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiTextInputInfos.getColorInfo().setBackgroundColor(Integrity::color(value, error));
            return error; 
        }

        static std::string fillBorderColor(env::Environment& env, env::GUITextInputInfos& guiTextInputInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiTextInputInfos.getColorInfo().setBorderColor(Integrity::color(value, error));
            return error; 
        }

        static std::string fillBorderThickness(env::Environment& env, env::GUITextInputInfos& guiTextInputInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiTextInputInfos.getColorInfo().setBorderThickness(Integrity::intValue(value, error));
            return error; 
        }
        
        static std::string fillFontPath(env::Environment& env, env::GUITextInputInfos& guiTextInputInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiTextInputInfos.getTextInfo().setFontPath(Integrity::path(env, value, error));
            return error; 
        }

        static std::string fillText(env::Environment& env, env::GUITextInputInfos& guiTextInputInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiTextInputInfos.getTextInfo().setTextLabel(value);
            return error; 
        }

        static std::string fillFontSize(env::Environment& env, env::GUITextInputInfos& guiTextInputInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiTextInputInfos.getTextInfo().setFontSize(Integrity::intValue(value, error));
            return error; 
        }

        static std::string fillTextColor(env::Environment& env, env::GUITextInputInfos& guiTextInputInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiTextInputInfos.getTextInfo().setTextColor(Integrity::color(value, error));
            return error; 
        }
    };

}
}

#endif