#pragma once

#include <string>
#include <vector>

struct Parameter {
  std::string var_name;
  std::string var_value;
  Parameter(std::string name, std::string value) : var_name(name), var_value(value) {}
};

class Block {
 public:
  void FillSolved(std::vector<Parameter>);
  Block();
  void print_any();

 private:
  std::string solver_path_;
  std::vector<Parameter> given_vars_;
  std::vector<Parameter> solved_vars_;
  std::string name_;
  std::string description_;
  std::string author_name_;
  int color_;
};
