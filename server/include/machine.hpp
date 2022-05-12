#include <cstdio>

#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

#include <appinfo.hpp>
#include <block.hpp>
#include <dbhelper.hpp>
#include <netserver.hpp>
#include <parser.hpp>
#include <serializer.hpp>
#include <user.hpp>

#define BUF_SIZE 128

#ifndef MACHINE
#define MACHINE

class Machine {

private:
  User user;
  NetServer net_server;
  std::string ProcessOneBlock(const std::string &launch_string);
  std::string MakeProcessStartString(const std::string &block_name);
  void SyncVariables(std::vector<Parameter> params);

public:
  Machine();
  Machine(const std::string &start_param_scheme,
          const std::string &start_param_vars);
  std::string ProcessAllBlocks();
};

#endif
