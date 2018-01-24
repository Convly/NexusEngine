#ifndef SPLIT_HPP_
# define SPLIT_HPP_

#include <iostream>
#include <vector>
#include <sstream>

namespace nx{
    template<typename Out>
    inline void split(const std::string &s, char delim, Out result, bool addEmpty = false){
        std::stringstream ss;
        ss.str(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            if (item != "" || addEmpty)
            *(result++) = item;
        }
    }

    inline std::vector<std::string> split(const std::string &s, char delim, bool addEmpty = false){
        std::vector<std::string> elems;
        split(s, delim, std::back_inserter(elems), addEmpty);
        return elems;
    }
}

#endif