/*
** Environment.hpp for Test in /Users/metge_q/rendu/Test
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Mon Dec 18 14:00:34 2017 Quentin Metge
** Last update Mon Jan 08 14:53:05 2018 Quentin Metge
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>

#include "Scene.hpp"

namespace nx
{
  /********  TMP  ********/
  class Resources
  {
  public:
    std::vector<std::string> scenes;
    std::vector<std::string> gameObjects;
    std::vector<std::string> layouts;

  public:
    Resources() {
      scenes.push_back("./Scenes");
      gameObjects.push_back("./GameObjects");
      layouts.push_back("./Layouts");
    }
    virtual ~Resources() {}
  };

  /*******************************/
  /********  Environment  ********/
  /*******************************/
  class Environment
  {
  private:
    std::unordered_map<std::string, GameObject> _gameObjects;
    std::unordered_map<std::string, Layout>     _layouts;
    std::unordered_map<std::string, Scene>      _scenes;

  public:
    std::unordered_map<std::string, Scene>&       getScenes() { return _scenes; }
    std::unordered_map<std::string, GameObject>&  getGameObjects() { return _gameObjects; }
    std::unordered_map<std::string, Layout>&      getLayouts() { return _layouts; }

  public:
    Environment(){}
    virtual ~Environment(){}
  };
  /************************/
} /* nx */
