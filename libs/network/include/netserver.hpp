#pragma once

#include <cstdint>

#include "netsocket.hpp"

class NetServer {
 public:
  bool InitializeServer(uint32_t port);
  NetServer();
  explicit NetServer(NetSocket server_socket);

 private:
  NetSocket server_socket_;
};
