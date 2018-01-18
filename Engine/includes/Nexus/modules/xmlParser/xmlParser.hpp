/*
** xmlParser.hpp for Test in /Users/metge_q/rendu/Test
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Mon Dec 18 13:38:52 2017 Quentin Metge
** Last update Mon Jan 08 15:51:44 2018 Quentin Metge
*/

#ifndef XML_PARSER_HPP_
# define XML_PARSER_HPP_

#include <cstdlib>
#include <sstream>

#include "rapidxml-1.13/rapidxml.hpp"
#include "Directory.hpp"
#include "Environment.hpp"
#include "Split.hpp"

using namespace rapidxml;

namespace nx
{
  class XmlParser
  {
  public:
    XmlParser(){}
    virtual ~XmlParser(){}

  public:
    static std::string mapTransformAttributes(Component& component, GameObject& gameObject, xml_node<>* componentNode){
      std::string error = "";
      
      // Position
      if (componentNode->first_node("pos")){
        if (componentNode->first_node("pos")->first_attribute("x") && componentNode->first_node("pos")->first_attribute("y")){
          component.getPos().x = std::stoi(componentNode->first_node("pos")->first_attribute("x")->value());
          component.getPos().y = std::stoi(componentNode->first_node("pos")->first_attribute("y")->value());
        }
        else{
          error += "Error: incorect position in the game object " + gameObject.getName() + "\n";
          return error;
        }
      }
      else{
        error += "Error: A transform component need a pos in the game object " + gameObject.getName() + "\n";
        return error;
      }
      // Rotation
      if (componentNode->first_node("rotation")){
        if (componentNode->first_node("rotation")->first_attribute("x") && componentNode->first_node("rotation")->first_attribute("y")){
          component.getRotation().x = std::stoi(componentNode->first_node("rotation")->first_attribute("x")->value());
          component.getRotation().y = std::stoi(componentNode->first_node("rotation")->first_attribute("y")->value());
        }
        else{
          error += "Error: incorect rotation in the game object " + gameObject.getName() + "\n";
          return error;
        }
      }
      else{
        error += "Error: A transform component need a rotation in the game object " + gameObject.getName() + "\n";
        return error;
      }
    }

    static std::string mapRendererAttributes(Component& component, GameObject& gameObject, xml_node<>* componentNode){
      std::string error = "";
      
      // Texture
      if (componentNode->first_node("texture")){
        if (componentNode->first_node("texture")->first_attribute("src"))
          component.getSrc() = componentNode->first_node("texture")->first_attribute("src")->value();
        else{
          error += "Error: incorect texture in the game object " + gameObject.getName() + "\n";
          return error;
        }
      }
      else{
        error += "Error: A renderer component need a texture in the game object " + gameObject.getName() + "\n";
        return error;
      }
      // Opacity
      if (componentNode->first_node("opacity")){
        if (componentNode->first_node("opacity")->first_attribute("value"))
          component.getOpacity() = std::atoi(componentNode->first_node("opacity")->first_attribute("value")->value());
        else{
          error += "Error: incorect opacity in the game object " + gameObject.getName() + "\n";
          return error;
        }
      }
      else{
        error += "Error: A renderer component need an opacity in the game object " + gameObject.getName() + "\n";
        return error;
      }
    }    

    static std::string mapComponentsGameObject(Environment& env, GameObject& gameObject, xml_node<>* componentNode){
      std::string error = "";
      Component component;

      if (componentNode->first_attribute("type"))
        component.getType() = componentNode->first_attribute("type")->value();
      else{
        error += "Error: " + gameObject.getName() + " doesn't have type\n";
        return error;
      }

      if (component.getType() == "transform")
        error += mapTransformAttributes(component, gameObject, componentNode);
      else if (component.getType() == "renderer")
        error += mapRendererAttributes(component, gameObject, componentNode);
      gameObject.getComponents().push_back(component);
    }

