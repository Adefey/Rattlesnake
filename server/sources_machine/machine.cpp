#include <machine.hpp>

void Machine::SyncVariables(std::vector<Parameter>) {}

std::string Machine::ProcessOneBlock(const std::string &launch_string) {
  return "";
}

std::string Machine::MakeProcessStartString(const std::string &block_name) {
  return "";
}

Machine::Machine() {}

Machine::Machine(const std::string &start_param_scheme,
                 const std::string &start_param_vars) {
  Parser::ParseBlocksFromJsonString(start_param_scheme, user.block_scheme);
  Parser::ParseParametersFromJsonString(start_param_vars, user.variables);
}

std::string Machine::ProcessAllBlocks() {
  for (size_t i = 0; i < user.block_scheme.size(); ++i) {
    std::string start_string =
        MakeProcessStartString(user.block_scheme[i].GetName());
    std::string block_output = ProcessOneBlock(start_string);
    std::vector<Parameter> block_output_vector;
    Parser::ParseParametersFromJsonString(block_output, block_output_vector);
    SyncVariables(block_output_vector);
  }
  std::string result = "";
  Serializer::ToJsonString(result, user.variables);
  return result;
}
