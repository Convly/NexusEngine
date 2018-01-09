#include "NetworkTcp.hpp"

NetworkTcp::NetworkTcp(nx::Engine *engine):
	_engine(engine){
	__initSocket();
}

NetworkTcp::~NetworkTcp() {

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
  this->write(it->second, data);
}

// Linux
void NetworkTcp::accept(unsigned short port) {
  unsigned int idMax = 1;

  nx::Log::debug("Start accept");
  while (1) {
	int sockfd, new_fd;  /* Écouter sur sock_fd, nouvelle connection sur new_fd */
	struct sockaddr_in my_addr;    /* Informations d'adresse */
	struct sockaddr_in their_addr; /* Informations d'adresse du client */
	socklen_t sin_size;

	memset(&my_addr, 0, sizeof(struct sockaddr_in));
	memset(&their_addr, 0, sizeof(struct sockaddr_in));

	sockfd = socket(AF_INET, SOCK_STREAM, 0); /* Contrôle d'erreur! */

	my_addr.sin_family = AF_INET;         /* host byte order */
	my_addr.sin_port = htons(port);     /* short, network byte order */
	my_addr.sin_addr.s_addr = INADDR_ANY; /* auto-remplissage avec mon IP */
	bzero(&(my_addr.sin_zero), 8);        /* zero pour le reste de struct */

	/* ne pas oublier les contrôles d'erreur pour ces appels: */
	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
	{
#ifdef _WIN32
		std::cerr << "[BIND] error: " << strerror(WSAGetLastError()) << std::endl;
#else
		std::cerr << "[BIND] error: " << strerror(errno) << std::endl;
#endif
		//	  nx::NetworkTcpException(strerror(errno));
		exit(84);
	}

	if (listen(sockfd, 10) == -1)
	{
#ifdef _WIN32
		std::cerr << "[LISTEN] error: " << strerror(WSAGetLastError()) << std::endl;
#else
		std::cerr << "[LISTEN] error: " << strerror(errno) << std::endl;
#endif
		//nx::NetworkTcpException(strerror(errno));
		exit(84);
	}

	sin_size = sizeof(struct sockaddr_in);
	if ((new_fd = ::accept(sockfd, (struct sockaddr*)&their_addr, &sin_size)) == -1)
	{
#ifdef _WIN32
		std::cerr << "[ACCEPT] error: " << strerror(WSAGetLastError()) << std::endl;
#else
		std::cerr << "[ACCEPT] error: " << strerror(errno) << std::endl;
#endif
		//nx::NetworkTcpException(strerror(errno));
		exit(84);
	}

	NetworkTcpTunnel networkTcpTunnel;

	networkTcpTunnel.id = idMax;
	networkTcpTunnel.fd = new_fd;
	networkTcpTunnel.addr = their_addr;
	this->_tunnels.insert(std::pair<unsigned int, NetworkTcpTunnel>(idMax, networkTcpTunnel));
	this->_thClients.insert(std::pair<unsigned int, std::shared_ptr<std::thread>>(idMax, std::make_shared<std::thread>(&NetworkTcp::handleOneTunnel, this, networkTcpTunnel)));
	idMax += 1;
  }
}

void NetworkTcp::connect(std::string ip, unsigned short port) {
  struct sockaddr_in address;

  bzero(&address, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_port = htons(port);
  address.sin_addr.s_addr = inet_addr(ip.c_str());
  int sd = socket(AF_INET, SOCK_STREAM, 0);
  if (::connect(sd, (struct sockaddr*)&address, sizeof(address)) != 0)
	nx::NetworkTcpException(strerror(errno));

  NetworkTcpTunnel	networkTcpTunnel;

  networkTcpTunnel.id = 0;
  networkTcpTunnel.fd = sd;
  networkTcpTunnel.addr = address;
  this->_tunnels.insert(std::pair<unsigned int, NetworkTcpTunnel>(0, networkTcpTunnel));

  this->handleOneTunnel(networkTcpTunnel);
}

void NetworkTcp::handleOneTunnel(NetworkTcpTunnel tunnel) {
  nx::Log::debug("New tunnel handle");
  while (1) {
	std::vector<char> data(4000);
	::recv(tunnel.fd, data.data(), data.size(), 0);

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
}

void NetworkTcp::write(NetworkTcpTunnel networkTcpTunnel, std::vector<char> data) {
  nx::Log::debug("New date write");

  if (::send(networkTcpTunnel.fd, data.data(), data.size(), 0) == -1)
	nx::NetworkTcpException(strerror(errno));
}
// End - Linux