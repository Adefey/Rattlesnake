#include <memory>
#include <string>
#include <vector>

#include <block.hpp>
#include <parser.hpp>
#include <serializer.hpp>
#include <user.hpp>

#ifndef MACHINEFACTORY
#define MACHINEFACTORY

class MachineFactory {

private:
  std::vector<std::string> machines_online;
  std::string MakeStartString(std::unique_ptr<User> user);
  void LaunchProcess(const std::string &launch_string);

public:
  MachineFactory();
  std::string ProcessMachine(std::unique_ptr<User> user);
  //запускает в докере
};

#endif
