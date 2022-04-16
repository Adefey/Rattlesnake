#pragma once

#include "inetlibrary.hpp"
#include "netclient.hpp"

class NetLibraryClient : public INetLibrary {
 public:
  NetLibraryClient();
  bool SendBlocksRequest(NetClient client);
  bool SendBlocksJson(NetClient client, std::string blocks);
  bool SendSchemeJson(NetClient client, std::string scheme);
  std::string ReceiveBlocksJson(NetClient client);
  ~NetLibraryClient() override;

 private:
  std::string ReceiveData(NetSocket socket) override;
  bool SendData(NetSocket socket, std::string data) override;
};
