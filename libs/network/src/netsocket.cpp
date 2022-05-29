#include "netsocket.hpp"

#include <sys/socket.h>
#include <unistd.h>

NetSocket::NetSocket() {
  socket_ = -1;
}

NetSocket::~NetSocket() {
  if (socket_ != -1) {
    close(socket_);
  }
}

bool NetSocket::CreateSocket() {
  socket_ = socket(PF_INET, SOCK_STREAM, 0);
  if (socket_ == -1) {
    return false;
  }
  return true;
}

int NetSocket::GetSocket() const {
  return socket_;
}

void NetSocket::SetSocket(const int& socket) {
  CloseSocket();
  socket_ = socket;
}

void NetSocket::CloseSocket() {
  if (socket_ != -1) {
    close(socket_);
    socket_ = -1;
  }
}

bool NetSocket::IsSocketOpen() const {
  return socket_ != -1;
}
