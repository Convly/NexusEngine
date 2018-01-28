#include "FrameworkNetworkClient.hpp"

FrameworkNetworkClient::FrameworkNetworkClient(nx::Engine* engine)
:
	nx::NetworkClientFrameworkTpl("FrameworkNetworkClient"),
	_engine(engine)
{
	nx::Log::inform("New NetworkClient Framework created");
}

FrameworkNetworkClient::~FrameworkNetworkClient()
{
	nx::Log::inform("New NetworkClient Framework deleted");
}