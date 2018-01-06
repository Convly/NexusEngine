#ifndef NEXUSENGINE_NETWORKTCP_HPP
#define NEXUSENGINE_NETWORKTCP_HPP

#include <arpa/inet.h>
#include <memory>
#include <strings.h>

#include <thread>
#include <atomic>
#include <unordered_map>

#include "Nexus/engine.hpp"

class NetworkTcp {
 protected:
  // Linux
  struct NetworkTcpClient {
	struct sockaddr_in	addr;
	int					fd;
  };
  // End - Linux
 protected:
  nx::Engine *_engine;

  std::unordered_map<unsigned int, NetworkTcpClient>						_clients;
  std::unordered_map<unsigned int, std::shared_ptr<std::thread>>			_thClients;


  std::shared_ptr<std::thread>	_thAccept;
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
  void handleOneClient(unsigned int id);
  void write(NetworkTcpClient networkTcpClient, std::vector<char> data);
  // End - Linux
};

#endif //NEXUSENGINE_NETWORKTCP_HPP