    // Parse and add a gameObject to env
    static std::string mapGameObject(Environment& env, xml_node<>* rootNode){
      std::string error = "";

      try{
        // Browse gameObjects
        for (xml_node<>* gameObjectNode = rootNode->first_node("gameObject"); gameObjectNode; gameObjectNode = gameObjectNode->next_sibling("gameObject")){
          GameObject gameObject;
          std::string gameObjectName;

          if (gameObjectNode->first_attribute("name")){
            gameObjectName = gameObjectNode->first_attribute("name")->value();
            gameObject.setName(gameObjectName);
          }
          else{
            error += "Error: A game object doesn't have name\n";
            break;
          }
          if (gameObjectNode->first_attribute("tag"))
            gameObject.getTag() = gameObjectNode->first_attribute("tag")->value();
          // Browse components
          for (auto componentNode = gameObjectNode->first_node("component"); componentNode; componentNode = componentNode->next_sibling("component"))
            error += mapComponentsGameObject(env, gameObject, componentNode);
          env.getGameObjects().push_back(gameObject);
        }
      }
      catch (std::exception e){
        error += "Error: Invalid game object argument";
      }
      return error;
    }

    template<typename T>
    static int nameExistInVec(const std::string& name, const std::vector<T>& vec){
      for (int i = 0; i < vec.size(); i++){
        if (vec.at(i).getName() == name)
          return i;
      }
      return -1;
    }

    static std::string mapLayoutAttribute(Environment& env, xml_node<>* attributeNode, Layout& layout){
      std::string error = "";

      if (std::string(attributeNode->name()).compare("component") == 0){
        Component component;

        if (attributeNode->first_attribute("type") && attributeNode->first_attribute("src")){
          component.getType() = attributeNode->first_attribute("type")->value();
          component.getSrc() = attributeNode->first_attribute("src")->value();
          layout.getComponents().push_back(component);
        }
        else
          error += "Error: Bad attrute for a component of " + layout.getName();
      }
      else if (std::string(attributeNode->name()).compare("gameObject") == 0){
        if (attributeNode->first_attribute("name")){                
          int i;
          if ((i = nameExistInVec(attributeNode->first_attribute("name")->value(), env.getGameObjects())) != -1)
            layout.getGameObjects().push_back(env.getGameObjects().at(i));
          else{                  
            error += "Error: this game object doesn't exist ";
            error += attributeNode->first_attribute("name")->value();
            error += "\n";
          }
        }
      }
      return error;
    }

    static std::string mapLayoutAttributes(Environment& env, xml_node<>* layoutNode){
      std::string error = "";
      Layout layout;
      std::string layoutName;

      if (layoutNode->first_attribute("name"))
        layout.setName(layoutNode->first_attribute("name")->value());
      else{
        error += "Error: A layout doesn't have name\n";
        return error;
      }
      for (auto attributeNode = layoutNode->first_node(); attributeNode; attributeNode = attributeNode->next_sibling())
        error += mapLayoutAttribute(env, attributeNode, layout);
      env.getLayouts().push_back(layout);
    }

    // Parse and add a layout to env
    static std::string mapLayout(Environment& env, xml_node<>* rootNode)
    {
      std::string error = "";

      try{
        // Browse gameObjects
        for (xml_node<>* layoutNode = rootNode->first_node("layout"); layoutNode; layoutNode = layoutNode->next_sibling("layout"))
          error += mapLayoutAttributes(env, layoutNode);
      }
      catch (std::exception e){
        error += "Error: Invalid layout argument";
      }
      return error;
    }

    static std::string mapGuiEvents(xml_node<>* attributeNode, GuiElement& guiElement){
      std::string error = "";
      std::vector<std::string> possibleFct = {
        "onMoveInside", "onMoveOutside",
        "onLeftClickPressedInside", "onLeftClickReleasedInside",
        "onRightClickPressedInside", "onRightClickReleasedInside",
        "onLeftClickPressedOutside", "onLeftClickReleasedOutside",
        "onRightClickPressedOutside", "onRightClickReleasedOutside"};

      for (auto it : possibleFct){
        if (attributeNode->first_attribute(it.c_str())){
          std::string value = attributeNode->first_attribute(it.c_str())->value();
          std::vector<std::string> splitedValue = split(value, ':');
          guiElement.getEvents().push_back({ it, script::ScriptInfos(splitedValue.at(0), splitedValue.at(1)) });
        }
      }
      return "";
    }

