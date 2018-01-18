#ifndef LAYER_HPP_
# define LAYER_HPP_

#include "Layout.hpp"

#include "Nexus/frameworks/RenderingFrameworkTpl.hpp"

namespace nx
{
  /********  GuiElement  ********/
  class GuiElement
  {
  private:
    std::string _name = "";
    std::string _type = "";
    int         _width = 0;
    int         _height = 0;
    Vector2d    _pos;
    std::string _backgroundColor = "";
    std::string _borderColor = "";
    bool        _pressButton = "";
    std::string _text = "";
    std::string _textColor = "";
    rendering::MouseEventsContainer _events;

  public:
    std::string&    getName() { return _name; }
    std::string&    getType() { return _type; }
    int&            getWidth() { return _width; }
    int&            getHeight() { return _height; }
    Vector2d&       getPos() { return _pos; }
    std::string&    getBackgroundColor() { return _backgroundColor; }
    std::string&    getBorderColor() { return _borderColor; }
    bool&           getPressButton() { return _pressButton; }    
    std::string&    getText() { return _text; }
    std::string&    getTextColor() { return _textColor; }
    rendering::MouseEventsContainer& getEvents() { return _events; }

  public:
    GuiElement() {}
    virtual ~GuiElement() {}
  }; /* GuiElement */

  /********  Layer  ********/
  class Layer
  {
  private:
    std::string _name = "";
    std::vector<GuiElement> _guiElements;

  public:
    std::string&   getName() { return _name; }
    std::vector<GuiElement>&  getGuiElements() { return _guiElements; }

  public:
    Layer() {}
    virtual ~Layer() {}
  }; /* Layer */
}

#endif