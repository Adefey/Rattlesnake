#pragma once

#include <sys/socket.h>
#include <netinet/in.h>

#include "netsocket.hpp"

class NetClient {
 public:
  bool SetServerAddress(const char* address);

 private:
  NetSocket client_socket_;
  sockaddr_in server_addr_;
};
