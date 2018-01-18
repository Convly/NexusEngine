/*
** Environment.hpp for Test in /Users/metge_q/rendu/Test
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Mon Dec 18 14:00:34 2017 Quentin Metge
** Last update Mon Jan 08 14:53:05 2018 Quentin Metge
*/

#ifndef ENVIRONMENT_HPP_
# define ENVIRONMENT_HPP_

#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>

#include "Scene.hpp"

namespace nx
{
  /*******************************/
  /********  Environment  ********/
  /*******************************/
  class Environment
  {
  private:
    std::vector<GameObject> _gameObjects;
    std::vector<Layout>     _layouts;
    std::vector<Layer>      _layers;
    std::vector<Scene>      _scenes;

  public:
    std::vector<Scene>&       getScenes() { return _scenes; }
    std::vector<GameObject>&  getGameObjects() { return _gameObjects; }
    std::vector<Layout>&      getLayouts() { return _layouts; }
    std::vector<Layer>&       getLayers() { return _layers; }

  public:
    Environment(){}
    virtual ~Environment(){}
  };
  /************************/
} /* nx */

#endif