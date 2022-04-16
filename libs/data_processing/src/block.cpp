#include "block.hpp"

Parameter::Parameter() {}

Parameter::Parameter(std::string name, std::string value) {}

Block::Block() {}

void Block::FillSolved(std::vector<Parameter>& solved_vars) {}

Block::Block(std::string solver_path, std::vector<Parameter>& given_vars,
             std::vector<Parameter>& solved_vars, std::string name, std::string description,
             std::string author_name, int color) {}

std::vector<std::string> Block::GetFieldsNames() const {
  return std::vector<std::string>();
}

std::string Block::GetSolverPath() const {
  return "";
}

std::vector<Parameter> Block::GetGivenVars() const {
  return std::vector<Parameter>();
}

std::vector<Parameter> Block::GetSolvedVars() const {
  return std::vector<Parameter>();
}

std::string Block::GetName() const {
  return "";
}

std::string Block::GetDescription() const {
  return "";
}

std::string Block::GetAuthorName() const {
  return "";
}

int Block::GetColor() const {
  return 0;
}
