#pragma once

#include "netclient.hpp"
#include "netlibrary.hpp"

class NetLibraryClient : public NetLibrary {
 public:
  static bool SendBlocksRequest(NetClient& sender);
  static bool SendSchemeJson(NetClient& sender, const std::string& scheme);
  static bool ReceiveBlocksJson(NetClient& receiver, std::string& blocks);
  static bool ReceiveResultsJson(NetClient& receiver, std::string& results);
};
