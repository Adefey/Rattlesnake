#include "netclient.hpp"

#include <arpa/inet.h>

NetClient::NetClient() : client_socket_(), server_addr_() {}

bool NetClient::SetServerAddress(const char* address, uint16_t port) {
  server_addr_.sin_family = AF_INET;
  server_addr_.sin_port = htons(port);
  if (inet_aton(address, &server_addr_.sin_addr) == 0) {
    return false;
  }
  return true;
}

bool NetClient::ConnectToServer() {
  if (!client_socket_.IsSocketOpen() && !client_socket_.CreateSocket()) {
    return false;
  }
  if (server_addr_.sin_family != AF_INET) {
    return false;
  }
  int connected =
      connect(client_socket_.GetSocket(), (struct sockaddr*)&server_addr_, sizeof(server_addr_));
  return connected == 0;
}

void NetClient::DisconnectFromServer() {
  client_socket_.CloseSocket();
}

NetSocket& NetClient::GetClientSocket() {
  return client_socket_;
}
