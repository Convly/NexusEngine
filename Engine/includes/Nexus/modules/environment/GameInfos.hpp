#ifndef NEXUS_ENGINE__GAMEINFOS_HPP_
#define NEXUS_ENGINE__GAMEINFOS_HPP_

namespace nx
{
	namespace env
	{
		class GameInfos
		{
		private:
			std::string _rootPath;
		
		public:
				template <typename Archive>
				void serialize(Archive& ar, unsigned int version)
				{
					ar & _rootPath;
				}

		public:
			GameInfos() : _rootPath("") {}
			GameInfos(const std::string& rootPath) : _rootPath(rootPath) {}
			~GameInfos() {}

		public:
			void setRootPath(const std::string& rootPath) { _rootPath = rootPath; }
			const std::string getRootPath() const { return _rootPath; }
		};
	}
}

#endif /* NEXUS_ENGINE__GAMEINFOS_HPP_ */