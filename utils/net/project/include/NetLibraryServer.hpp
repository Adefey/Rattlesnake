#pragma once

#include "INetLibrary.hpp"
#include "NetServer.hpp"

class NetLibraryServer : public INetLibrary {
 public:
  bool SendData(NetSocket socket, std::string data) override;
  bool SendBlocksJson(NetServer server, std::string blocks);
  bool SendResultsJson(NetServer server, std::string results);

  std::string ReceiveBlocksJson(NetServer server);
  std::string ReceiveData(NetSocket socket) override;
};
