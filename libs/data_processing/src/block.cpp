#include "block.hpp"

#include <utility>

Parameter::Parameter() {
  param_name = "";
  param_value = "";
}

Parameter::Parameter(std::string name, std::string value) {
  param_name = std::move(name);
  param_value = std::move(value);
}

Block::Block() {
  solver_path_ = "";
  name_ = "";
  description_ = "";
  author_name_ = "";
  color_ = -1;
}

void Block::FillSolved(std::vector<Parameter>& solved_vars) {
  solved_vars_.clear();
  for (const auto& param : solved_vars) {
    solved_vars_.emplace_back(param);
  }
}

Block::Block(std::string solver_path, std::vector<Parameter>& given_vars,
             std::vector<Parameter>& solved_vars, std::string name, std::string description,
             std::string author_name, int color) {
  solver_path_ = std::move(solver_path);
  given_vars_ = std::vector<Parameter>(given_vars);
  solved_vars_ = std::vector<Parameter>(solved_vars);
  name_ = std::move(name);
  description_ = std::move(description);
  author_name_ = std::move(author_name);
  color_ = color;
}

std::vector<std::string> Block::GetFieldsNames() {
  std::vector<std::string> result{
      {"solver_path", "given_vars", "solved_vars", "name", "description", "author_name", "color"}};
  return result;
}

std::string Block::GetSolverPath() const {
  return solver_path_;
}

std::vector<Parameter> Block::GetGivenVars() const {
  return given_vars_;
}

std::vector<Parameter> Block::GetSolvedVars() const {
  return solved_vars_;
}

std::string Block::GetName() const {
  return name_;
}

std::string Block::GetDescription() const {
  return description_;
}

std::string Block::GetAuthorName() const {
  return author_name_;
}

int Block::GetColor() const {
  return color_;
}
