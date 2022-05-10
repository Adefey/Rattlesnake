#pragma once

#include <string>
#include <vector>

struct Parameter {
  Parameter();
  Parameter(std::string name, std::string value);

  std::string param_name;
  std::string param_value;
};

class Block {
 public:
  Block();
  Block(std::string solver_path, std::vector<Parameter>& given_vars,
        std::vector<Parameter>& solved_vars, std::string name, std::string description,
        std::string author_name, int color);

  static std::vector<std::string> GetFieldsNames();

  std::string GetSolverPath() const;

  std::vector<Parameter> GetGivenVars() const;

  std::vector<Parameter> GetSolvedVars() const;

  std::string GetName() const;

  std::string GetDescription() const;

  std::string GetAuthorName() const;

  int GetColor() const;

  void FillSolved(std::vector<Parameter>& solved_vars);

 private:
  std::string solver_path_;
  std::vector<Parameter> given_vars_;
  std::vector<Parameter> solved_vars_;
  std::string name_;
  std::string description_;
  std::string author_name_;
  int color_;
};
