#pragma once

class NetSocket {
 public:
  NetSocket();

  NetSocket(const NetSocket&) = delete;
  NetSocket(NetSocket&&) = delete;

  NetSocket operator=(const NetSocket&) = delete;
  NetSocket operator=(NetSocket&&) = delete;

  ~NetSocket();

  int GetSocket() const;
  bool CreateSocket();
  void SetSocket(const int& socket);
  void CloseSocket();
  bool IsSocketOpen() const;

 private:
  int socket_;
};
