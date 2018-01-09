#ifndef NEXUSENGINE_NETWORKTCP_HPP
#define NEXUSENGINE_NETWORKTCP_HPP

#include <memory>

#include <thread>
#include <atomic>
#include <unordered_map>
#include <future>
#include <chrono>
#include <string.h>


#include "Nexus/errors/NetworkTcpException.hpp"


#ifdef _WIN32
#include <ws2tcpip.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <arpa/inet.h>
#endif

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)

#include "Nexus/engine.hpp"

#include "ANetworkTransport.hpp"

void	__initSocket();
void	__closeSocket(int socket);

class NetworkTcp : public ANetworkTransport {
 protected:
  // Linux
  struct NetworkTcpTunnel {
	unsigned int		id;
	struct sockaddr_in	addr;
	int					fd;
  };
  // End - Linux
 protected:
  nx::Engine *_engine;

  std::unordered_map<unsigned int, NetworkTcpTunnel>						_tunnels;
  std::unordered_map<unsigned int, std::shared_ptr<std::thread>>			_thClients;


  // Server mode
  std::shared_ptr<std::thread>	_thAccept;

  // Client mode
  std::shared_ptr<std::thread>	_thConnect;
 public:
  NetworkTcp(nx::Engine *);
  ~NetworkTcp();

  void startAccept(unsigned short port);
  void startConnect(std::string ip, unsigned short port);

  void send(unsigned int id, std::vector<char> data);
 private:
  // Linux
  void accept(unsigned short port);
  void connect(std::string ip, unsigned short port);
  void handleOneTunnel(NetworkTcpTunnel networkTcpTunnel);
  void write(NetworkTcpTunnel networkTcpTunnel, std::vector<char> data);
  // End - Linux
};

#endif //NEXUSENGINE_NETWORKTCP_HPP
