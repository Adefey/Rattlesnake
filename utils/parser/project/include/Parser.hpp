#pragma once

#include <string>
#include <vector>

class Block {};
class Parameter {};

class Parser {
  static bool ToInt(std::string value, int& result);
  static bool ToDouble(std::string value, double& result);
  static bool ParseBlockFromJsonString(std::string val, Block& result);
  static bool ParseBlocksFromJsonString(std::string val, vector<Block>& result);
  static bool ParseParameterFromJsonString(std::string val, Parameter& result);
  static bool ParseParametersFromJsonString(std::string val, vector<Parameter>& result);
};
