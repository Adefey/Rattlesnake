#include <string>
#include <vector>

#include <block.hpp>
#include <dbhelper.hpp>
#include <user.hpp>

#ifndef MACHINE
#define MACHINE

class Machine {

private:
  User user;
  void ProcessOneBlock(const std::string &launch_string);
  std::string MakeProcessStartString(const std::string &block_name);

public:
  Machine();
  Machine(const std::string &start_params);
  std::string ProcessAllBlocks();
};

#endif
