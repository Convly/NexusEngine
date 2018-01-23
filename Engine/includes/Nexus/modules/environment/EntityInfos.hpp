#ifndef NEXUS_ENGINE__ENTITYINFOS_HPP_
#define NEXUS_ENGINE__ENTITYINFOS_HPP_

# include <string>

namespace nx
{
	namespace env
	{
		struct EntityInfos
		{
			std::string		name;
			bool			active;

		public:
			EntityInfos(std::string const& name_) : name(name_), active(true) {}
			EntityInfos(std::string const& name_, bool const active_) : name(name_), active(active_) {}
			~EntityInfos() {}
		};
	}
}

#endif /* NEXUS_ENGINE__ENTITYINFOS_HPP_ */