#pragma once

#include <string>

class NetMessage {
 public:
  NetMessage() = default;
  int message_length;
  std::string message_type;
  std::string content;
};
