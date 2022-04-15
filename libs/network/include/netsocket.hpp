#pragma once

class NetSocket {
 public:
  void SetSocket(int socket);
  int GetSocket() const;
  bool CreateSocket();
  void CloseSocket();

 private:
  int socket_;
};
