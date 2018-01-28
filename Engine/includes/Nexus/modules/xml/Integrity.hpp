#ifndef INTEGRITY_HPP_
# define INTEGRITY_HPP_

#include <iostream>
#include <unordered_map>
#include <algorithm>

#include "Nexus/modules/environment/Environment.hpp"
#include "rapidxml-1.13/rapidxml.hpp"

#include "Nexus/standalone/Split.hpp"

using namespace rapidxml;

namespace nx{
namespace xml{

    class Util{
    public:
        static void initMandatoryAtt(std::vector<std::string>& mandatoryAtt){
            mandatoryAtt = {
                "name"
            };
        }

        static std::string getAttributes(const std::string& tagName, xml_node<>* rootNode, std::unordered_map<std::string, std::string>& attributes){
            std::string error = "";
            std::vector<std::string> mandatoryAtt;

            initMandatoryAtt(mandatoryAtt);
            for (auto node = rootNode->first_attribute(); node; node = node->next_attribute()){
                std::string key = node->name();
                std::string value = node->value();
                if (attributes.find(key) == attributes.end())
                    attributes[key] = value;
                else
                    error += "Error: This attribute \"" + key + "\" already exist in the " + tagName + " named \"" + attributes.at("name") + "\"\n";
            }
            for (auto att : mandatoryAtt){
                if (attributes.find(att) == attributes.end())
                    error += "Error: A \"" + tagName + "\" tag need to have a \"" + att + "\"\n";
            }
            return error;
        }
    };

    class Integrity{
    public:
        static bool boolValue(const std::string& str, std::string& error){
            if (str == "True")
                return true;
            else if (str == "False")
                return false;
            error += "Error: this attribute \"" + str + "\" need to be a boolean\n";
            return true;
        }

        static nx::env::RGBa color(const std::string& str, std::string& error){
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
                    error += "Error: this color attribute \"" + str + "\" is not in the correct format. They all need to be float.\n";
                }
            }
            else
                error += "Error: this color attribute \"" + str + "\" is not in the correct format. \"r,g,b,a\"\n";
            return backgroundColor;
        }

        static std::string path(env::Environment& env, const std::string& pathType, const std::string& str, std::string& error){
            try{
                Crawler crawler(env.getGameInfos().getRootPath() + pathType);
            }
            catch (...){
                error += "Error: An attribute path is incorrect \"" + str + "\"\n"; 
            }
            return str;
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

        static int intValue(const std::string& str, std::string& error){
            int rotation = 0;

            try{
                rotation = std::stoi(str);
            }
            catch (...){
                error += "Error: this attribute \"" + str + "\" is not in the correct format. It need to be a int\n";
            }
            return rotation;
        }

        static maths::Vector2f xyValues(const std::string& str, std::string& error){
            maths::Vector2f size = 0;
            std::vector<std::string> splitedValue = split(str, ',');

            if (splitedValue.size() == 2){
                try{
                    size.x = std::stof(splitedValue.at(0));
                    size.y = std::stof(splitedValue.at(1));
                }
                catch (...){
                    error += "Error: this attribute \"" + str + "\" is not in the correct format. \"float,float\"\n";
                }
            }
            else
                error += "Error: this attribute \"" + str + "\" is not in the correct format. \"x,y\"\n";
            return size;
        }

        static int opacity(const std::string& str, std::string& error){
            int opacity = 0;

            try{
                opacity = std::stoi(str);
                if (opacity < 0 || opacity > 100)
                    error += "Error: this direction attribute \"" + str + "\" is not in the correct format. It need to be between 0 and 100\n";
            }
            catch (...){
                error += "Error: this opacity attribute \"" + str + "\" is not in the correct format. It need to be between 0 and 100\n";
                opacity = 0;
                return 0;
            }
            return opacity;
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
            double doubleValue = 0;

            try{
                doubleValue = std::stod(str);
            }
            catch (...){
                error += "Error: this " + name + " attribute \"" + str + "\" is not in the correct format. It need to be a double\n";
            }
            return doubleValue;
        }

        static void event(nx::env::MouseEventsContainer& events, const std::string& pathType, env::Environment& env, const std::string& str, const std::string& eventName, std::string& error){
            nx::env::MouseEventsContainer event;
            std::vector<std::string> splitedValue = split(str, ':');

            if (splitedValue.size() == 2){
                try{
                    Crawler crawler(env.getGameInfos().getRootPath() + pathType);
                    std::string fctName = splitedValue.at(1);
                    events.push_back({ eventName, script::ScriptInfos(splitedValue.at(0), fctName) });
                }
                catch (...){
                    error += "Error: this \"" + eventName + "\" attribute \"" + str + "\" is not in the correct format. (path is incorect or not found)\n";
                }
            }
            else
                error += "Error: this \"" + eventName + "\" attribute \"" + str + "\" is not in the correct format.\n";
        }
    };

}
}

#endif