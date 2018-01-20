#include "FrameworkNetworkServer.hpp"

FrameworkNetworkServer::FrameworkNetworkServer(nx::Engine* engine)
:
	nx::NetworkServerFrameworkTpl("FrameworkNetworkServer"),
	_engine(engine)
{
	nx::Log::inform("New NetworkServer Framework created");
}

FrameworkNetworkServer::~FrameworkNetworkServer()
{
	nx::Log::inform("New NetworkServer Framework deleted");
}

void FrameworkNetworkServer::pingNetworkServerFramework()
{
	nx::Log::inform("Pong");
}