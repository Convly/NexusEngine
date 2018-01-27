#ifndef PARSER_HPP_
# define PARSER_HPP_

#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>

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
        static std::string addRessources(env::Environment& env, const GameInfosParser& gameInfosParser){
            std::string error = "";
            std::string current;
            std::vector<fs::path> filesName;

            try{
                current = "scripts";
                Crawler crawler(env.getGameInfos().getRootPath() + gameInfosParser.getFields()._resources.at(current));
                env.getRessources().getScriptPaths() = crawler.getRecursiveEntriesList();
                current = "musics";
                crawler = Crawler(env.getGameInfos().getRootPath() + gameInfosParser.getFields()._resources.at(current));
                env.getRessources().getMusicPaths() = crawler.getRecursiveEntriesList();
                current = "sounds";
                crawler = Crawler(env.getGameInfos().getRootPath() + gameInfosParser.getFields()._resources.at(current));
                env.getRessources().getSoundPaths() = crawler.getRecursiveEntriesList();
                current = "images";
                crawler = Crawler(env.getGameInfos().getRootPath() + gameInfosParser.getFields()._resources.at(current));
                env.getRessources().getImagePaths() = crawler.getRecursiveEntriesList();
            }
            catch (...){
                error += "Error: \"" + gameInfosParser.getFields()._resources.at(current) + "\" doesn't exist\n";
            }
            return error;
        }

        static bool fillEnvironment(env::Environment& env, const GameInfosParser& gameInfosParser) {
            std::string error = "";

            env.getGameInfos().setRootPath(Crawler::getAbsoluteDir(gameInfosParser.getPath()).string());
            error += addRessources(env, gameInfosParser);            
            error += Parser::xml(env, gameInfosParser.getFields()._resources.at("game"));
            if (!error.empty()){
                std::ofstream file;
                file.open (env.getGameInfos().getRootPath() + "/xml_error_log.txt");
                file << error;
                file.close();
                return false;
            }
            return true;
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