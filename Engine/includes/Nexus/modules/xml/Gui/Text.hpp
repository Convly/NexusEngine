#ifndef TEXT_XML_HPP_
# define TEXT_XML_HPP_

#include <iostream>
#include <unordered_map>

#include "Nexus/modules/environment/Environment.hpp"
#include "Nexus/modules/xml/rapidxml-1.13/rapidxml.hpp"

#include "Nexus/modules/xml/Gui/GuiElement.hpp"

using namespace rapidxml;

namespace nx{
namespace xml{
    
    class Text{
    public:
        static void init(std::unordered_map<std::string, std::function<std::string(env::Environment&, const GameInfosParser& gameInfosParser, env::GUITextInfos&, const std::string& tag, const std::string& value)>>& autorizedAtt){
            autorizedAtt = std::unordered_map<std::string, std::function<std::string(env::Environment&, const GameInfosParser& gameInfosParser, env::GUITextInfos&, const std::string& tag, const std::string& value)>>({
                {"fontPath", &fillFontPath},
                {"text", &fillText},
                {"fontSize", &fillFontSize},
                {"textColor", &fillTextColor}
            });
        }

        static std::string fillTextBox(env::Environment& env, const GameInfosParser& gameInfosParser, env::Layer& layer, xml_node<>* rootNode){
            std::string error = "";
            std::unordered_map<std::string, std::string> attributes;

            if ((error += Util::getAttributes(rootNode->name(), rootNode, attributes)).empty()){
                env::gui::Text text;

                error += GuiElement::fillGuiElementInfos(env, gameInfosParser, text.getGuiElementInfos(), attributes, true);
                error += fillTextInfo(env, gameInfosParser, text.getGuiTextInfos(), attributes);
                layer.addText(text);
            }
            return error;
        }

        static std::string fillTextInfo(env::Environment& env, const GameInfosParser& gameInfosParser, env::GUITextInfos& guiTextInfos, std::unordered_map<std::string, std::string>& attributes){
            std::string error = "";
            std::unordered_map<std::string, std::function<std::string(env::Environment&, const GameInfosParser& gameInfosParser, env::GUITextInfos&, const std::string& tag, const std::string& value)>> autorizedAtt;

            init(autorizedAtt);
            for (auto attribute : attributes){
                if (autorizedAtt.find(attribute.first) != autorizedAtt.end())
                    autorizedAtt.at(attribute.first)(env, gameInfosParser, guiTextInfos, attribute.first, attribute.second);
                else
                    error += "Error: This attribute \"" + attribute.first + "\" doesn't exist in a text.\n";
            }
            return error;
        }
        
        static std::string fillFontPath(env::Environment& env, const GameInfosParser& gameInfosParser, env::GUITextInfos& guiTextInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiTextInfos.getTextInfo().setFontPath(Integrity::path(env, gameInfosParser.getFields()._resources.at("images"), value, error));
            return error; 
        }

        static std::string fillText(env::Environment& env, const GameInfosParser& gameInfosParser, env::GUITextInfos& guiTextInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiTextInfos.getTextInfo().setTextLabel(value);
            return error; 
        }

        static std::string fillFontSize(env::Environment& env, const GameInfosParser& gameInfosParser, env::GUITextInfos& guiTextInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiTextInfos.getTextInfo().setFontSize(Integrity::intValue(value, error));
            return error; 
        }

        static std::string fillTextColor(env::Environment& env, const GameInfosParser& gameInfosParser, env::GUITextInfos& guiTextInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiTextInfos.getTextInfo().setTextColor(Integrity::color(value, error));
            return error; 
        }
    };

}
}

#endif