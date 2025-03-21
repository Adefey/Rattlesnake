#pragma once

#include <string>
#include <vector>

struct Parameter {
  Parameter();
  Parameter(std::string name, std::string value);

  std::string param_name;
  std::string param_value;
};

struct Block {
  Block();
  Block(std::string solver_path, std::vector<Parameter>& given_vars,
        std::vector<Parameter>& solved_vars, std::string name, std::string description,
        std::string author_name, int color);

  static std::vector<std::string> GetFieldsNames();

  std::string solver_path;
  std::vector<Parameter> given_vars;
  std::vector<Parameter> solved_vars;
  std::string name;
  std::string description;
  std::string author_name;
  int color;
};
