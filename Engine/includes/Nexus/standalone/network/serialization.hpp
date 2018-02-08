#ifndef NEXUS_ENGINE_SERIALIZATION_HPP_
#define NEXUS_ENGINE_SERIALIZATION_HPP_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/thread.hpp>
#include <boost/archive/text_iarchive.hpp>


#include "Nexus/standalone/network/netutils.hpp"

namespace nx {
    namespace serialization {
        static nx::UdpEventPacket deserialize(const std::string& data) {
			nx::UdpEventPacket packet;
			std::stringstream archive_stream(data);
			{
				boost::archive::text_iarchive archive(archive_stream);
				archive >> packet;
			}

			return packet;
		}

		static std::string serialize(const nx::UdpEventPacket& packet) {
			std::stringstream ss;
			{
				boost::archive::text_oarchive archive(ss);
				archive << packet;
			}
			return ss.str();
		}
    }
}

#endif