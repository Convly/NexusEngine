#include "Nexus/systems/SystemTpl.hpp"
#include "Nexus/engine.hpp"

nx::SystemTpl::SystemTpl(const std::string& name)
:
	_name(name),
	_engine(nx::Engine::Instance()),
	_maxConnectID(0)
{

}

nx::SystemTpl::~SystemTpl()
{

}

const std::string&	nx::SystemTpl::getName() const
{
	return this->_name;
}

const nx::Engine& nx::SystemTpl::getEngine() const
{
	return this->_engine;
}

void nx::SystemTpl::emitter(const nx::Event& event)
{
	for (const auto link : this->_links)
	{
		if (link.type == event.type) {
			link.callback(event);
		}
	}
}

uint32_t nx::SystemTpl::connect(const nx::EVENT eventType, const std::function<void(const nx::Event&)>& callback)
{
	this->_maxConnectID++;

	this->_links.push_back(nx::EventLink(
		this->_maxConnectID,
		eventType,
		callback
	));

	return this->_maxConnectID;
}

bool nx::SystemTpl::disconnect(const uint32_t uid)
{
	auto it = std::find_if(this->_links.begin(), this->_links.end(), [&](auto item){return (item.uid == uid);});
	if (uid > this->_maxConnectID) {
		nx::Log::error("The given UID is greater than the maxID assigned", "BAD_DISCONNECT_UID", 3);
		return false;
	} else if (it == this->_links.end()) {
		nx::Log::error("There is no link with the given UID", "BAD_DISCONNECT_UID", 3);
		return false;
	}

	this->_links.erase(it);
	return true;
}