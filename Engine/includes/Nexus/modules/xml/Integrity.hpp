#ifndef INTEGRITY_HPP_
# define INTEGRITY_HPP_

#include <iostream>
#include <unordered_map>

#include "Nexus/modules/environment/Environment.hpp"
#include "rapidxml-1.13/rapidxml.hpp"

#include "Nexus/standalone/Split.hpp"

using namespace rapidxml;

namespace nx{
namespace xml{

    class Util{
    public:
        static std::string getAttributes(const std::string& tagName, xml_node<>* rootNode, std::unordered_map<std::string, std::string>& attributes){
            std::string error = "";

            for (auto node = rootNode->first_attribute(); node; node = node->next_attribute()){
                std::string key = node->name();
                std::string value = node->value();
                if (attributes.find(key) == attributes.end())
                    attributes[key] = value;
                else{
                    if (attributes.find("name") != attributes.end())
                        error += "Error: this attribute \"" + key + "\" already exist in the " + tagName + " named \"" + attributes.at("name") + "\"\n";
                    else
                        error += "Error: A \"" + tagName + "\" tag doesn't have a name\n";
                }
            }
            return error;
        }
    };

    class Integrity{
    public:
        static bool active(const std::string& str, std::string& error){
            if (str == "True")
                return true;
            else if (str == "False")
                return false;
            error += "Error: this active attribute \"" + str + "\" is not a boolean\n";
            return true;
        }

        static nx::env::RGBa backgroundColor(const std::string& str, std::string& error){
            nx::env::RGBa backgroundColor;
            std::vector<std::string> splitedValue = split(str, ',');

            if (splitedValue.size() == 4){
                try{
                    backgroundColor.setRed(std::stof(splitedValue.at(0)));
                    backgroundColor.setGreen(std::stof(splitedValue.at(1)));
                    backgroundColor.setBlue(std::stof(splitedValue.at(2)));
                    backgroundColor.setAlpha(std::stof(splitedValue.at(3)));
                }
                catch (...){
                    error += "Error: this backgroundColor attribute \"" + str + "\" is not in the correct format. They all need to be float.\n";
                }
            }
            else
                error += "Error: this backgroundColor attribute \"" + str + "\" is not in the correct format. \"r,g,b,a\"\n";
            return backgroundColor;
        }

        static std::string path(env::Environment& env, const std::string& str, std::string& error){
            std::string path = env.getGameInfos().getRootPath() + str;

            try{
                Crawler crawler(path);
            }
            catch (...){
                error += "Error: An attribute path is incorect \"" + str + "\"\n"; 
            }
            return path;
        }

        static maths::Vector2f pos(const std::string& str, std::string& error){
            maths::Vector2f pos;
            std::vector<std::string> splitedValue = split(str, ',');

            if (splitedValue.size() == 2){
                try{
                    pos.x = std::stof(splitedValue.at(0));
                    pos.y = std::stof(splitedValue.at(1));
                }
                catch (...){
                    error += "Error: this pos attribute \"" + str + "\" is not in the correct format. They all need to be float\n";
                }
            }
            else
                error += "Error: this pos attribute \"" + str + "\" is not in the correct format. \"x,y\"\n";
            return pos;
        }

        static int rotation(const std::string& str, std::string& error){
            int rotation;

            try{
                rotation = std::stoi(str);
            }
            catch (...){
                error += "Error: this roation attribute \"" + str + "\" is not in the correct format. It need to be a int\n";
            }
            return rotation;
        }

        static maths::Vector2f size(const std::string& str, std::string& error){
            maths::Vector2f size;
            std::vector<std::string> splitedValue = split(str, ',');

            if (splitedValue.size() == 2){
                try{
                    size.x = std::stof(splitedValue.at(0));
                    size.y = std::stof(splitedValue.at(1));
                }
                catch (...){
                    error += "Error: this size attribute \"" + str + "\" is not in the correct format. They all need to be float\n";
                }
            }
            else
                error += "Error: this size attribute \"" + str + "\" is not in the correct format. \"x,y\"\n";
            return size;
        }

        static maths::Vector2f direction(const std::string& str, std::string& error){
            maths::Vector2f direction;
            std::vector<std::string> splitedValue = split(str, ',');

            if (splitedValue.size() == 2){
                try{
                    direction.x = std::stof(splitedValue.at(0));
                    direction.y = std::stof(splitedValue.at(1));
                }
                catch (...){
                    error += "Error: this direction attribute \"" + str + "\" is not in the correct format. They all need to be float\n";
                }
            }
            else
                error += "Error: this direction attribute \"" + str + "\" is not in the correct format. \"x,y\"\n";
            return direction;
        }

        static int opacity(const std::string& str, std::string& error){
            int opacity;

            if (opacity >= 0 && opacity <= 100){
                try{
                    opacity = std::stoi(str);
                }
                catch (...){
                    error += "Error: this opacity attribute \"" + str + "\" is not in the correct format. It need to be between 0 and 100\n";
                }
            }
            else
                error += "Error: this direction attribute \"" + str + "\" is not in the correct format. \"x,y\"\n";
            return opacity;
        }

        static std::string texturePath(env::Environment& env, const std::string& str, std::string& error){
            std::string path = env.getGameInfos().getRootPath() + str;

            try{
                Crawler crawler(path);
            }
            catch (...){
                error += "Error: An attribute texturePath is incorect \"" + str + "\"\n"; 
            }
            return path;
        }

        static env::ShapeType shapeType(const std::string& str, std::string& error){
            env::ShapeType shapeType = env::ShapeType::UNDEFINED;

            if (str == "None")
                shapeType = env::ShapeType::UNDEFINED;
            else if (str == "Rectangle")
                shapeType = env::ShapeType::RECTSHAPE;
            else if (str == "Circle")
                shapeType = env::ShapeType::CIRCLESHAPE;
            else if (str == "Convex")
                shapeType = env::ShapeType::CONVEXSHAPE;
            else
                error += "Error: An attribute shapeType is incorect \"" + str + "\". It need to be one of these \"None\", \"Rectangle\", \"Circle\", \"Convex\"\n";
            return shapeType;
        }

        static double doubleValue(const std::string& name, const std::string& str, std::string& error){
            double doubleValue;

            try{
                doubleValue = std::stod(str);
            }
            catch (...){
                error += "Error: this " + name + " attribute \"" + str + "\" is not in the correct format. It need to be a double\n";
            }
            return doubleValue;
        }
    };

}
}

#endif