#pragma once

#include "NetSocket.hpp"

class NetServer {
 public:
  bool InitializeServer(uint32_t port);

 private:
  NetSocket server_socket_;
};
