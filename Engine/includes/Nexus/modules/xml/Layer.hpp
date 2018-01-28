#ifndef LAYER_HPP_
# define LAYER_HPP_

#include <iostream>
#include <functional>
#include <unordered_map>

#include "Nexus/modules/environment/Environment.hpp"
#include "Nexus/modules/xml/rapidxml-1.13/rapidxml.hpp"

#include "Nexus/modules/xml/Gui/GuiElement.hpp"
#include "Nexus/modules/xml/Gui/Button.hpp"
#include "Nexus/modules/xml/Gui/CheckBox.hpp"
#include "Nexus/modules/xml/Gui/ComboBox.hpp"
#include "Nexus/modules/xml/Gui/Image.hpp"
#include "Nexus/modules/xml/Gui/ProgressBar.hpp"
#include "Nexus/modules/xml/Gui/Sprite.hpp"
#include "Nexus/modules/xml/Gui/Text.hpp"
#include "Nexus/modules/xml/Gui/TextInput.hpp"

using namespace rapidxml;

namespace nx{
namespace xml{

    class Layer{
    public:
        static void initGuiElementTags(std::unordered_map<std::string, std::function<std::string(env::Environment&, env::Layer&, xml_node<>*)>>& guiElementTags){
            guiElementTags = std::unordered_map<std::string, std::function<std::string(env::Environment&, env::Layer&, xml_node<>*)>>({
                {"Button", &Button::fillButton},
                {"CheckBox", &CheckBox::fillCheckBox},
                {"ComboBox", &ComboBox::fillComboBox},
                {"Image", &Image::fillImage},
                {"ProgressBar", &ProgressBar::fillProgressBar},
                {"Sprite", &Sprite::fillSprite},
                {"Text", &Text::fillTextBox},
                {"TextInput", &TextInput::fillTextInput}
            });
        }

        static std::vector<env::Layer> getLayers(env::Environment& env, xml_node<>* rootNode, std::string& error){
            std::unordered_map<std::string, std::string> attributes;
            std::vector<env::Layer> layers;

            for (xml_node<>* node = rootNode->first_node(); node; node = node->next_sibling()){
                env::Layer layer;
                if ((error += Util::getAttributes(node->name(), node, attributes)).empty())
                    error += Layer::fillLayer(env, layer, node, attributes);
                layers.push_back(layer);
            }
            return layers;
        }

        static std::string fillLayer(env::Environment& env, env::Layer& layer, xml_node<>* rootNode, const std::unordered_map<std::string, std::string>& attributes){
            std::string error = "";
            std::unordered_map<std::string, std::function<std::string(env::Environment&, env::Layer&, xml_node<>*)>> guiElementTags;

            initGuiElementTags(guiElementTags);
            for (auto attribute : attributes){
                if (attribute.first == "name")
                    layer.getEntityInfos().setName(attributes.at("name"));
                else if (attribute.first == "active")
                    layer.getEntityInfos().setActive(Integrity::boolValue(attributes.at("active"), error));
                else
                    error += "Error: This attribute can't be created in this Layer tag \"" + attributes.at("name") + "\"\n";
            }
            for (xml_node<>* node = rootNode->first_node(); node; node = node->next_sibling()){
                if (guiElementTags.find(std::string(node->name())) != guiElementTags.end())
                    error += guiElementTags.at(std::string(node->name()))(env, layer, node);
                else
                    error += "Error: This tag can not be in a Layer \"" + std::string(node->name()) + "\"\n";
            }
            return error;
        }
    };

}
}

#endif