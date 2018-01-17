/*
** Scene.hpp for Test in /Users/metge_q/rendu/Test
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Tue Dec 26 20:39:05 2017 Quentin Metge
** Last update Tue Dec 26 20:46:11 2017 Quentin Metge
*/

#ifndef SCENE_HPP_
# define SCENE_HPP_

#include <unordered_map>

#include "Layer.hpp"

namespace nx
{
  /********  Scene  ********/
  class Scene
  {
  private:
    std::string _name = "";
    std::unordered_map<std::string, GameObject>  _gameObjects;
    std::vector<Component>                        _components;

  public:
    std::string&                                    getName() { return _name; }
    std::unordered_map<std::string, GameObject>&    getGameObjects() { return _gameObjects; }
    std::vector<Component>&                         getComponents() { return _components; }

  public:
    Scene() {}
    virtual ~Scene() {}
  }; /* Scene */
} 

#endif
