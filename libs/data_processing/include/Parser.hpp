#pragma once

#include <string>
#include <vector>

#include "Block.hpp"

class Parser {
  static bool ToInt(std::string value, int& result);
  static bool ToDouble(std::string value, double& result);
  static bool ParseBlockFromJsonString(std::string val, Block& result);
  static bool ParseBlocksFromJsonString(std::string val, std::vector<Block>& result);
  static bool ParseParameterFromJsonString(std::string val, Parameter& result);
  static bool ParseParametersFromJsonString(std::string val, std::vector<Parameter>& result);
};
