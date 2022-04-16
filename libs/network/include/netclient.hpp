#pragma once

#include <netinet/in.h>
#include <sys/socket.h>

#include "netsocket.hpp"

class NetClient {
 public:
  bool SetServerAddress(const char* address);
  NetClient();

 private:
  NetSocket client_socket_;
  sockaddr_in server_addr_;
};
