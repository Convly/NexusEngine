#include "FrameworkNetwork.hpp"

FrameworkNetwork::FrameworkNetwork(nx::Engine *engine)
	:
	_isListen(false),
	nx::NetworkFrameworkTpl("FrameworkNetwork"),
	_engine(engine) {
  std::cout << "New Network Framework created" << std::endl;
}

FrameworkNetwork::~FrameworkNetwork() {
  std::cout << "New Network Framework deleted" << std::endl;
}

void FrameworkNetwork::acceptor(std::string port) {
  if (this->_isListen) {
	return;
  }

  int sock = socket(PF_INET, SOCK_STREAM, 0);

  struct sockaddr_in address;
  memset(&address, 0, sizeof(address));
  address.sin_family = PF_INET;
  address.sin_port = htons(std::atoi(port.data()));
  address.sin_addr.s_addr = INADDR_ANY;

  int optval = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);

  int result = bind(sock, (struct sockaddr *)&address, sizeof(address));
  if (result != 0) {
	perror("bind() failed");
	return;
  }

  nx::Log::debug("[Network] Start acceptor (0.0.0.0:" + port + ")");

  result = listen(sock, 5);
  if (result != 0) {
	perror("listen() failed");
	return;
  }
  this->_isListen = true;
}

void FrameworkNetwork::connect(std::string ip, std::string port) {
}
