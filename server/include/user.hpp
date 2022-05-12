#include <string>
#include <vector>

#include <block.hpp>
#include <netserver.hpp>
#include <parser.hpp>
#include <serializer.hpp>

#ifndef USER
#define USER

struct User {
  std::string name;
  NetSocket user_socket;
  std::vector<Block> block_scheme;
  std::vector<Parameter> variables;
  User(const std::string &username, NetSocket socket,
       const std::vector<Block> &scheme, const std::vector<Parameter> &vars)
      : name(username), user_socket(socket), block_scheme(scheme),
        variables(vars) {}
  User() : block_scheme({}), variables({}) {}
};

#endif
