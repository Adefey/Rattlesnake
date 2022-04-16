#pragma once

#include "inetlibrary.hpp"
#include "netserver.hpp"

class NetLibraryServer : public INetLibrary {
 public:
  NetLibraryServer();
  bool SendBlocksJson(NetServer server, std::string blocks);
  bool SendResultsJson(NetServer server, std::string results);
  std::string ReceiveBlocksJson(NetServer server);
  ~NetLibraryServer() override;

 private:
  std::string ReceiveData(NetSocket socket) override;
  bool SendData(NetSocket socket, std::string data) override;
};
