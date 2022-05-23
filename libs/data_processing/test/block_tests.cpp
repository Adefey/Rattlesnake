#include <gtest/gtest.h>

#include <string>

#include "block.hpp"

TEST(block_tests, get_fields_names_test) {
  Block empty_block;
  std::vector<std::string> block_fields = Block::GetFieldsNames();

  std::vector<std::string> block_fields_true;
  block_fields_true.emplace_back("solver_path");
  block_fields_true.emplace_back("given_vars");
  block_fields_true.emplace_back("solved_vars");
  block_fields_true.emplace_back("name");
  block_fields_true.emplace_back("description");
  block_fields_true.emplace_back("author_name");
  block_fields_true.emplace_back("color");

  ASSERT_EQ(block_fields.size(), block_fields_true.size());

  bool is_equal = true;
  for (size_t i = 0; i < block_fields_true.size(); ++i) {
    is_equal &= (block_fields_true[i] == block_fields[i]);
  }
  EXPECT_TRUE(is_equal);
}

TEST(block_tests, empty_block_fields_test) {
  Block empty_block;

  std::string solver_path = empty_block.solver_path;
  std::string empty_string;
  EXPECT_EQ(solver_path, empty_string);

  std::string name = empty_block.name;
  EXPECT_EQ(name, empty_string);

  std::string description = empty_block.description;
  EXPECT_EQ(description, empty_string);

  std::string author_name = empty_block.author_name;
  EXPECT_EQ(author_name, empty_string);

  int color = empty_block.color;
  EXPECT_EQ(color, -1);

  std::vector<Parameter> params = empty_block.solved_vars;
  EXPECT_TRUE(params.empty());

  params = empty_block.given_vars;
  EXPECT_TRUE(params.empty());
}

TEST(block_tests, fill_solved_params_test) {
  Block empty_block;

  std::vector<Parameter> params;
  params.emplace_back(Parameter());
  params.emplace_back(Parameter());
  params.emplace_back(Parameter());

  empty_block.solved_vars.clear();
  empty_block.solved_vars = params;

  std::vector<Parameter> params_from_block = empty_block.solved_vars;

  ASSERT_EQ(params_from_block.size(), params.size());

  bool is_equal = true;
  for (size_t i = 0; i < params.size(); ++i) {
    is_equal &= (params[i].param_name == params_from_block[i].param_name &&
                 params[i].param_value == params_from_block[i].param_value);
  }
  EXPECT_TRUE(is_equal);
}