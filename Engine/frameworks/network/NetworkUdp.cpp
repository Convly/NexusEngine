//
// Made by Marco
//

#include "NetworkUdp.hpp"

NetworkUdp::NetworkUdp() :
	_socket(0),
	_addrInfo(nullptr)
{
}

NetworkUdp::~NetworkUdp()
{
	if (_addrInfo != nullptr)
		freeaddrinfo(_addrInfo);
	if (_socket)
		__closeSocket(_socket);

}

void		NetworkUdp::startSend(const std::string &ip, unsigned short port)
{
	char	decimal_port[16];
	struct	addrinfo hints;

	__initSocket();

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

void		NetworkUdp::startReceive(unsigned short port)
{
	_ip = "127.0.0.1";
	_port = port;

	__initSocket();

	if ((_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		throw nx::NetworkUdpException("cannot create socket");

	memset((char *)&_serverAddr, 0, sizeof(_serverAddr));

	_serverAddr.sin_family = AF_INET;
	_serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	_serverAddr.sin_port = htons(_port);

	if (bind(_socket, (struct sockaddr *)&_serverAddr, sizeof(_serverAddr)) < 0)
		throw nx::NetworkUdpException("bind failed");
}

void		NetworkUdp::send(unsigned short port, std::vector<char> data)
{
	std::string	msg;

	for (auto it : data)
		msg += it;
	sendto(_socket, msg.c_str(), msg.size(), 0, _addrInfo->ai_addr, _addrInfo->ai_addrlen);

}

void		NetworkUdp::receive(unsigned short port)
{
	if (port <= 0)
		port = _port;
	socklen_t addrlen = sizeof(_clientAddr);
	memset(_buff, 0, MAX_BUFFER_SIZE);
	recvfrom(_socket, _buff, MAX_BUFFER_SIZE, 0, (struct sockaddr *)&_clientAddr, &addrlen);
}
