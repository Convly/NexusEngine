//
// Made by Marco
//

#include "NetworkUdp.hpp"

#ifdef _WIN32

void	__initSocket()
{
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 0), &WSAData);
}

void	__closeSocket(int socket)
{
	closesocket(socket);
	WSACleanup();
}
#else

void	__initSocket()
{
}

void	__closeSocket(int socket)
{
	close(socket);
}
#endif // _WIN32