//
// Made by Marco
//

#ifndef NETWORK_UDP_HPP_
# define NETWORK_UDP_HPP_

#include <unordered_map>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <thread>
#include <atomic>
#include <future>
#include <chrono>

#include "Nexus/errors/NetworkUdpException.hpp"
#include "ANetworkTransport.hpp"
#include "Nexus/engine.hpp"

#ifdef _WIN32
#include <ws2tcpip.h>
#include <dbnetlib.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#endif // _WIN32

#define MAX_BUFFER_SIZE 2048

void	__initSocket();
void	__closeSocket(int socket);

class NetworkUdp : public ANetworkTransport
{
protected:
	nx::Engine			*_engine;
	int                 _socket;
	struct sockaddr_in 	_serverAddr;
	struct sockaddr_in 	_clientAddr;
	std::string         _ip;
	short               _port;
	char				_buff[MAX_BUFFER_SIZE];
	struct addrinfo		*_addrInfo;
	bool				_init;

	std::unordered_map<unsigned int, std::shared_ptr<std::thread>>			_thClients;

	//Server Mode
	std::shared_ptr<std::thread>	_thReceive;

	//Send
	std::shared_ptr<std::thread>	_thSend;

public:
	explicit	NetworkUdp(nx::Engine *engine);
	virtual		~NetworkUdp();

public:
	void		startSend(const std::string &ip, unsigned short port);
	void		startReceive(unsigned short port);

public:
	void		send(unsigned short port, std::vector<char> data);
	void		receive(unsigned short port);
};

#endif // NETWORK_UDP_HPP_
