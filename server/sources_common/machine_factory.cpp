#include <machine_factory.hpp>

MachineFactory::MachineFactory() {
  char cwd[1024];
  getcwd(cwd, sizeof(cwd));
  pwd = std::string(cwd);
  std::string cmd =
      " docker run -v " + pwd + ":/home -w /home/ -t -i ubuntu uname -a";
  FILE *dummy;
  //  Процесс создается и закрывается. Это надо чтобы убунту скачалась, если ее
  //  нет
  if (!(dummy = popen(cmd.c_str(), "r"))) {
    throw std::runtime_error("Cannot make process");
  }
  if (pclose(dummy)) {
    throw std::runtime_error("Cannot start");
  }
}

std::string MachineFactory::MakeStartString(const User &user) {

  std::string result =
      "docker run -v " + pwd +
      ":/home -w /home/ -t -i ubuntu ./RattlesnakeMachine " +
      Serializer::ToJsonString((std::vector<Block> &)user.block_scheme) + " " +
      Serializer::ToJsonString((std::vector<Parameter> &)user.variables);
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
    throw std::runtime_error("Cannot start");
  }
  return result;
}
