//
// Made by Marco
//

#include "NetworkUdp.hpp"

NetworkUdp::NetworkUdp(nx::Engine *engine) :
	_engine(engine),
	_socket(0),
	_addrInfo(nullptr),
	_ip(""),
	_port(0),
	_sendMode(false)
{
	__initSocket();
}

NetworkUdp::~NetworkUdp()
{
	if (_addrInfo != nullptr)
		freeaddrinfo(_addrInfo);
	if (_socket)
		__closeSocket(_socket);
	__stopSocket();
}

void		NetworkUdp::startSend(const std::string &ip, unsigned short port, std::vector<char> data)
{
	char	decimal_port[16];
	struct	addrinfo hints;

	if (!_sendMode || _ip != ip || _port != port)
	{
		if (_sendMode == true)
			freeaddrinfo(_addrInfo);
		_sendMode = true;
		nx::Log::inform("init before send");
		_ip = ip;
		_port = port;

		snprintf(decimal_port, sizeof(decimal_port), "%d", _port);
		decimal_port[sizeof(decimal_port) / sizeof(decimal_port[0]) - 1] = '\0';
		memset(&hints, 0, sizeof(hints));

		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_DGRAM;
		hints.ai_protocol = IPPROTO_UDP;

		if (getaddrinfo(_ip.c_str(), decimal_port, &hints, &_addrInfo) != 0 || _addrInfo == NULL)
			throw nx::NetworkUdpException("invalid address or port: \"" + _ip + ":" + decimal_port + "\"");

		_socket = socket(_addrInfo->ai_family, SOCK_DGRAM, IPPROTO_UDP);
		if (_socket == -1)
		{
			freeaddrinfo(_addrInfo);
			throw nx::NetworkUdpException("could not create socket for: \"" + _ip + ":" + decimal_port + "\"");
		}
	}
	send(data);
}

void		NetworkUdp::startReceive(unsigned short port)
{
	this->_thReceive = std::make_shared<std::thread>(&NetworkUdp::receive, this, port);
}

void		NetworkUdp::send(std::vector<char> data)
{
	nx::Log::inform("Ready to send");

	std::string	msg;
	std::string body;
	std::string header;
	std::string footer;
	bool		run = true;

	while (run)
	{
		for (auto it : data)
			body += it;
		msg = header + body + footer;

		if (sendto(_socket, msg.c_str(), msg.size(), 0, _addrInfo->ai_addr, _addrInfo->ai_addrlen) == -1)
			nx::Log::inform("ERROR ON SEEEEEEEND !!");

		run = false;
	}
	nx::Log::inform("send ok");
}

void		NetworkUdp::receive(unsigned short port)
{
	_ip = "127.0.0.1";
	_port = port;

	nx::Log::inform("Init before recv");

	_sendMode = false;

	socklen_t addrlen = sizeof(_clientAddr);

	if ((_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		throw nx::NetworkUdpException("cannot create socket");

	memset((char *)&_serverAddr, 0, sizeof(_serverAddr));

	_serverAddr.sin_family = AF_INET;
	_serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	_serverAddr.sin_port = htons(_port);

	if (bind(_socket, (struct sockaddr *)&_serverAddr, sizeof(_serverAddr)) < 0)
		throw nx::NetworkUdpException("bind failed");

	nx::Log::inform("[UDP RECV] : starting listening");

	while (1)
	{
		nx::Log::debug("-- a");
		std::vector<char> data(4000);
		nx::Log::debug("-- b");

		nx::Log::debug("before recvfrom");
		if (recvfrom(_socket, data.data(), 4000, 0, (struct sockaddr *)&_clientAddr, &addrlen) == -1)
			nx::Log::debug("ERROR ERROR ERROR (recv from)");
			//throw nx::NetworkUdpException("recvfrom failed");
		nx::Log::debug("after recvfrom");
		nx::Log::debug("-- c");

		nx::Log::debug("[Network] Data:");
		nx::Log::debug(data.data());
		nx::Log::debug("--\n");
		nx::Log::debug("-- d");

		const nx::Event event = this->convertNetworkDataToEvent(data);
		nx::Log::debug("-- e");

		nx::Log::debug("Event type: " + std::to_string(event.type));

		nx::Log::debug("-- f");

		std::future<void> eventEmit(std::async([&]() {
			this->_engine->emit(event);
		}));
		nx::Log::debug("-- g");

		eventEmit.get();
		nx::Log::debug("-- h");
	}
	nx::Log::debug("STOP RECEIVE");
}
