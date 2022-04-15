#include <string>
#include <vector>

#include <appinfo.hpp>
#include <block.hpp>
#include <dbhelper.hpp>
#include <netserver.hpp>
#include <parser.hpp>
#include <serializer.hpp>
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
