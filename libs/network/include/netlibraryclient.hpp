#pragma once

#include "netclient.hpp"
#include "netlibrary.hpp"

class NetLibraryClient : public NetLibrary {
 public:
  static bool SendBlocksRequest(NetClient& sender);
  static bool SendParametersJson(NetClient& sender, const std::string& params);
  static bool SendSchemeJson(NetClient& sender, const std::string& scheme, const std::string& parameters);
  static bool ReceiveBlocksJson(NetClient& receiver, std::string& blocks);
  static bool ReceiveResultsJson(NetClient& receiver, std::string& results);
};
