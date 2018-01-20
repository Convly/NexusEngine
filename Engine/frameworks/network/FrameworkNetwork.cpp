#include "FrameworkNetwork.hpp"

FrameworkNetwork::FrameworkNetwork(nx::Engine* engine)
:
	nx::NetworkFrameworkTpl("FrameworkNetwork"),
	_engine(engine)
{
	nx::Log::inform("New Network Framework created");
}

FrameworkNetwork::~FrameworkNetwork()
{
	nx::Log::inform("New Network Framework deleted");
}

void FrameworkNetwork::pingNetworkFramework()
{
	nx::Log::inform("Pong");
}