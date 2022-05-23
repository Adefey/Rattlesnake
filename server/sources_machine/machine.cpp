#include <machine.hpp>

bool Machine::HasParameter(const std::string &name) {
  for (size_t i = 0; i < user.variables.size(); ++i) {
    if (user.variables[i].param_name == name) {
      return true;
    }
  }
  return false;
}

std::string Machine::GetParamValueByName(const std::string &name) {
  for (size_t i = 0; i < user.variables.size(); ++i) {
    if (user.variables[i].param_name == name) {
      return user.variables[i].param_value;
    }
  }
  return "";
}

void Machine::SetParamValueByName(const std::string &name,
                                  const std::string &value) {
  for (size_t i = 0; i < user.variables.size(); ++i) {
    if (user.variables[i].param_name == name) {
      user.variables[i].param_value = value;
      return;
    }
  }
}

void Machine::SyncVariables(std::vector<Parameter> params) {
  for (auto element : params) {
    if (HasParameter(element.param_name)) {
      SetParamValueByName(element.param_name, element.param_value);
    } else {
      user.variables.push_back(element);
    }
  }
}

std::string Machine::ProcessOneBlock(const std::string &launch_string) {
  std::string result = "";
  char buf[BUF_SIZE];
  FILE *process_output;

  if (!(process_output = popen(launch_string.c_str(), "r"))) {
    throw std::runtime_error("Unable to open process (Block)");
  }

  while (fgets(buf, BUF_SIZE, process_output)) {
    result += buf;
  }

  if (pclose(process_output)) {
    throw std::runtime_error("Block exited with error");
  }

  return result;
}

std::string Machine::MakeProcessStartString(const Block &block) {
  std::string result = "python3 ";
  result += block.solver_path;
  std::vector<Parameter> given_vars = block.given_vars;
  for (auto variable : given_vars) {
    result += " " + GetParamValueByName(variable.param_name);
  }
  return result;
}

std::vector<Parameter> Machine::ProcessBlockOutput(const std::string &data,
                                                   const Block &block) {
  //Этот метод по выводу блока составляет массив именованных переменных. Я
  //отказался от вывода из питона json-строки, потому что во-первых эту строку
  //надо составлять вручную на питоне и это костыльно, во вторых, для разрешения
  //конфликтов имен мы можем менять в блоке имена входных и выходных переменных,
  //поэтому питон возвращает просто какие-то значения и они записываются в
  //массив переменных по именам, указанных в block.solved_vars
  std::vector<Parameter> vars = {};
  std::vector<Parameter> solved_vars = block.solved_vars;
  std::vector<std::string> strings = {};
  std::stringstream ss(data);
  std::string tmp = "";
  while (getline(ss, tmp, ' ')) {
    strings.push_back(tmp);
  }
  for (size_t i = 0; i < solved_vars.size(); ++i) {
    vars.push_back(Parameter(solved_vars[i].param_name, strings[i]));
  }
  return vars;
}

Machine::Machine() {}

Machine::Machine(const std::string &start_param_scheme,
                 const std::string &start_param_vars) {
  Parser::ParseBlocksFromJsonString(start_param_scheme, user.block_scheme);
  Parser::ParseParametersFromJsonString(start_param_vars, user.variables);
}

std::string Machine::ProcessAllBlocks() {
  for (size_t i = 0; i < user.block_scheme.size(); ++i) {
    std::string start_string = MakeProcessStartString(user.block_scheme[i]);
    std::string block_output = "";
    block_output = ProcessOneBlock(start_string);
    std::vector<Parameter> block_output_vector =
        ProcessBlockOutput(block_output, user.block_scheme[i]);
    SyncVariables(block_output_vector);
  }
  std::string result = Serializer::ToJsonString(user.variables);
  return result;
}
