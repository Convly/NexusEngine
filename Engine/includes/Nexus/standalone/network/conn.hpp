#ifndef NEXUS_ENGINE__CONN_HPP_
#define NEXUS_ENGINE__CONN_HPP_

#include "Nexus/engine.hpp"
#include "Nexus/standalone/network/netutils.hpp"

extern nx::Engine* enginePtr;

namespace nx {
    class Conn {
        public:
            Conn() {}
            ~Conn() {}

        public:
            static void localConnect(const std::string& ip, const short port)
            {
                external::any infos = nx::netcust_host_t(ip, port);
                enginePtr->emit(nx::EVENT::NETCUST_CONNECT, infos);
            }

            static void localDisconnect()
            {
                enginePtr->emit(nx::EVENT::NETCUST_DISCONNECT, 0);
            }
    };
}

#endif