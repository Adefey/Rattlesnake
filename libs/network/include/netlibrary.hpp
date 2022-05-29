#pragma once

#include <string>

#include "netmessage.hpp"
#include "netsocket.hpp"

class NetLibrary {
 public:
  static bool SendData(NetSocket& socket, const NetMessage& message);
  static bool ReceiveData(NetSocket& socket, NetMessage& msg);

 private:
  static const size_t base_string_length = 9;
  static bool SendString(NetSocket& socket, const std::string& str);
  static bool ReceiveString(NetSocket& socket, std::string& str, size_t str_size);
};
