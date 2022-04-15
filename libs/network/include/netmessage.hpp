#pragma once

class NetMessage {
 public:
  int message_length;
  std::string message_type;
  std::string content;
};
