#pragma once

class NetSocket {
 public:
  NetSocket();
  explicit NetSocket(int socket);

  void SetSocket(int socket);
  int GetSocket() const;
  bool CreateSocket();
  void CloseSocket();
  ~NetSocket();

 private:
  int socket_;
};