    static std::string mapGuiElementAttribute(xml_node<>* attributeNode, Layer& layer){
      std::string error = "";

      if (std::string(attributeNode->name()).compare("guiElement") == 0){
        GuiElement guiElement;

        if (attributeNode->first_attribute("name"))
          guiElement.getName() = attributeNode->first_attribute("name")->value();
        else{
          error += "Error: A guiElement in the layer" + layer.getName() + " doesn't have name\n";
          return error;
        }
        if (attributeNode->first_attribute("type"))
          guiElement.getType() = attributeNode->first_attribute("type")->value();
        else{
          error += "Error: The guiElement " + guiElement.getName() + " in " + layer.getName() + " doesn't have type\n";
          return error;
        }
        if (attributeNode->first_attribute("width"))
          guiElement.getWidth() = std::stoi(attributeNode->first_attribute("width")->value());
        if (attributeNode->first_attribute("height"))
          guiElement.getHeight() = std::stoi(attributeNode->first_attribute("height")->value());
        if (attributeNode->first_attribute("pos")){
          std::vector<std::string> splitedValue = split(attributeNode->first_attribute("pos")->value(), ';');
          if (splitedValue.size() < 2){
            error += "Error: Bad position\n";
            return error;
          }
          guiElement.getPos().x = std::stoi(splitedValue[0]); 
          guiElement.getPos().y = std::stoi(splitedValue[1]); 
        }
        if (attributeNode->first_attribute("background-color"))
          guiElement.getBackgroundColor() = attributeNode->first_attribute("background-color")->value();
        if (attributeNode->first_attribute("border-color"))
          guiElement.getBorderColor() = attributeNode->first_attribute("border-color")->value();
        if (attributeNode->first_attribute("press-button"))
          std::istringstream(attributeNode->first_attribute("press-button")->value()) >> std::boolalpha >> guiElement.getPressButton();
        if (attributeNode->first_attribute("text"))
          guiElement.getText() = attributeNode->first_attribute("text")->value();  
        if (attributeNode->first_attribute("text-color"))
          guiElement.getTextColor() = attributeNode->first_attribute("text-color")->value();                                                      
        error += mapGuiEvents(attributeNode, guiElement);
        layer.getGuiElements().push_back(guiElement);
      }
      return error;
    }

    // Parse and add a layer to env
    static std::string mapLayer(Environment& env, xml_node<>* rootNode)
    {
      std::string error = "";

      try{
        // Browse gameObjects
        for (xml_node<>* layerNode = rootNode->first_node("layer"); layerNode; layerNode = layerNode->next_sibling("layer")){
          Layer layer;

          if (layerNode->first_attribute("name"))
            layer.getName() = layerNode->first_attribute("name")->value();
          else{
            error += "Error: A layer doesn't have a name\n";
            break;
          }
          for (auto attributeNode = layerNode->first_node(); attributeNode; attributeNode = attributeNode->next_sibling()){
            error += mapGuiElementAttribute(attributeNode, layer);
          }
          env.getLayers().push_back(layer);
        }
      }
      catch (std::exception e){
        error += "Error: Invalid layer argument";
      }
      return error;
    }

    static std::string mapSceneComponents(Environment& env, xml_node<>* attributeNode, Scene& scene){
      std::string error = "";
      Component component;

      if (attributeNode->first_attribute("type") && attributeNode->first_attribute("src"))
      {
        component.getType() = attributeNode->first_attribute("type")->value();
        component.getSrc() = attributeNode->first_attribute("src")->value();
        scene.getComponents().push_back(component);
      }
      else
        error += "Error: Bad attribute for a component of " + scene.getName() + "\n";
      return error;
    }
    
    static std::string mapSceneGameObjects(Environment& env, xml_node<>* attributeNode, Scene& scene){
      std::string error = "";

      if (attributeNode->first_attribute("name"))
      {                
        int i;
        if ((i = nameExistInVec(attributeNode->first_attribute("name")->value(), env.getGameObjects())) != -1)
          scene.getGameObjects().push_back(env.getGameObjects().at(i));
        else
        {                  
          error += "Error: this game object doesn't exist ";
          error += attributeNode->first_attribute("name")->value();
          error += "\n";
        }
      }
      return error;
    }

      static std::string mapSceneLayouts(Environment& env, xml_node<>* attributeNode, Scene& scene){
        std::string error = "";

        if (attributeNode->first_attribute("name")){         
                  int i;
          if ((i = nameExistInVec(attributeNode->first_attribute("name")->value(), env.getLayouts())) != -1){
            for (auto value : env.getLayouts().at(i).getGameObjects())
              scene.getGameObjects().push_back(value);  
            for (auto value : env.getLayouts().at(i).getComponents())
              scene.getComponents().push_back(value);  
          }
          else{                  
            error += "Error: this layout doesn't exist ";
            error += attributeNode->first_attribute("name")->value();
            error += "\n";
          }
        }
      return error;
    }

