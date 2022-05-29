#pragma once

#include <string>
#include <vector>

#include "block.hpp"

class Serializer {
 public:
  static std::string ToString(int value);
  static std::string ToString(double value);
  static std::string ToJsonString(const Block& value);
  static std::string ToJsonString(const std::vector<Block>& values);
  static std::string ToJsonString(const Parameter& value);
  static std::string ToJsonString(const std::vector<Parameter>& values);
};
