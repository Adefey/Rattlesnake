#include <gtest/gtest.h>

#include <string>

#include "parser.hpp"

TEST(parser_tests, string_to_int_test) {
  std::string empty_string;
  int int_result = 0;
  EXPECT_FALSE(Parser::ToInt(empty_string, int_result));

  std::string incorrect_string = "123m,z";
  EXPECT_FALSE(Parser::ToInt(incorrect_string, int_result));

  incorrect_string = "0131231231231231231";
  EXPECT_FALSE(Parser::ToInt(incorrect_string, int_result));

  incorrect_string = "1.42";
  EXPECT_FALSE(Parser::ToInt(incorrect_string, int_result));

  std::string correct_string = "1582";
  EXPECT_TRUE(Parser::ToInt(correct_string, int_result));
  EXPECT_EQ(int_result, 1582);

  correct_string = "0";
  EXPECT_TRUE(Parser::ToInt(correct_string, int_result));
  EXPECT_EQ(int_result, 0);

  correct_string = "-171582";
  EXPECT_TRUE(Parser::ToInt(correct_string, int_result));
  EXPECT_EQ(int_result, -171582);
}

TEST(parser_tests, string_to_double_test) {
  std::string empty_string;
  double double_result = 0;
  EXPECT_FALSE(Parser::ToDouble(empty_string, double_result));

  std::string incorrect_string = "123m,z";
  EXPECT_FALSE(Parser::ToDouble(incorrect_string, double_result));

  incorrect_string = "1..42";
  EXPECT_FALSE(Parser::ToDouble(incorrect_string, double_result));

  std::string correct_string = "1582";
  EXPECT_TRUE(Parser::ToDouble(correct_string, double_result));
  EXPECT_EQ(double_result, 1582);

  correct_string = "0";
  EXPECT_TRUE(Parser::ToDouble(correct_string, double_result));
  EXPECT_EQ(double_result, 0);

  correct_string = "-171582.88";
  EXPECT_TRUE(Parser::ToDouble(correct_string, double_result));
  EXPECT_EQ(double_result, -171582.88);
}

TEST(parser_tests, parse_param) {
  Parameter param;

  std::string incorrect_string;
  EXPECT_FALSE(Parser::ParseParameterFromJsonString(incorrect_string, param));

  std::string correct_string = R"({"key":"value"})";
  EXPECT_TRUE(Parser::ParseParameterFromJsonString(correct_string, param));
  EXPECT_EQ(param.param_name, "key");
  EXPECT_EQ(param.param_value, "value");

  correct_string = "{}";
  EXPECT_TRUE(Parser::ParseParameterFromJsonString(incorrect_string, param));

  incorrect_string = R"({"key";"value"})";
  EXPECT_FALSE(Parser::ParseParameterFromJsonString(incorrect_string, param));
}

TEST(parser_tests, parse_params) {
  std::vector<Parameter> params;

  std::string incorrect_string;
  EXPECT_FALSE(Parser::ParseParametersFromJsonString(incorrect_string, params));

  params.clear();
  std::string correct_string = "values:[]";
  EXPECT_TRUE(Parser::ParseParametersFromJsonString(correct_string, params));
  EXPECT_TRUE(params.empty());

  incorrect_string = R"({values:[{"key";"value"},{"key";"value"},{"key";"value"}]})";
  EXPECT_FALSE(Parser::ParseParametersFromJsonString(incorrect_string, params));

  params.clear();
  correct_string = R"([{"key":"value"},{"key":"value"},{"key":"value"}])";
  EXPECT_TRUE(Parser::ParseParametersFromJsonString(correct_string, params));
  ASSERT_EQ(params.size(), 3);
  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(params[i].param_name, "key");
    EXPECT_EQ(params[i].param_value, "value");
  }
}

TEST(parser_tests, parse_block) {
  Block block;

  std::string incorrect_string;
  EXPECT_FALSE(Parser::ParseBlockFromJsonString(incorrect_string, block));

  incorrect_string = "{}";
  EXPECT_FALSE(Parser::ParseBlockFromJsonString(incorrect_string, block));

  incorrect_string = R"({"key";"value"})";
  EXPECT_FALSE(Parser::ParseBlockFromJsonString(incorrect_string, block));

  std::string correct_string =
      "{\"solver_path\":\"path\",\"given_vars\":[{\"key\":\"value\"}],\"solved_vars\":[{}],"
      "\"name\":\"block_name\",\"description\":\"block_descr\",\"author_name\":\"block_author_"
      "name\",\"color\":\"11\"}";
  EXPECT_TRUE(Parser::ParseBlockFromJsonString(correct_string, block));

  EXPECT_EQ(block.GetSolverPath(), "path");

  std::vector<Parameter> vars = block.GetGivenVars();
  ASSERT_EQ(vars.size(), 1);
  EXPECT_EQ(vars[0].param_name, "key");
  EXPECT_EQ(vars[0].param_value, "value");

  vars.clear();
  vars = block.GetSolvedVars();
  EXPECT_TRUE(vars.empty());

  EXPECT_EQ(block.GetName(), "block_name");
  EXPECT_EQ(block.GetDescription(), "block_descr");
  EXPECT_EQ(block.GetAuthorName(), "block_author_name");
  EXPECT_EQ(block.GetColor(), 11);
}

TEST(parser_tests, parse_blocks) {
  std::vector<Block> blocks;

  std::string incorrect_string;
  EXPECT_FALSE(Parser::ParseBlocksFromJsonString(incorrect_string, blocks));

  incorrect_string = "{}";
  EXPECT_FALSE(Parser::ParseBlocksFromJsonString(incorrect_string, blocks));

  std::string correct_string =
      "{\"solver_path\":\"path\",\"given_vars\":[{\"key\":\"value\"}],\"solved_vars\":[{}],"
      "\"name\":\"block_name\",\"description\":\"block_descr\",\"author_name\":\"block_author_"
      "name\",\"color\":\"11\"}";

  blocks.clear();
  EXPECT_TRUE(Parser::ParseBlocksFromJsonString(incorrect_string, blocks));
  ASSERT_EQ(blocks.size(), 1);

  EXPECT_EQ(blocks[0].GetSolverPath(), "path");

  std::vector<Parameter> vars = blocks[0].GetGivenVars();
  ASSERT_EQ(vars.size(), 1);
  EXPECT_EQ(vars[0].param_name, "key");
  EXPECT_EQ(vars[0].param_value, "value");

  vars.clear();
  vars = blocks[0].GetSolvedVars();
  EXPECT_TRUE(vars.empty());

  EXPECT_EQ(blocks[0].GetName(), "block_name");
  EXPECT_EQ(blocks[0].GetDescription(), "block_descr");
  EXPECT_EQ(blocks[0].GetAuthorName(), "block_author_name");
  EXPECT_EQ(blocks[0].GetColor(), 11);
}
