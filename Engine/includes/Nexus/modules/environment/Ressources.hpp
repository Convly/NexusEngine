#ifndef NEXUS_ENGINE__RESSOURCES_HPP_
#define NEXUS_ENGINE__RESSOURCES_HPP_

# include <vector>

#include "Nexus/standalone/Crawler.hpp"

namespace nx
{
	namespace env
	{
		class Ressources
		{
		private:
			std::vector<std::string>	_soundPaths;
			std::vector<std::string>	_musicPaths;
			std::vector<std::string>	_scriptPaths;
			std::vector<std::string>	_imagePaths;
			std::vector<std::string>	_fontPaths;

		public:
			Ressources() {}
			~Ressources() {}

			// Setters
			void	addSoundPath(std::string const& soundPath)
			{
				this->_soundPaths.push_back(soundPath);
			}

			void	addMusicPath(std::string const& musicPath)
			{
				this->_musicPaths.push_back(musicPath);
			}

			void	addImagePath(std::string const& imagePath)
			{
				this->_imagePaths.push_back(imagePath);
			}

			void	addScriptPath(std::string const& scriptPath)
			{
				this->_scriptPaths.push_back(scriptPath);
			}

			void	addFontPath(std::string const& fontPath)
			{
				this->_fontPaths.push_back(fontPath);
			}

			// Getters
			std::vector<std::string> &	getSoundPaths()
			{
				return (this->_soundPaths);
			}

            std::string getSoundPathAt(int idx) {
                return (this->_soundPaths.at(idx));
            }

			std::vector<std::string> &	getMusicPaths()
			{
				return (this->_musicPaths);
			}

            std::string getMusicPathAt(int idx) {
                return (this->_musicPaths.at(idx));
            }

			std::vector<std::string> &	getImagePaths()
			{
				return (this->_imagePaths);
			}

            std::string getImagePathAt(int idx) {
                return (this->_imagePaths.at(idx));
            }

			std::vector<std::string> &	getScriptPaths()
			{
				return (this->_scriptPaths);
			}

            std::string getScriptPathAt(int idx) {
                return (this->_scriptPaths.at(idx));
            }

			std::vector<std::string> &	getFontPaths()
			{
				return (this->_fontPaths);
			}

            std::string getFontPathAt(int idx) {
                return (this->_fontPaths.at(idx));
            }
		};
	}
}

#endif /* NEXUS_ENGINE__RESSOURCES_HPP_ */