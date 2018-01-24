#ifndef NX_ENGINE__STANDALONE_GAMEINFOSPARSER_HPP
#define NX_ENGINE__STANDALONE_GAMEINFOSPARSER_HPP

#include "Nexus/standalone/GameInfosParser/rapidjson/document.h"
#include "Nexus/standalone/GameInfosParser/rapidjson/istreamwrapper.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include "Nexus/errors/BadFormatGameJSONException.hpp"

namespace nx {

    class GameInfosParser {
        const std::vector<std::string>	GameInfosAttrs = {
            "title",
            "version",
            "author",
            "icon",
            "cover",
            "description",
            "url",
            "remote",
            "command"
        };

        const std::vector<std::string>	GameRessourcesAttrs = {
            "xml",
            "scripts",
            "sounds",
            "musics",
            "images"
        };

        struct Fields {
            std::unordered_map<std::string, std::string> _infos;
            std::unordered_map<std::string, std::string> _resources;
        };

    public:
        GameInfosParser(const std::string& confPath)
        :
            _path(confPath)
        {
            auto d = this->getJSONDocumentFromPath();

            if (d.HasParseError()) {
                throw nx::BadFormatGameJSONException("JSON format is incorrect");
            }

            if (d.FindMember("game") == d.MemberEnd()) {
                throw nx::BadFormatGameJSONException("Cannot access 'game' tag");
            } else if (d["game"].GetObject().FindMember("infos") == d["game"].GetObject().MemberEnd()) {
                throw nx::BadFormatGameJSONException("Cannot access 'infos' tag");		
            } else if (d["game"].GetObject().FindMember("ressources") == d["game"].GetObject().MemberEnd()) {
                throw nx::BadFormatGameJSONException("Cannot access 'ressources' tag");
            }

            this->getInfosTags(d);
            this->getRessourceTags(d);

            this->checkInfosIntegrity();
        }

        virtual ~GameInfosParser() {}

    public:
        rapidjson::Document getJSONDocumentFromPath()
        {
            std::ifstream ifs(this->_path);
            rapidjson::IStreamWrapper isw(ifs);
            rapidjson::Document d;
            d.ParseStream(isw);
            return d;
        }

        void getInfosTags(const rapidjson::Document& d)
        {
            for (const auto& item : d["game"].GetObject()["infos"].GetObject()) {
                std::string name(item.name.GetString());
                std::string value(item.value.GetString());
                bool validParam = (std::find_if(nx::GameInfosParser::GameInfosAttrs.begin(), nx::GameInfosParser::GameInfosAttrs.end(), [&](auto it){return it == name;}) != nx::GameInfosParser::GameInfosAttrs.end());
                if (!validParam) {
                    std::string ret = "Unknown infos parameter: " + name;
                    throw nx::BadFormatGameJSONException(ret);
                }
                this->_fields._infos[name] = value;
            }
        }

        void getRessourceTags(const rapidjson::Document& d)
        {
            for (const auto& item : d["game"].GetObject()["ressources"].GetObject()) {
                std::string name(item.name.GetString());
                std::string value = item.value.GetString();
                bool validParam = (std::find_if(nx::GameInfosParser::GameRessourcesAttrs.begin(), nx::GameInfosParser::GameRessourcesAttrs.end(), [&](auto it){return it == name;}) != nx::GameInfosParser::GameRessourcesAttrs.end());
                if (!validParam) {
                    std::string ret = "Unknown ressources parameter: " + name;
                    throw nx::BadFormatGameJSONException(ret);
                }
                this->_fields._resources[name] = value;
            }
        }

        void checkInfosIntegrity() const
        {
            for (auto tag : nx::GameInfosParser::GameInfosAttrs)
            {
                if (std::find_if(this->_fields._infos.begin(), this->_fields._infos.end(), [&](auto it){return tag == it.first;}) == this->_fields._infos.end()) {
                    std::string ret = "Missing infos tag '" + tag + "'";
                    throw nx::BadFormatGameJSONException(ret);
                }
            }

            for (auto tag : nx::GameInfosParser::GameRessourcesAttrs)
            {
                if (std::find_if(this->_fields._resources.begin(), this->_fields._resources.end(), [&](auto it){return tag == it.first;}) == this->_fields._resources.end()) {
                    std::string ret = "Missing ressource tag '" + tag + "'";
                    throw nx::BadFormatGameJSONException(ret);
                }
            }
        }

        void dump() const
        {
            std::cerr << "_> Dumping JSON file at " << this->_path << ":" << std::endl;
            for (auto it : this->_fields._infos) {
                std::cerr << "_> >>> " << it.first << "\t-\t" << it.second << std::endl;
            }
            for(auto it : this->_fields._resources) {
                std::cerr << "_> >>> " << it.first << ":" << std::endl;
                std::cerr << "\t\t >>> " << it.second << std::endl;
            }
        }

        const std::string& getPath() const {
            return this->_path;
        }

        const nx::GameInfosParser::Fields& getFields() const {
            return this->_fields;
        }

        nx::GameInfosParser::Fields& getFields() {
            return this->_fields;
        }

	private:
		std::string                         _path;
		nx::GameInfosParser::Fields         _fields;
    };
}

#endif