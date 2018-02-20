#ifndef NEXUS_ENGINE_SERIALIZATION_HPP_
#define NEXUS_ENGINE_SERIALIZATION_HPP_

#include <atomic>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>

#include "Nexus/modules/environment/Environment.hpp"
#include "Nexus/standalone/network/netutils.hpp"

BOOST_CLASS_EXPORT_GUID(nx::DerivedPlacedHolder<nx::UdpEventPacket>, "p<nx::UdpEventPacket>");
BOOST_CLASS_EXPORT_GUID(nx::DerivedPlacedHolder<nx::netcust_host_t>, "p<nx::netcust_host_t>");
BOOST_CLASS_EXPORT_GUID(nx::DerivedPlacedHolder<nx::netserv_client_t>, "p<nx::netserv_client_t>");
BOOST_CLASS_EXPORT_GUID(nx::DerivedPlacedHolder<std::string>, "p<std::string>");
BOOST_CLASS_EXPORT_GUID(nx::DerivedPlacedHolder<nx::Any>, "p<nx::Any>");
BOOST_CLASS_EXPORT_GUID(nx::DerivedPlacedHolder<uint8_t>, "p<uint8_t>");
BOOST_CLASS_EXPORT_GUID(nx::DerivedPlacedHolder<int>, "p<int>");
BOOST_CLASS_EXPORT_GUID(nx::DerivedPlacedHolder<nx::env::Scene>, "p<nx::env::Scene>");
BOOST_CLASS_EXPORT_GUID(nx::DerivedPlacedHolder<nx::env::RGBa>, "p<nx::env::RGBa>");
BOOST_CLASS_EXPORT_GUID(nx::DerivedPlacedHolder<nx::script::ScriptInfos>, "p<nx::script::ScriptInfos>");

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