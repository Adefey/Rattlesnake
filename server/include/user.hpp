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
  User() : block_scheme({}), variables({}) {}
};

#endif
