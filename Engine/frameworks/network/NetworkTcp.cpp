#include "NetworkTcp.hpp"

NetworkTcp::NetworkTcp(nx::Engine *engine):
	_engine(engine){

}

NetworkTcp::~NetworkTcp() {

}

void NetworkTcp::startAccept(unsigned short port) {
  this->_thAccept = std::make_shared<std::thread>(&NetworkTcp::accept, this, port);
}

void NetworkTcp::startConnect(std::string ip, unsigned short port) {
  this->connect(ip, port);
}

void NetworkTcp::send(unsigned int id, std::vector<char> data) {
  auto it = this->_clients.find(id);
  if (it == this->_clients.end())
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

	sockfd = socket(AF_INET, SOCK_STREAM, 0); /* Contrôle d'erreur! */

	my_addr.sin_family = AF_INET;         /* host byte order */
	my_addr.sin_port = htons(port);     /* short, network byte order */
	my_addr.sin_addr.s_addr = INADDR_ANY; /* auto-remplissage avec mon IP */
	bzero(&(my_addr.sin_zero), 8);        /* zero pour le reste de struct */

	/* ne pas oublier les contrôles d'erreur pour ces appels: */
	bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr));

	listen(sockfd, 10);

	sin_size = sizeof(struct sockaddr_in);
	new_fd = ::accept(sockfd, (struct sockaddr*)&their_addr, &sin_size);

	NetworkTcpClient networkTcpClient;

	networkTcpClient.fd = new_fd;
	networkTcpClient.addr = their_addr;
	this->_clients.insert(std::pair<unsigned int, NetworkTcpClient>(idMax, networkTcpClient));
	this->_thClients.insert(std::pair<unsigned int, std::shared_ptr<std::thread>>(idMax, std::make_shared<std::thread>(&NetworkTcp::handleOneClient, this, idMax)));
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
  ::connect(sd, (struct sockaddr*)&address, sizeof(address));
}

void NetworkTcp::handleOneClient(unsigned int id) {
  nx::Log::debug("New client handle");
}

void NetworkTcp::write(NetworkTcpClient networkTcpClient, std::vector<char> data) {
  nx::Log::debug("New date write");
}
// End - Linux