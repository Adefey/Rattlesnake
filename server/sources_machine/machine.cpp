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

std::string Machine::MakeProcessStartString(const Block &block) {
  std::string result = "python3 ";
  result += block.GetSolverPath();
  std::vector<Parameter> given_vars = block.GetGivenVars();
  for (auto variable : given_vars) {
    //В переменных внутри блока пусто, если ожидается, что туда значения будут
    //загружаться из user.variables по имени параметра. Если там не пусто,
    //значит там лежит имя другого параметра, по которому тоже из user.variables
    //надо взять значения. Типа переопределение имени параметра чтобы разрешать
    //конфликты имен
    if (variable.param_value == "" || variable.param_value == "0") {
      //Если это - пустое, значит надо обратиться к user.variables, где лежат
      //все переменные
      result += " " + GetParamValueByName(variable.param_name);
    } else {
      //Иначе - там лежит имя переменной для связывания
      result += " " + GetParamValueByName(variable.param_value);
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
    std::string start_string = MakeProcessStartString(user.block_scheme[i]);
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
