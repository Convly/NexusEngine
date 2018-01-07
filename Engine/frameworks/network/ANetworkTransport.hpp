#ifndef NEXUSENGINE_ANETWORKTRANSPORT_HPP
#define NEXUSENGINE_ANETWORKTRANSPORT_HPP

#include <vector>

#include "Nexus/engine.hpp"

class ANetworkTransport {
 protected:
  std::vector<char> convertEventToNetworkData(nx::Event event) {
	auto const ptr = reinterpret_cast<char*>(&event);
	std::vector<char> data(ptr, ptr + sizeof event);
	return (data);
  }

  nx::Event convertNetworkDataToEvent(std::vector<char> data) {
	const nx::Event * event = reinterpret_cast<const nx::Event*>(data.data());
	return (*event);
  }
};

#endif //NEXUSENGINE_ANETWORKTRANSPORT_HPP
