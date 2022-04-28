#include <machine.hpp>

void SyncVariables(std::vector<Parameter>) {}

std::string Machine::ProcessOneBlock(const std::string &launch_string) {}

std::string Machine::MakeProcessStartString(const std::string &block_name) {
  return "";
}

Machine::Machine() {}

Machine::Machine(const std::string &start_param_scheme,
                 const std::string &start_param_vars) {
  user = new User;
  ParseBlocksFromJsonString(start_param_scheme, user.block_scheme);
  ParseParametersFromJsonString(start_param_vars, user.variables);
}

std::string Machine::ProcessAllBlocks() {
  for (int i = 0; i < user.block_scheme.size(); ++i) {
    std::string start_string =
        MakeProcessStartString(user.block_scheme[i].name);
    std::string block_output = ProcessOneBlock(start_string);
    std::vector<Parameter> block_output_vector;
    ParseParametersFromJsonString(block_output, block_output_vector);
    SyncVariables(block_output_vector);
  }
  std::string result = ToJsonString(user.variables);
  return result;
}

Machine::~Machine() { delete user }
