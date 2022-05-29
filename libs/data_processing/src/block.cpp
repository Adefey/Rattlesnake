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
  solver_path = "";
  name = "";
  description = "";
  author_name = "";
  color = -1;
}

Block::Block(std::string solver_path_param, std::vector<Parameter>& given_vars_param,
             std::vector<Parameter>& solved_vars_param, std::string name_param, std::string description_param,
             std::string author_name_param, int color_param) {
  solver_path = std::move(solver_path_param);
  given_vars = std::vector<Parameter>(given_vars_param);
  solved_vars = std::vector<Parameter>(solved_vars_param);
  name = std::move(name_param);
  description = std::move(description_param);
  author_name = std::move(author_name_param);
  color = color_param;
}

std::vector<std::string> Block::GetFieldsNames() {
  std::vector<std::string> result{
      {"solver_path", "given_vars", "solved_vars", "name", "description", "author_name", "color"}};
  return result;
}
