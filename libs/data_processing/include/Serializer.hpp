#pragma once

#include <string>
#include <vector>

#include "Block.hpp"

class Serializer {
  static std::string ToString(int value);
  static std::string ToString(double value);
  static std::string ToJsonString(Block value);
  static std::string ToJsonString(std::vector<Block> value);
  static std::string ToJsonString(Parameter value);
  static std::string ToJsonString(std::vector<Parameter> value);
};
