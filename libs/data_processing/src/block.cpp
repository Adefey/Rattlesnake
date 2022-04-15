#include "block.hpp"

Parameter::Parameter() {}

Parameter::Parameter(std::string name, std::string value) {}

Block::Block() {}

void Block::FillSolved(std::vector<Parameter>& solved_vars) {}

Block::Block(std::string solver_path, std::vector<Parameter>& given_vars,
             std::vector<Parameter>& solved_vars, std::string name, std::string description,
             std::string author_name, int color) {}

std::vector<std::string> Block::GetFieldsNames() const {}

std::string Block::GetSolverPath() const {}

std::vector<Parameter> Block::GetGivenVars() const {}

std::vector<Parameter> Block::GetSolvedVars() const {}

std::string Block::GetName() const {}

std::string Block::GetDescription() const {}

std::string Block::GetAuthorName() const {}

int Block::GetColor() const {}
