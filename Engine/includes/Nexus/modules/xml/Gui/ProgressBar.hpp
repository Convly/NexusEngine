#ifndef PROGRESSBAR_XML_HPP_
# define PROGRESSBAR_XML_HPP_

#include <iostream>
#include <unordered_map>

#include "Nexus/modules/environment/Environment.hpp"
#include "Nexus/modules/xml/rapidxml-1.13/rapidxml.hpp"

#include "Nexus/modules/xml/Gui/GuiElement.hpp"

using namespace rapidxml;

namespace nx{
namespace xml{
    
    class ProgressBar{
    public:
        static void init(std::unordered_map<std::string, std::function<std::string(env::Environment&, env::GUIProgressBarInfos&, const std::string& tag, const std::string& value)>>& autorizedAtt){
            autorizedAtt = std::unordered_map<std::string, std::function<std::string(env::Environment&, env::GUIProgressBarInfos&, const std::string& tag, const std::string& value)>>({
                {"backgroundColor", &fillBackgroundColor},
                {"borderColor", &fillBorderColor},
                {"borderThickness", &fillBorderThickness},
                {"fontPath", &fillFontPath},
                {"fontSize", &fillFontSize},
            });
        }

        static std::string fillProgressBar(env::Environment& env, env::Layer& layer, xml_node<>* rootNode){
            std::string error = "";
            std::unordered_map<std::string, std::string> attributes;

            if ((error += Util::getAttributes(rootNode->name(), rootNode, attributes)).empty()){
                env::gui::ProgressBar progressBar;

                error += GuiElement::fillGuiElementInfos(env, progressBar.getGuiElementInfos(), attributes, false);
                error += fillProgressBarInfo(env, progressBar.getGuiProgressBarInfos(), attributes);
                layer.addProgressBar(progressBar);
            }
            return error;
        }

        static std::string fillProgressBarInfo(env::Environment& env, env::GUIProgressBarInfos& guiProgressBarInfos, std::unordered_map<std::string, std::string>& attributes){
            std::string error = "";
            std::unordered_map<std::string, std::function<std::string(env::Environment&, env::GUIProgressBarInfos&, const std::string& tag, const std::string& value)>> autorizedAtt;

            init(autorizedAtt);
            for (auto attribute : attributes){
                if (autorizedAtt.find(attribute.first) != autorizedAtt.end())
                    autorizedAtt.at(attribute.first)(env, guiProgressBarInfos, attribute.first, attribute.second);
                else
                    error += "Error: This attribute \"" + attribute.first + "\" doesn't exist in a progressBar.\n";
            }
            return error;
        }

        static std::string fillBackgroundColor(env::Environment& env, env::GUIProgressBarInfos& guiProgressBarInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiProgressBarInfos.colorInfo.setBackgroundColor(Integrity::color(value, error));
            return error; 
        }

        static std::string fillBorderColor(env::Environment& env, env::GUIProgressBarInfos& guiProgressBarInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiProgressBarInfos.colorInfo.setBorderColor(Integrity::color(value, error));
            return error; 
        }

        static std::string fillBorderThickness(env::Environment& env, env::GUIProgressBarInfos& guiProgressBarInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiProgressBarInfos.colorInfo.setBorderThickness(Integrity::intValue(value, error));
            return error; 
        }
        
        static std::string fillFontPath(env::Environment& env, env::GUIProgressBarInfos& guiProgressBarInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiProgressBarInfos.textInfo.setFontPath(Integrity::path(env, value, error));
            return error; 
        }

        static std::string fillFontSize(env::Environment& env, env::GUIProgressBarInfos& guiProgressBarInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiProgressBarInfos.textInfo.setFontPath(Integrity::path(env, value, error));
            return error; 
        }
    };

}
}

#endif