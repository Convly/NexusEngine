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

#include "rapidxml-1.13/rapidxml.hpp"
#include "Directory.hpp"
#include "Environment.hpp"

using namespace rapidxml;

namespace nx
{
  class XmlParser
  {
  public:
    XmlParser(){}
    virtual ~XmlParser(){}

  public:
    // get the next xml tree of a list a directory
    static std::string getNextXmlTree(Environment& env, const std::string xmlType, const std::vector<std::string>& dirPaths)
    {
      std::string error = "";
      xml_node<>* rootNode = nullptr;
      static std::vector<std::string> filesName;
      xml_document<> doc; 
      static int i = 0;

      while (i < dirPaths.size())
      {
        static int j = 0;

        if (j == 0 && !getComponentFilesName(dirPaths[i], filesName))
        {
          std::cerr << "Error: " << dirPaths[i] << std::endl;
          i = 0;
          j = 0;
          return nullptr;
        }
        while (j < filesName.size())
        {
          std::ifstream theFile(filesName[j++]);
          std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
          buffer.push_back('\0');
          doc.parse<0>(&buffer[0]);
          rootNode = doc.first_node("nx");
          if (rootNode == nullptr)
          {
            error += "Error: nx tag not found in " + filesName[j - 1] + "\n";
            std::cerr << "Error: nx tag not found in " << filesName[j - 1] << std::endl;
          }
          else
          {
            if (xmlType == "gameObject"){
              if (!(error += mapGameObject(env, rootNode)).empty())
                return error;
            }
            else if (xmlType == "layout"){
              if (!(error = mapLayout(env, rootNode)).empty())
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

    // Parse and add a gameObject to env
    static std::string mapGameObject(Environment& env, xml_node<>* rootNode)
    {
      std::string error = "";

      try
      {
        // Browse gameObjects
        for (xml_node<>* gameObjectNode = rootNode->first_node("gameObject"); gameObjectNode; gameObjectNode = gameObjectNode->next_sibling("gameObject"))
        {
          GameObject gameObject;
          std::string gameObjectName;

          if (gameObjectNode->first_attribute("name"))
          {
            gameObjectName = gameObjectNode->first_attribute("name")->value();
            gameObject.getName() = gameObjectName;
          }
          else
          {
            error += "Error: A game object doesn't have name\n";
            break;
          }
          if (gameObjectNode->first_attribute("tag"))
          {
            gameObject.getTag() = gameObjectNode->first_attribute("tag")->value();
          }
          else
          {
            error += "Error: A game object doesn't have name\n";
            break;
          }

          // Browse components
          for (auto componentNode = gameObjectNode->first_node("component"); componentNode; componentNode = componentNode->next_sibling("component"))
          {
            Component component;
            if (componentNode->first_attribute("type"))
            {
              component.getType() = componentNode->first_attribute("type")->value();
            }
            else
            {
                error += "Error: " + gameObjectName + " doesn't have type\n";
                break;
            }

            // Position
            if (componentNode->first_node("pos"))
            {
              if (componentNode->first_node("pos")->first_attribute("x") && componentNode->first_node("pos")->first_attribute("y"))
              {
                component.getPosition().x = std::stoi(componentNode->first_node("pos")->first_attribute("x")->value());
                component.getPosition().y = std::stoi(componentNode->first_node("pos")->first_attribute("y")->value());
              }
              else
                error += "Error: incorect position in the game object " + gameObjectName + "\n";
            }

            // Rotation
            if (componentNode->first_node("rotation"))
            {
              if (componentNode->first_node("rotation")->first_attribute("x") && componentNode->first_node("rotation")->first_attribute("y"))
              {
                component.getRotation().x = std::stoi(componentNode->first_node("rotation")->first_attribute("x")->value());
                component.getRotation().y = std::stoi(componentNode->first_node("rotation")->first_attribute("y")->value());
              }
              else
                error += "Error: incorect rotation in the game object " + gameObjectName + "\n";
            }

            // Texture
            if (componentNode->first_node("texture"))
            {
              if (componentNode->first_node("texture")->first_attribute("src"))
              {
                component.getSrc() = componentNode->first_node("texture")->first_attribute("src")->value();
              }
              else
                error += "Error: incorect texture in the game object " + gameObjectName + "\n";
            }

            // Opacity
            if (componentNode->first_node("opacity"))
            {
              if (componentNode->first_node("opacity")->first_attribute("value"))
              {
                component.getOpacity() = std::atoi(componentNode->first_node("opacity")->first_attribute("value")->value());
              }
              else
                error += "Error: incorect opacity in the game object " + gameObjectName + "\n";
            }
            gameObject.getComponents().push_back(component);
          }
          env.getGameObjects()[gameObjectName] = gameObject;
        }
      }
      catch (std::exception e)
      {
        error += "Error: Invalid argument";
      }
      return error;
    }

    // Parse and add a layout to env
    static std::string mapLayout(Environment& env, xml_node<>* rootNode)
    {
      std::string error = "";

      try
      {
        // Browse gameObjects
        for (xml_node<>* layoutNode = rootNode->first_node("layout"); layoutNode; layoutNode = layoutNode->next_sibling("layout"))
        {
          Layout layout;
          std::string layoutName;

          if (layoutNode->first_attribute("name"))
          {
            layoutName = layoutNode->first_attribute("name")->value();
          }
          else
          {
            error += "Error: A game object doesn't have name\n";
            break;
          }
          for (auto attributeNode = layoutNode->first_node(); attributeNode; attributeNode = attributeNode->next_sibling())
          {
            if (std::string(attributeNode->name()).compare("component") == 0)
            {
              Component component;

              if (attributeNode->first_attribute("type") && attributeNode->first_attribute("src"))
              {
                component.getType() = attributeNode->first_attribute("type")->value();
                component.getSrc() = attributeNode->first_attribute("src")->value();
                layout.getComponents().push_back(component);
              }
              else
              {
                error += "Error: Bad attrute for a component of " + layoutName;
              }
            }
            else if (std::string(attributeNode->name()).compare("gameObject") == 0)
            {
              if (attributeNode->first_attribute("name"))
              {                
                auto it = env.getGameObjects().find(attributeNode->first_attribute("name")->value());
                if (it != env.getGameObjects().end())
                {                  
                  layout.getGameObjects().insert({ it->first, it->second });
                }
                else
                {                  
                  error += "Error: this game object doesn't exist ";
                  error += attributeNode->first_attribute("name")->value();
                  error += "\n";
                }
              }
            }
          }
          env.getLayouts()[layoutName] = layout;
        }
      }
      catch (std::exception e)
      {
        error += "Error: Invalid argument";
      }
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
            if (std::string(attributeNode->name()).compare("component") == 0)
            {
              Component component;

              if (attributeNode->first_attribute("type") && attributeNode->first_attribute("src"))
              {
                component.getType() = attributeNode->first_attribute("type")->value();
                component.getSrc() = attributeNode->first_attribute("src")->value();
                scene.getComponents().push_back(component);
              }
              else
              {
                error += "Error: Bad attrute for a component of " + sceneName;
              }
            }
            else if (std::string(attributeNode->name()).compare("gameObject") == 0)
            {
              if (attributeNode->first_attribute("name"))
              {                
                auto it = env.getGameObjects().find(attributeNode->first_attribute("name")->value());
                if (it != env.getGameObjects().end())
                {                  
                  scene.getGameObjects().insert({ it->first, it->second });
                }
                else
                {                  
                  error += "Error: this game object doesn't exist ";
                  error += attributeNode->first_attribute("name")->value();
                  error += "\n";
                }
              }
            }
            else if (std::string(attributeNode->name()).compare("layout") == 0)
            {
              if (attributeNode->first_attribute("name"))
              {                
                auto it = env.getLayouts().find(attributeNode->first_attribute("name")->value());
                if (it != env.getLayouts().end())
                {                  
                  scene.getLayouts().insert({ it->first, it->second });
                }
                else
                {                  
                  error += "Error: this layout doesn't exist ";
                  error += attributeNode->first_attribute("name")->value();
                  error += "\n";
                }
              }
            }
          }
          env.getScenes()[sceneName] = scene;
        }
      }
      catch (std::exception e)
      {
        error += "Error: Invalid argument";
      }
      return error;
    }

    // fill the environement object
    static std::string fillEnvironment(Environment& env, const Resources& resources)
    {
      std::string error = "";
      std::string tmp = "";

      while ((tmp = getNextXmlTree(env, "gameObject", resources.gameObjects)) != "End"){
        if (!tmp.empty())
          error += tmp;
      }
      while ((tmp = getNextXmlTree(env, "layout", resources.layouts)) != "End"){
        if (!tmp.empty())
          error += tmp;
      }
      while ((tmp = getNextXmlTree(env, "scene", resources.scenes)) != "End"){
        if (!tmp.empty())
          error += tmp;
      }
      return error;
    }
  };

} /* nx */

#endif
