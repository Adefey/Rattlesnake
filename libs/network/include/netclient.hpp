#pragma once

#include <netinet/in.h>
#include <sys/socket.h>

#include "netsocket.hpp"

class NetClient {
 public:
  NetClient();

  NetClient(const NetClient&) = delete;
  NetClient(NetClient&&) = delete;

  NetClient operator=(const NetClient&) = delete;
  NetClient operator=(NetClient&&) = delete;

  ~NetClient() = default;

  bool SetServerAddress(const char* address, uint16_t port);
  bool ConnectToServer();
  void DisconnectFromServer();
  NetSocket& GetClientSocket();

 private:
  NetSocket client_socket_;
  sockaddr_in server_addr_;
};
