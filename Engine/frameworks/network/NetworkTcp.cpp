#include "NetworkTcp.hpp"

static void error(int socket)
{
#ifdef _WIN32
	std::string msg(std::string("[BIND] error:") + std::string(strerror(WSAGetLastError())));
#else
	std::string msg(std::string("[BIND] error:") + std::string(strerror(errno)));
#endif
	__closeSocket(socket);
	nx::NetworkTcpException(msg.c_str());
}

NetworkTcp::NetworkTcp(nx::Engine *engine) :
	_engine(engine)
{
	__initSocket();
}

NetworkTcp::~NetworkTcp()
{
	__stopSocket();
}

void NetworkTcp::startAccept(unsigned short port) {
  this->_thAccept = std::make_shared<std::thread>(&NetworkTcp::accept, this, port);
}

void NetworkTcp::startConnect(std::string ip, unsigned short port) {
  this->_thConnect = std::make_shared<std::thread>(&NetworkTcp::connect, this, ip, port);
}

void NetworkTcp::send(unsigned int id, std::vector<char> data) {
  auto it = this->_tunnels.find(id);
  if (it == this->_tunnels.end())
	return ;
  try
  {
	  this->write(it->second, data);
  }
  catch (const nx::NetworkTcpException &e)
  {
	  nx::Log::debug(std::string("[SEND] on tunnel [") + std::to_string(id) + std::string("] error: ") + std::string(e.what()));
  }
}

// Linux
void NetworkTcp::accept(unsigned short port) {
  unsigned int idMax = 1;

  nx::Log::debug("Start accept");

  int sockfd, new_fd;  /* Écouter sur sock_fd, nouvelle connection sur new_fd */
  struct sockaddr_in my_addr;    /* Informations d'adresse */
  struct sockaddr_in their_addr; /* Informations d'adresse du client */
  socklen_t sin_size;

  memset(&my_addr, 0, sizeof(struct sockaddr_in));
  memset(&their_addr, 0, sizeof(struct sockaddr_in));

  sockfd = socket(PF_INET, SOCK_STREAM, 0); /* Contrôle d'erreur! */

  my_addr.sin_family = AF_INET;         /* host byte order */
  my_addr.sin_port = htons(port);     /* short, network byte order */
  my_addr.sin_addr.s_addr = INADDR_ANY; /* auto-remplissage avec mon IP */
  bzero(&(my_addr.sin_zero), 8);        /* zero pour le reste de struct */

	/* ne pas oublier les contrôles d'erreur pour ces appels: */
  if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
	  error(sockfd);

  if (listen(sockfd, 10) == -1)
	  error(sockfd);

  sin_size = sizeof(struct sockaddr_in);

  NetworkTcpTunnel networkTcpTunnel;

  while (1)
  {
	if ((new_fd = ::accept(sockfd, (struct sockaddr*)&their_addr, &sin_size)) < 0)
		error(sockfd);


	networkTcpTunnel.id = idMax;
	networkTcpTunnel.fd = new_fd;
	networkTcpTunnel.addr = their_addr;
	this->_tunnels.insert(std::pair<unsigned int, NetworkTcpTunnel>(idMax, networkTcpTunnel));
	this->_thClients.insert(std::pair<unsigned int, std::shared_ptr<std::thread>>(idMax, std::make_shared<std::thread>(&NetworkTcp::handleOneTunnel, this, networkTcpTunnel)));
	idMax += 1;
  }
}

void NetworkTcp::connect(std::string ip, unsigned short port)
{
	struct sockaddr_in address;
  memset(&address, 0, sizeof(struct sockaddr_in));
  address.sin_family = AF_INET;
  address.sin_port = htons(port);
  address.sin_addr.s_addr = inet_addr(ip.c_str());
  int sd = socket(PF_INET, SOCK_STREAM, 0);
  if (::connect(sd, (struct sockaddr*)&address, sizeof(address)) != 0)
	  error(sd);

  NetworkTcpTunnel	networkTcpTunnel;

  networkTcpTunnel.id = 0;
  networkTcpTunnel.fd = sd;
  networkTcpTunnel.addr = address;
  this->_tunnels.insert(std::pair<unsigned int, NetworkTcpTunnel>(0, networkTcpTunnel));
  this->handleOneTunnel(networkTcpTunnel);
}

void NetworkTcp::handleOneTunnel(NetworkTcpTunnel tunnel)
{
  nx::Log::debug("New tunnel handle");
  
  while (1)
  {
	std::vector<char> data(4000);
	if (::recv(tunnel.fd, data.data(), data.size(), 0) <= 0)
		break;

	nx::Log::debug("[Network] Data:");
	nx::Log::debug(data.data());
	nx::Log::debug("--\n");

	const nx::Event event = this->convertNetworkDataToEvent(data);

	nx::Log::debug("Event type: " + std::to_string(event.type));

	std::future<void> eventEmit(std::async([&]() {
	  this->_engine->emit(event);
	}));

	eventEmit.get();
  }
  nx::Log::debug(std::string("Tunnel ") + std::to_string(tunnel.id) + std::string(" close"));
  __closeSocket(tunnel.fd);
  _tunnels.erase(tunnel.id);
}

void NetworkTcp::write(NetworkTcpTunnel networkTcpTunnel, std::vector<char> data)
{
  nx::Log::debug("New data write");

  if (::send(networkTcpTunnel.fd, data.data(), data.size(), 0) <= 0)
	  error(networkTcpTunnel.fd);
}
// End - Linux