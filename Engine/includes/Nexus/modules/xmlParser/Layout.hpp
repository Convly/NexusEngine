/*
** Layout.hpp for Test in /Users/metge_q/rendu/Test
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Tue Dec 26 20:38:36 2017 Quentin Metge
** Last update Mon Jan 08 14:58:36 2018 Quentin Metge
*/

#ifndef LAYOUT_HPP_
# define LAYOUT_HPP_

#include <unordered_map>

#include "GameObject.hpp"

namespace nx
{
  /********  Layout  ********/
  class Layout
  {
  private:
    std::unordered_map<std::string, GameObject> _gameObjects;
    std::vector<Component> _components;
    std::string _name;

  public:
    std::unordered_map<std::string, GameObject>&  getGameObjects() { return _gameObjects; }
    std::vector<Component>&  getComponents() { return _components; }
    std::string& getName() { return _name; }

  public:
    Layout() {}
    virtual ~Layout() {}

  public:
    Layout& operator=(Layout other)
    {
      _gameObjects = other.getGameObjects();
      _components = other.getComponents();
    }
  };
} /* nx */

#endif