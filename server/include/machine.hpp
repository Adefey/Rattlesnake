#include <unistd.h>

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <sstream>
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

#define BUF_SIZE 256

#ifndef MACHINE
#define MACHINE

class Machine {

private:
  User user;
  NetServer net_server;
  std::string ProcessOneBlock(const std::string &launch_string);
  std::string GetParamValueByName(const std::string &name);
  void SetParamValueByName(const std::string &name, const std::string &value);
  bool HasParameter(const std::string &name);
  std::string MakeProcessStartString(const Block &block);
  void SyncVariables(std::vector<Parameter> params);
  std::vector<Parameter> ProcessBlockOutput(const std::string &data,
                                            const Block &block);

public:
  Machine();
  Machine(const std::string &start_param_scheme,
          const std::string &start_param_vars);
  std::string ProcessAllBlocks();
};

#endif
