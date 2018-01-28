#ifndef BUTTON_XML_HPP_
# define BUTTON_XML_HPP_

#include <iostream>
#include <unordered_map>

#include "Nexus/modules/environment/Environment.hpp"
#include "Nexus/modules/xml/rapidxml-1.13/rapidxml.hpp"

#include "Nexus/modules/xml/Gui/GuiElement.hpp"

using namespace rapidxml;

namespace nx{
namespace xml{
    
    class Button{
    public:
        static void init(std::unordered_map<std::string, std::function<std::string(env::Environment&, const GameInfosParser& gameInfosParser, env::GUIButtonInfos&, const std::string& tag, const std::string& value)>>& autorizedAtt){
            autorizedAtt = std::unordered_map<std::string, std::function<std::string(env::Environment&, const GameInfosParser& gameInfosParser, env::GUIButtonInfos&, const std::string& tag, const std::string& value)>>({
                {"isPushButton", &fillIsPushButton},
                {"backgroundColor", &fillBackgroundColor},
                {"borderColor", &fillBorderColor},
                {"borderThickness", &fillBorderThickness},
                {"fontPath", &fillFontPath},
                {"text", &fillText},
                {"fontSize", &fillFontSize},
                {"textColor", &fillTextColor}
            });
        }

        static std::string fillButton(env::Environment& env, const GameInfosParser& gameInfosParser, env::Layer& layer, xml_node<>* rootNode){
            std::string error = "";
            std::unordered_map<std::string, std::string> attributes;

            if ((error += Util::getAttributes(rootNode->name(), rootNode, attributes)).empty()){
                env::gui::Button button;

                error += GuiElement::fillGuiElementInfos(env, gameInfosParser, button.getGuiElementInfos(), attributes, false);
                error += fillButtonInfo(env, gameInfosParser, button.getGuiButtonInfos(), attributes);
                layer.addButton(button);
            }
            return error;
        }

        static std::string fillButtonInfo(env::Environment& env, const GameInfosParser& gameInfosParser, env::GUIButtonInfos& guiButtonInfos, std::unordered_map<std::string, std::string>& attributes){
            std::string error = "";
            std::unordered_map<std::string, std::function<std::string(env::Environment&, const GameInfosParser& gameInfosParser, env::GUIButtonInfos&, const std::string& tag, const std::string& value)>> autorizedAtt;

            init(autorizedAtt);
            for (auto attribute : attributes){
                if (autorizedAtt.find(attribute.first) != autorizedAtt.end())
                    autorizedAtt.at(attribute.first)(env, gameInfosParser, guiButtonInfos, attribute.first, attribute.second);
                else
                    error += "Error: This attribute \"" + attribute.first + "\" doesn't exist in a button.\n";
            }
            return error;
        }

        static std::string fillIsPushButton(env::Environment& env, const GameInfosParser& gameInfosParser, env::GUIButtonInfos& guiButtonInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiButtonInfos.setIsPushButton(Integrity::boolValue(value, error));
            return error; 
        }

        static std::string fillBackgroundColor(env::Environment& env, const GameInfosParser& gameInfosParser, env::GUIButtonInfos& guiButtonInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiButtonInfos.getColorInfo().setBackgroundColor(Integrity::color(value, error));
            return error; 
        }

        static std::string fillBorderColor(env::Environment& env, const GameInfosParser& gameInfosParser, env::GUIButtonInfos& guiButtonInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiButtonInfos.getColorInfo().setBorderColor(Integrity::color(value, error));
            return error; 
        }

        static std::string fillBorderThickness(env::Environment& env, const GameInfosParser& gameInfosParser, env::GUIButtonInfos& guiButtonInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiButtonInfos.getColorInfo().setBorderThickness(Integrity::intValue(value, error));
            return error; 
        }
        
        static std::string fillFontPath(env::Environment& env, const GameInfosParser& gameInfosParser, env::GUIButtonInfos& guiButtonInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiButtonInfos.getTextInfo().setFontPath(Integrity::path(env, gameInfosParser.getFields()._resources.at("images"), value, error));
            return error;
        }

        static std::string fillText(env::Environment& env, const GameInfosParser& gameInfosParser, env::GUIButtonInfos& guiButtonInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiButtonInfos.getTextInfo().setTextLabel(value);
            return error; 
        }

        static std::string fillFontSize(env::Environment& env, const GameInfosParser& gameInfosParser, env::GUIButtonInfos& guiButtonInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiButtonInfos.getTextInfo().setFontSize(Integrity::intValue(value, error));
            return error; 
        }

        static std::string fillTextColor(env::Environment& env, const GameInfosParser& gameInfosParser, env::GUIButtonInfos& guiButtonInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiButtonInfos.getTextInfo().setTextColor(Integrity::color(value, error));
            return error; 
        }
    };

}
}

#endif