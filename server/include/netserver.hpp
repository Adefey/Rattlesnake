
#ifndef NETSERVER
#define NETSERVER

typedef int NetSocket;

class NetServer {
private:
  int server_socket;

public:
  NetServer(){}
  NetServer(int port){}
};

#endif
