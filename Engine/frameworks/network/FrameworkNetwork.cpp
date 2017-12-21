#include "FrameworkNetwork.hpp"

FrameworkNetwork::FrameworkNetwork(nx::Engine *engine)
	:
	nx::NetworkFrameworkTpl("FrameworkNetwork"),
	_engine(engine) {
  std::cout << "New Network Framework created" << std::endl;
}

FrameworkNetwork::~FrameworkNetwork() {
  std::cout << "New Network Framework deleted" << std::endl;
}

void FrameworkNetwork::waitClient(unsigned int port) {
  // Rework
  this->_thListenData = std::make_shared<std::thread>(&FrameworkNetwork::waitData, this, port);
}

void FrameworkNetwork::waitData(unsigned int port) {
  int sock = socket(PF_INET, SOCK_STREAM, 0);

  struct sockaddr_in address;
  memset(&address, 0, sizeof(address));
  address.sin_family = PF_INET;
  address.sin_port = htons(port);
  address.sin_addr.s_addr = INADDR_ANY;

  int optval = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);

  int result = bind(sock, (struct sockaddr *)&address, sizeof(address));
  if (result != 0) {
	perror("bind() failed");
	return;
  }

  nx::Log::debug("[Network] Start acceptor (0.0.0.0:" + std::to_string(port) + ")");

  result = listen(sock, 5);
  if (result != 0) {
	perror("listen() failed");
	return;
  }

  // Newclient
  struct sockaddr_in address1;
  socklen_t len = sizeof(address1);
  memset(&address1, 0, sizeof(address1));
  int sd = accept(sock, (struct sockaddr*)&address1, &len);
  if (sd < 0) {
	perror("accept() failed");
	return ;
  }

  nx::Log::debug("[Network] New client");
  //
}

void FrameworkNetwork::connect(std::string ip, unsigned int port) {
  struct sockaddr_in address;

  memset (&address, 0, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_port = htons(port);
  address.sin_addr.s_addr = inet_addr(ip.c_str());
  int sd = socket(AF_INET, SOCK_STREAM, 0);
  if (::connect(sd, (struct sockaddr*)&address, sizeof(address)) != 0) {
	return ;
  }
}
