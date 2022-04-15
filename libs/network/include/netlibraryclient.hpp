#pragma once

#include "inetlibrary.hpp"
#include "netclient.hpp"

class NetLibraryClient : public INetLibrary {
 public:
  bool SendData(NetSocket socket, std::string data) override;
  bool SendBlocksRequest(NetClient client);
  bool SendBlocksJson(NetClient client, std::string blocks);
  bool SendSchemeJson(NetClient client, std::string scheme);

  std::string ReceiveData(NetSocket socket) override;
  std::string ReceiveBlocksJson(NetClient client);
};
