#include <block.hpp>
#include <netserver.hpp>

#ifndef USER
#define USER

struct User {
  NetSocket user_socket;
  std::vector<std::string> block_scheme;
  std::vector<Parameter> variables;
  User(NetSocket socket, std::vector<std::string> scheme,
       std::vector<Parameter> vars)
      : user_socket(socket), block_scheme(scheme), variables(vars) {}
};

#endif
