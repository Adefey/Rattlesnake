#pragma once

#include <string>
#include <vector>

#include "block.hpp"

class Parser {
 public:
  static bool ToInt(const std::string& value, int& result);
  static bool ToDouble(const std::string& value, double& result);
  static bool ParseBlockFromJsonString(const std::string& val, Block& result);
  static bool ParseBlocksFromJsonString(const std::string& val, std::vector<Block>& result);
  static bool ParseParameterFromJsonString(const std::string& val, Parameter& result);
  static bool ParseParametersFromJsonString(const std::string& val, std::vector<Parameter>& result);
};
