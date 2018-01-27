#ifndef PARSER_HPP_
# define PARSER_HPP_

#include <iostream>
#include <vector>

#include "rapidxml-1.13/rapidxml.hpp"
#include "Nexus/standalone/Crawler.hpp"
#include "Nexus/modules/environment/Environment.hpp"
#include "Nexus/standalone/GameInfosParser/GameInfosParser.hpp"
#include "Nexus/modules/xml/Xml.hpp"

using namespace rapidxml;

namespace nx{
namespace xml{

    class Parser{
    public:
        static std::string fillEnvironment(env::Environment& env, const GameInfosParser& gameInfosParser) {
            std::string error = "";
            env.getGameInfos().setRootPath(Crawler::getAbsoluteDir(gameInfosParser.getPath()).string());
            error += Parser::xml(env, gameInfosParser.getFields()._resources.at("game"));
            // scripts
            // sounds
            // musics
            // images
            return error;
        }

        // get the next xml tree of a list a directory
        static std::string xml(env::Environment& env, const std::string& path){
            std::string error = "";
            try{
                xml_node<>* rootNode = nullptr;
                std::vector<fs::path> filesName;
                xml_document<> doc;

                Crawler crawler(env.getGameInfos().getRootPath() + path);
                filesName = crawler.getRecursiveEntriesList();
                if (filesName.empty())
                    return "Error: there's no xml files in \"" + path + "\"\n";
                for (int i = 0; i < filesName.size(); i++){
                    std::ifstream theFile(filesName[i]);
                    std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
                    buffer.push_back('\0');
                    doc.parse<0>(&buffer[0]);
                    rootNode = doc.first_node("nx");
                    if (rootNode == nullptr)
                        error += "Error: nx tag not found in " + filesName[i].string() + "\n";
                    else 
                        error += Xml::fillEnvironment(env, rootNode);
                }
            }
            catch (...){
                error += "Error: on the loading xml file\n";
            }
            return error;
        }
    };

}
}

#endif