    static std::string mapSceneAttributes(Environment& env, xml_node<>* attributeNode, Scene& scene){
      std::string error = "";

      if (std::string(attributeNode->name()).compare("component") == 0)
        error += mapSceneComponents(env, attributeNode, scene);
      else if (std::string(attributeNode->name()).compare("gameObject") == 0)
        error += mapSceneGameObjects(env, attributeNode, scene);
      else if (std::string(attributeNode->name()).compare("layout") == 0)
        error += mapSceneLayouts(env, attributeNode, scene);
      return error;
    }

    // Parse and add a scene to env
    static std::string mapScene(Environment& env, xml_node<>* rootNode)
    {
      std::string error = "";

      try
      {
        // Browse gameObjects
        for (xml_node<>* sceneNode = rootNode->first_node("scene"); sceneNode; sceneNode = sceneNode->next_sibling("scene"))
        {
          Scene scene;
          std::string sceneName;

          if (sceneNode->first_attribute("name"))
          {
            sceneName = sceneNode->first_attribute("name")->value();
            scene.getName() = sceneName;
          }
          else
          {
            error += "Error: A game object doesn't have name\n";
            break;
          }
          for (auto attributeNode = sceneNode->first_node(); attributeNode; attributeNode = attributeNode->next_sibling())
          {
            error += mapSceneAttributes(env, attributeNode, scene);
          }
          env.getScenes().push_back(scene);
        }
      }
      catch (std::exception e){
        error += "Error: Invalid scene argument";
      }
      return error;
    }

    // get the next xml tree of a list a directory
    static std::string getNextXmlTree(Environment& env, const std::string xmlType, const std::vector<std::string>& dirPaths){
      std::string error = "";
      xml_node<>* rootNode = nullptr;
      static std::vector<std::string> filesName;
      xml_document<> doc; 
      static int i = 0;

      while (i < dirPaths.size()){
        static int j = 0;

        if (j == 0 && !getComponentFilesName(dirPaths[i], filesName)){
          error += "Error: " + xmlType + " in get files name " + dirPaths[i] + "\n";
          i = 0;
          j = 0;
          return error;
        }
        while (j < filesName.size()){
          std::ifstream theFile(filesName[j++]);
          std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
          buffer.push_back('\0');
          doc.parse<0>(&buffer[0]);
          rootNode = doc.first_node("nx");
          if (rootNode == nullptr){
            error += "Error: nx tag not found in " + filesName[j - 1] + "\n";
            std::cerr << "Error: nx tag not found in " << filesName[j - 1] << std::endl;
          }
          else{            
            if (xmlType == "gameObject"){
              if (!(error += mapGameObject(env, rootNode)).empty())
                return error;
            }
            else if (xmlType == "layout"){
              if (!(error = mapLayout(env, rootNode)).empty())
                return error;
            }
            else if (xmlType == "layer"){
              if (!(error = mapLayer(env, rootNode)).empty())
                return error;
            }
            else if (xmlType == "scene"){              
              if (!(error = mapScene(env, rootNode)).empty())
                return error;
            }
            return "";
          }
        }
        j = 0;
        i++;
      }
      i = 0;
      return "End";
    }

    // fill the environement object
    static std::string fillEnvironment(Environment& env, const std::unordered_map<std::string, std::vector<std::string>>& resources)
    {
      std::string error = "";
      std::string tmp = "";

      while ((tmp = getNextXmlTree(env, "gameObject", resources.at("gameobjects"))) != "End"){
        if (!tmp.empty()){
          error += tmp;
          break;
        }
      }
      while ((tmp = getNextXmlTree(env, "layout", resources.at("layouts"))) != "End"){
        if (!tmp.empty()){
          error += tmp;
          break;
        }
      }
      while ((tmp = getNextXmlTree(env, "layer", resources.at("layers"))) != "End"){
        if (!tmp.empty()){
          error += tmp;
          break;
        }
      }
      while ((tmp = getNextXmlTree(env, "scene", resources.at("scenes"))) != "End"){
        if (!tmp.empty()){
          error += tmp;
          break;
        }
      }
      return error;
    }
  };

} /* nx */

#endif
