#ifndef NEXUS_ENGINE__RENDERING_UTILS_HPP
#define NEXUS_ENGINE__RENDERING_UTILS_HPP

#include "Nexus/engine.hpp"
#include "Nexus/standalone/network/netutils.hpp"

extern nx::Engine* enginePtr;

namespace nx {
namespace rendering {
namespace tools {
    static void script_bi_send(const nx::EVENT type, const external::any& data)
    {
        enginePtr->emit(nx::EVENT::NETCUST_SEND_EVENT, nx::Event(type, data));
        enginePtr->emit(type, data);
    }
}
}
}

#endif // !NEXUS_ENGINE__RENDERING_UTILS_HPP