#include <vector>
#include <string>

#ifndef BLOCK
#define BLOCK

struct Parameter {
  std::string var_name;
  std::string var_value;
  Parameter(std::string name, std::string value)
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
  void FillSolved(std::vector<Parameter>);
};

#endif
