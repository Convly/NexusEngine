#ifndef GUIELEMENT_HPP_
# define GUIELEMENT_HPP_

#include <iostream>
#include <unordered_map>

#include "Nexus/modules/environment/Environment.hpp"
#include "Nexus/modules/xml/rapidxml-1.13/rapidxml.hpp"

using namespace rapidxml;

namespace nx{
namespace xml{

    class GuiElement{
    public:
        static void initEventsAttributes(std::vector<std::string>& eventsAttributes){
            eventsAttributes = {
                "onMoveInside",
                "onMoveOutside",
                "onLeftClickPressedInside",
                "onLeftClickReleasedInside",
                "onRightClickPressedInside",
                "onRightClickReleasedInside",
                "onLeftClickPressedOutside",
                "onLeftClickReleasedOutside",
                "onRightClickPressedOutside",
                "onRightClickReleasedOutside",
                "keyTextEntered",
                "keyPressed"
            };
        }

        static std::string fillGuiElementInfos(env::Environment& env, env::GUIElementInfos& guiElementInfos, std::unordered_map<std::string, std::string>& attributes, bool isTextGui){
            std::string error = "";
            std::vector<std::string> eventsAttributes;

            initEventsAttributes(eventsAttributes);
            for (auto it = attributes.begin(); it != attributes.end();){
                bool found = true;

                if (it->first == "name")
                    guiElementInfos.setIdentifier(it->second);
                else if (it->first == "active")
                    guiElementInfos.setActive(Integrity::boolValue(it->second, error));
                else if (it->first == "pos")
                    guiElementInfos.setPos(Integrity::pos(it->second, error));
                else if (it->first == "size" && !isTextGui)
                    guiElementInfos.setSize(Integrity::xyValues(it->second, error));
                else if (std::find(eventsAttributes.begin(), eventsAttributes.end(), it->first) != eventsAttributes.end())
                    Integrity::event(guiElementInfos.getEvents(), env, it->second, it->first, error);
                else
                    found = false;
                if (found){
                    attributes.erase(it);
                    it = attributes.begin();
                }
                else
                    it++;

            }
            return error;
        }

        static std::string comboBox(env::Environment& env, env::Layer& layer, xml_node<>* rootNode){
            std::string error = "";

            return error;
        }

        static std::string image(env::Environment& env, env::Layer& layer, xml_node<>* rootNode){
            std::string error = "";

            return error;
        }

        static std::string progressBar(env::Environment& env, env::Layer& layer, xml_node<>* rootNode){
            std::string error = "";

            return error;
        }

        static std::string sprite(env::Environment& env, env::Layer& layer, xml_node<>* rootNode){
            std::string error = "";

            return error;
        }

        static std::string text(env::Environment& env, env::Layer& layer, xml_node<>* rootNode){
            std::string error = "";

            return error;
        }

        static std::string textInput(env::Environment& env, env::Layer& layer, xml_node<>* rootNode){
            std::string error = "";

            return error;
        }
    };

}
}

#endif