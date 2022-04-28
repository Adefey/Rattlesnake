#include <string>
#include <vector>

#include <block.hpp>
#include <netserver.hpp>
#include <parser.hpp>
#include <serializer.hpp>

#ifndef USER
#define USER

struct User {
  NetSocket user_socket;
  std::vector<Block> block_scheme;
  std::vector<Parameter> variables;
  User(NetSocket socket, const std::vector<Block> &scheme,
       const std::vector<Parameter> &vars)
      : user_socket(socket), block_scheme(scheme), variables(vars) {}
  User() : block_scheme({}), variables({}) {}
};

#endif
