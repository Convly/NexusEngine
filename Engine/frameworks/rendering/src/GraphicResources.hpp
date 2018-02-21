#ifndef NEXUS_ENGINE__GRAPHICRESOURCES_HPP_
#define NEXUS_ENGINE__GRAPHICRESOURCES_HPP_

struct GraphicResources
{
	std::unordered_map<std::string, sf::Font *> fonts;
	std::unordered_map<std::string, sf::Texture> textures;
};

#endif /* NEXUS_ENGINE__GRAPHICRESOURCES_HPP_ */