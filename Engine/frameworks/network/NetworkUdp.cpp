//
// Made by Marco
//

#include "NetworkUdp.hpp"

NetworkUdp::NetworkUdp(nx::Engine *engine) :
	_engine(engine),
	_ipS(""),
	_portS(0),
	_socketS(0),
	_addrInfo(nullptr),
	_ipC(""),
	_portC(0),
	_socketC(0)
{
	__initSocket();
}

NetworkUdp::~NetworkUdp()
{
	if (_addrInfo != nullptr)
		freeaddrinfo(_addrInfo);
	if (_socketS)
		__closeSocket(_socketS);
	if (_socketC)
		__closeSocket(_socketC);
	__stopSocket();
}

void		NetworkUdp::startSend(const std::string &ip, unsigned short port, std::vector<char> data)
{
	char	decimal_port[16];
	struct	addrinfo hints;

	const nx::Event e = *this->convertNetworkDataToEvent(data);

	nx::Log::inform("[UDP START SEND] event.type: [" + std::to_string(e.type) + "]");
	nx::Log::inform("[UDP START SEND] event.arg: [" + std::string(e.data.data()) + "]");
	nx::Log::inform("[UDP START SEND] size = " + std::to_string(data.size()));

	std::cout << "must init" << std::endl;

	if (_ipC != ip || _portC != port)
	{
		if (_ipC != "" || _portC != 0)
			freeaddrinfo(_addrInfo);
		nx::Log::inform("init before send");
		_ipC = ip;
		_portC = port;

		snprintf(decimal_port, sizeof(decimal_port), "%d", _portC);
		decimal_port[sizeof(decimal_port) / sizeof(decimal_port[0]) - 1] = '\0';
		memset(&hints, 0, sizeof(hints));

		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_DGRAM;
		hints.ai_protocol = IPPROTO_UDP;

		std::cout << "get addr info to pass" << std::endl;

		if (getaddrinfo(_ipC.c_str(), decimal_port, &hints, &_addrInfo) != 0 || _addrInfo == NULL)
			throw nx::NetworkUdpException("invalid address or port: \"" + _ipC + ":" + decimal_port + "\"");

		std::cout << "get addr info done" << std::endl;

		_socketC = socket(_addrInfo->ai_family, SOCK_DGRAM, IPPROTO_UDP);
		if (_socketC == -1)
		{
			freeaddrinfo(_addrInfo);
			std::cout << "error on socket creation" << std::endl;
			throw nx::NetworkUdpException("could not create socket for: \"" + _ipC + ":" + decimal_port + "\"");
		}
	}
	int count = 1;
	while (count)
	{
		send(data);
		count -= 1;
	}
}

void		NetworkUdp::startReceive(unsigned short port)
{
	this->_thReceive = std::make_shared<std::thread>(&NetworkUdp::receive, this, port);
}

void		NetworkUdp::send(std::vector<char> data)
{
	const nx::Event e = *this->convertNetworkDataToEvent(data);

	nx::Log::inform("[UDP SEND] event.type: [" + std::to_string(e.type) + "]");
	nx::Log::inform("[UDP SEND] event.arg: [" + std::string(e.data.data()) + "]");

	nx::Log::inform("Ready to send");

	bool		run = true;
	while (run)
	{
		std::vector<char>	toSend(4000, 0);
		for (size_t i = 0; i < data.size() && i < toSend.size(); ++i)
			toSend[i] = data[i];
		nx::Log::inform("[UDP SEND] Raw Data: [" + std::string(data.data()) + "]");

		int r = 0;

		if ((r = sendto(_socketC, toSend.data(), toSend.size(), 0, _addrInfo->ai_addr, _addrInfo->ai_addrlen)) == -1)
			nx::Log::inform("ERROR ON SEEEEEEEND !!");

		nx::Log::inform("[UDP SEND] send ok " + std::to_string(r));

		run = false;
	}
	nx::Log::inform("send ok");
}

void		NetworkUdp::receive(unsigned short port)
{
	_ipS = "127.0.0.1";
	_portS = port;

	nx::Log::inform("Init before recv");

	_sendMode = false;

	socklen_t addrlen = sizeof(_clientAddr);

	if ((_socketS = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		throw nx::NetworkUdpException("cannot create socket");

	memset((char *)&_serverAddr, 0, sizeof(_serverAddr));

	_serverAddr.sin_family = AF_INET;
	_serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	_serverAddr.sin_port = htons(_portS);

	if (bind(_socketS, (struct sockaddr *)&_serverAddr, sizeof(_serverAddr)) < 0)
		throw nx::NetworkUdpException("bind failed");

	nx::Log::inform("[UDP RECV] : starting listening");

	int count = 0;

	int r = 0;

	std::vector<char> data;
	data.reserve(4000);
	
	while (1)
	{
		data.clear();
		nx::Log::debug("before recvfrom");
		if ((r = ::recvfrom(_socketS, data.data(), 4000, 0, (struct sockaddr *)&_clientAddr, &addrlen)) == -1)
			nx::Log::debug("ERROR ERROR ERROR (recv from)");
			//throw nx::NetworkUdpException("recvfrom failed");
		nx::Log::debug("after recvfrom " + std::to_string(r));

		nx::Log::inform("[UDP RECEIVE] Raw Data: [" + std::string(data.data()) + "]");
		nx::Log::debug("--\n");

		if (data.data() == nullptr)
			nx::Log::inform(":D :) :| :[ :( :G :'G");
		std::cout << "before NETWORK DATA to EVENT" << std::endl;
		const nx::Event event = *this->convertNetworkDataToEvent(data);
		std::cout << "after NETWORK DATA to EVENT" << std::endl;

		std::cout << "string of data = " << event.stringFromVector(data) << std::endl;

		nx::Log::debug("[UDP RECEIVE] Event type: " + std::to_string(event.type));
		std::future<void> eventEmit(std::async([&]() {
			this->_engine->emit(event);
		}));

		eventEmit.get();
		count += 1;
		std::cout << "requetes recu: " << count << std::endl;
	}
	nx::Log::debug("STOP RECEIVE");
}
