
#ifndef NETSERVER
#define NETSERVER

typedef int NetSocket;

class NetServer {

private:
  int server_socket;

public:
  NetServer() : server_socket(0) {}
  NetServer(int port) : server_socket(port) {}
};

#endif
