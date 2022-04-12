
#ifndef NETSERVER
#define NETSERVER

typedef int NetSocket;

class NetServer {
private:
  int server_socket;

public:
  NetServer(int port);
};

#endif
