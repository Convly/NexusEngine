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
			std::vector<fs::path>	_soundPaths;
			std::vector<fs::path>	_musicPaths;
			std::vector<fs::path>	_scriptPaths;
			std::vector<fs::path>	_imagePaths;

		public:
			Ressources() {}
			~Ressources() {}

			// Setters
			void	addSoundPath(fs::path const& soundPath)
			{
				this->_soundPaths.push_back(soundPath);
			}

			void	addMusicPath(fs::path const& musicPath)
			{
				this->_musicPaths.push_back(musicPath);
			}

			void	addImagePath(fs::path const& imagePath)
			{
				this->_imagePaths.push_back(imagePath);
			}

			void	addScriptPath(fs::path const& scriptPath)
			{
				this->_scriptPaths.push_back(scriptPath);
			}

			// Getters
			std::vector<fs::path> &	getSoundPaths()
			{
				return (this->_soundPaths);
			}

            fs::path getSoundPathAt(int idx) {
                return (this->_soundPaths.at(idx));
            }

			std::vector<fs::path> &	getMusicPaths()
			{
				return (this->_musicPaths);
			}

            fs::path getMusicPathAt(int idx) {
                return (this->_musicPaths.at(idx));
            }

			std::vector<fs::path> &	getImagePaths()
			{
				return (this->_imagePaths);
			}

            fs::path getImagePathAt(int idx) {
                return (this->_imagePaths.at(idx));
            }

			std::vector<fs::path> &	getScriptPaths()
			{
				return (this->_scriptPaths);
			}

            fs::path getScriptPathAt(int idx) {
                return (this->_scriptPaths.at(idx));
            }
		};
	}
}

#endif /* NEXUS_ENGINE__RESSOURCES_HPP_ */