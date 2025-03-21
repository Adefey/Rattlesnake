#pragma once

#include "netlibrary.hpp"
#include "netserver.hpp"

class NetLibraryServer : public NetLibrary {
 public:
  static bool SendBlocksJson(NetSocket& receiver, const std::string& blocks);
  static bool SendResultsJson(NetSocket& receiver, const std::string& results);
  static bool ReceiveMessage(NetSocket& receiver, NetMessage& msg);
};
