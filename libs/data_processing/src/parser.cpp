#include "parser.hpp"

bool Parser::ToInt(std::string value, int& result) {
  return false;
}

bool Parser::ToDouble(std::string value, double& result) {
  return false;
}

bool Parser::ParseParameterFromJsonString(std::string val, Parameter& result) {
  return false;
}

bool Parser::ParseParametersFromJsonString(std::string val, std::vector<Parameter>& result) {
  return false;
}

bool Parser::ParseBlockFromJsonString(std::string val, Block& result) {
  return false;
}

bool Parser::ParseBlocksFromJsonString(std::string val, std::vector<Block>& result) {
  return false;
}
