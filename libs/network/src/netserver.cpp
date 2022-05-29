#include "netserver.hpp"

#include <netinet/in.h>

NetServer::NetServer() : server_socket_() {
  server_socket_.CreateSocket();
}

bool NetServer::InitializeServer(uint16_t port) {
  struct sockaddr_in server_addr {};
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(port);

  if (bind(server_socket_.GetSocket(), (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
    return false;
  }

  listen(server_socket_.GetSocket(), 32);

  return true;
}

bool NetServer::AcceptConnection(NetSocket& value) const {
  int client_socket = accept(server_socket_.GetSocket(), nullptr, nullptr);
  if (client_socket > -1) {
    value.SetSocket(client_socket);
    return true;
  }
  return false;
}
