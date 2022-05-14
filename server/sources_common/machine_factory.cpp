#include <machine_factory.hpp>

MachineFactory::MachineFactory() {}

std::string MachineFactory::MakeStartString(const User &user) {

  std::string result =
      "./RattlesnakeMachine \'" +
      Serializer::ToJsonString((std::vector<Block> &)user.block_scheme) +
      "\' \'" +
      Serializer::ToJsonString((std::vector<Parameter> &)user.variables) + '\'';
  return result;
}

std::string MachineFactory::ProcessMachine(const User &user) {
  std::string start_string = MakeStartString(user);
  std::string result = "";
  char buf[BUF_SIZE];
  FILE *process_output;

  if (!(process_output = popen(start_string.c_str(), "r"))) {
    throw std::runtime_error("Cannot make process");
  }

  while (fgets(buf, BUF_SIZE, process_output)) {
    result += buf;
  }

  if (pclose(process_output)) {
    throw std::runtime_error("Cannot start or ended bad");
  }
  return result;
}
