#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <block.hpp>
#include <parser.hpp>
#include <serializer.hpp>
#include <user.hpp>

#define BUF_SIZE 128

#ifndef MACHINEFACTORY
#define MACHINEFACTORY

class MachineFactory {

private:
  std::string MakeStartString(const User &user);
  std::string pwd;

public:
  MachineFactory();
  std::string ProcessMachine(const User &user);
  //запускает в докере
};

#endif
