#ifndef INTEGRITY_HPP_
# define INTEGRITY_HPP_

#include <iostream>
#include <unordered_map>

#include "Nexus/modules/environment/Environment.hpp"

namespace nx{
namespace xml{

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


            error += "Error: this backgroundColor attribute \"" + str + "\" is not in the correct format. \"r,g,b,a\"\n";
            return backgroundColor;
        }
    };

}
}

#endif