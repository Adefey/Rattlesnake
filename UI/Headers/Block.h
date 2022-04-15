#include <string>
#include <vector>

#ifndef BLOCK
#define BLOCK

struct Parameter {
  std::string var_name;
  std::string var_value;
  Parameter(const std::string &name, const std::string &value)
      : var_name(name), var_value(value) {}
};

class Block {

private:
  std::string solver_path;
  std::vector<Parameter> given_vars;
  std::vector<Parameter> solved_vars;
  std::string name;
  std::string description;
  std::string author_name;
  int color;

public:
  Block();
  void FillSolved(const std::vector<Parameter>);
};

#endif