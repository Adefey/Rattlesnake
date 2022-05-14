#pragma once

#include <cstdint>

#include "netsocket.hpp"

class NetServer {
 public:
  NetServer();

  NetServer(const NetServer&) = delete;
  NetServer(NetServer&&) = delete;

  NetServer operator=(const NetServer&) = delete;
  NetServer operator=(NetServer&&) = delete;

  ~NetServer() = default;

  bool InitializeServer(uint16_t port);

  bool AcceptConnection(NetSocket& value) const;

 private:
  NetSocket server_socket_;
};
