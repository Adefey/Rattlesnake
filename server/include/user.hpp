#include <string>
#include <vector>

#include <block.hpp>
#include <netserver.hpp>

#ifndef USER
#define USER

struct User {
  NetSocket user_socket;
  std::vector<std::string> block_scheme;
  std::vector<Parameter> variables;
  User(NetSocket socket, const std::vector<std::string> &scheme,
       const std::vector<Parameter> &vars)
      : user_socket(socket), block_scheme(scheme), variables(vars) {}
  User() : user_socket(0), block_scheme({}), variables({}) {}
};

#endif
