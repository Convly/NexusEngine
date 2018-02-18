#ifndef SFX_HPP_
# define SFX_HPP_

#include <iostream>
#include <functional>
#include <unordered_map>

#include "Nexus/modules/environment/Environment.hpp"
#include "Nexus/modules/xml/rapidxml-1.13/rapidxml.hpp"

using namespace rapidxml;

namespace nx
{
	namespace xml
	{

		class Sfx
		{
		public:

			static std::vector<env::Sfx> getSfx(env::Environment& env, const GameInfosParser& gameInfosParser, xml_node<>* rootNode, std::string& error)
			{
				std::unordered_map<std::string, std::string> attributes;
				std::vector<env::Sfx> sfx;

				for (xml_node<>* node = rootNode->first_node("Sfx"); node; node = node->next_sibling("Sfx"))
				{
					env::Sfx sfx;
					attributes.clear();
					if ((error += Util::getAttributes(node->name(), node, attributes)).empty())
						error += Sfx::fillSfx(env, gameInfosParser, sfx, node, attributes);
					sfx.push_back(sfx);
				}
				return sfx;
			}

			static std::string fillSfx(env::Environment& env, const GameInfosParser& gameInfosParser, env::Sfx& sfx, xml_node<>* rootNode, const std::unordered_map<std::string, std::string>& attributes)
			{
				std::string error = "";

				for (auto attribute : attributes)
				{
					if (attribute.first == "name")
					{
						sfx.getEntityInfos().setName(attributes.at("name"));
						sfx.setPath(attributes.at("name"));
					}
					else if (attribute.first == "active")
						layer.getEntityInfos().setActive(Integrity::boolValue(attributes.at("active"), error));
					else
						error += "Error: This attribute can't be created in this Layer tag \"" + attributes.at("name") + "\"\n";
				}
				for (xml_node<>* node = rootNode->first_node(); node; node = node->next_sibling()) {
					if (guiElementTags.find(std::string(node->name())) != guiElementTags.end())
						error += guiElementTags.at(std::string(node->name()))(env, gameInfosParser, layer, node);
					else
						error += "Error: This tag can not be in a Layer \"" + std::string(node->name()) + "\"\n";
				}
				return error;
			}
		};

	}
}

#endif // SFX_HPP_