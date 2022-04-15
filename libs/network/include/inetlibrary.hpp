#pragma once

#include <string>

#include "netsocket.hpp"

class INetLibrary {
 public:
  virtual bool SendData(NetSocket, std::string) = 0;
  virtual std::string ReceiveData(NetSocket) = 0;
  virtual ~INetLibrary() = default;
};
