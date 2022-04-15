#include "parser.hpp"

bool Parser::ToInt(std::string value, int& result) {}

bool Parser::ToDouble(std::string value, double& result) {}

bool Parser::ParseParameterFromJsonString(std::string val, Parameter& result) {}

bool Parser::ParseParametersFromJsonString(std::string val, std::vector<Parameter>& result) {}

bool Parser::ParseBlockFromJsonString(std::string val, Block& result) {}

bool Parser::ParseBlocksFromJsonString(std::string val, std::vector<Block>& result) {}
