/*
** GameObject.hpp for Test in /Users/metge_q/rendu/Test
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Tue Dec 26 20:37:27 2017 Quentin Metge
** Last update Mon Jan 08 14:58:58 2018 Quentin Metge
*/

#include <memory>
#include <unordered_map>

struct Vector2d
{
  Vector2d& operator=(Vector2d other)
  {
    x = other.x;
    y = other.y;
  }

  int x = 0;
  int y = 0;
};

namespace nx
{
  /********  Component  *******/
  class Component
  {
  private:
    std::string _type = "";
    std::string _tag = "";
    std::string _src = "";
    int         _opacity = 0;
    Vector2d    _position;
    Vector2d    _rotation;

  public:
    std::string&  getType() { return _type; }
    std::string&  getTag() { return _tag; }
    std::string&  getSrc() { return _src; }
    int&          getOpacity() { return _opacity; }
    Vector2d&     getPosition() { return _position; }
    Vector2d&     getRotation() { return _rotation; }

  public:
    Component() {}
    virtual ~Component() {}

  public:
    Component& operator=(Component other)
    {
      _tag = other.getTag();
      _type = other.getType();
      _src = other.getSrc();
      _opacity = other.getOpacity();
      _position = other.getPosition();
      _rotation = other.getRotation();
    }
  }; /* Component */

  /********  GameObject  *******/
  class GameObject
  {
  private:
    std::string _name = "";
    std::vector<Component> _components;

  public:
    std::string&  getName() { return _name; }
    std::vector<Component>& getComponents() { return _components; }

  public:
    GameObject() {}
    virtual ~GameObject() {}

  public:
    GameObject& operator=(GameObject other)
    {
      _name = other.getName();
      _components = other._components;
    }
  }; /* GameObject */
} /* nx */
