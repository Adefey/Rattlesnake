#include <machine_factory.hpp>

MachineFactory::MachineFactory() {}

std::string MachineFactory::ProcessMachine(std::unique_ptr<User> user) {
  //запускает в докере и сразу возвращает результат
  return "";
}
std::string MachineFactory::MakeStartString(std::unique_ptr<User> user) {
  return "";
}

void MachineFactory::LaunchProcess(const std::string &launch_string) {}
