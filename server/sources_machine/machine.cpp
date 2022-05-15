#include <machine.hpp>

void Machine::SyncVariables(std::vector<Parameter> params) {
  for (auto element : params) {
    bool asigned = false;
    for (size_t i = 0; i < user.variables.size(); ++i) {
      if (user.variables[i].param_name == element.param_name) {
        user.variables[i].param_value = element.param_value;
        asigned = true;
        break;
      }
    }
    if (!asigned) {
      user.variables.push_back(element);
    }
  }
}

std::string Machine::ProcessOneBlock(const std::string &launch_string) {
  std::string result = "";
  char buf[BUF_SIZE];
  FILE *process_output;

  if (!(process_output = popen(launch_string.c_str(), "r"))) {
    throw std::runtime_error("Unable to open process");
  }

  while (fgets(buf, BUF_SIZE, process_output)) {
    result += buf;
  }

  if (pclose(process_output)) {
    throw std::runtime_error("No such block or it threw error");
  }

  return result;
}

std::string Machine::MakeProcessStartString(const std::string &block_name) {
  std::string result = "python3 ";
  for (size_t i = 0; i < user.block_scheme.size(); ++i) {
    if (user.block_scheme[i].GetName() == block_name) {
      result += user.block_scheme[i].GetSolverPath();
      std::vector<Parameter> given_vars = user.block_scheme[i].GetGivenVars();
      for (auto variable : given_vars) {
        for (auto existing_variable : user.variables) {
          if (variable.param_name == existing_variable.param_name) {
            result += " " + existing_variable.param_value;
          }
        }
      }
      break;
    }
  }
  return result;
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
    std::string block_output = "";
    try {
      block_output = ProcessOneBlock(start_string);
    } catch (std::runtime_error const &) {
      return "SCHEME FAILED";
    }
    std::vector<Parameter> block_output_vector = {};

    Parser::ParseParametersFromJsonString(block_output, block_output_vector);
    SyncVariables(block_output_vector);
  }
  std::string result = Serializer::ToJsonString(user.variables);
  return result;
}
