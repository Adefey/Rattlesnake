#include <gtest/gtest.h>

#include <string>

#include "parser.hpp"
#include "serializer.hpp"

TEST(serializer_tests, from_int_to_string) {
  int val = 0;
  std::string result = Serializer::ToString(val);
  EXPECT_EQ(result, "0");

  val = -12345;
  result = Serializer::ToString(val);
  EXPECT_EQ(result, "-12345");

  val = 12345678;
  result = Serializer::ToString(val);
  EXPECT_EQ(result, "12345678");
}

TEST(serializer_tests, from_double_to_string) {
  double val = 0;
  std::string result = Serializer::ToString(val);
  EXPECT_EQ(std::stod(result), 0);

  val = 123.456;
  result = Serializer::ToString(val);
  EXPECT_EQ(std::stod(result), 123.456);

  val = -9151.381;
  result = Serializer::ToString(val);
  EXPECT_EQ(std::stod(result), -9151.381);
}

TEST(serializer_tests, from_param_to_string) {
  Parameter empty_param;
  std::string result = Serializer::ToJsonString(empty_param);
  EXPECT_EQ(result, R"({"param_name":"","param_value":""})");

  Parameter param("key", "value");
  result = Serializer::ToJsonString(param);
  std::string expected_result = R"({"param_name":"key","param_value":"value"})";
  EXPECT_EQ(result, expected_result);
}

TEST(serializer_tests, from_params_to_string) {
  std::vector<Parameter> params;
  std::string result = Serializer::ToJsonString(params);
  EXPECT_EQ(result, R"([])");

  params.push_back(Parameter("key", "value"));
  result = Serializer::ToJsonString(params);
  EXPECT_EQ(result, R"([{"param_name":"key","param_value":"value"}])");

  params.push_back(Parameter("name", "val"));
  result = Serializer::ToJsonString(params);
  EXPECT_EQ(
      result,
      R"([{"param_name":"key","param_value":"value"},{"param_name":"name","param_value":"val"}])");
}

TEST(serializer_tests, from_block_to_string) {
  Block empty_block, result_block;
  std::string result = Serializer::ToJsonString(empty_block);
  bool res = Parser::ParseBlockFromJsonString(result, result_block);
  ASSERT_TRUE(res);

  EXPECT_EQ(empty_block.color, result_block.color);
  EXPECT_EQ(empty_block.author_name, result_block.author_name);
  EXPECT_EQ(empty_block.description, result_block.description);
  EXPECT_EQ(empty_block.name, result_block.name);

  std::vector<Parameter> empty_params;
  Block block("path", empty_params, empty_params, "block_name", "block_descr", "block_author_name",
              11);

  result = Serializer::ToJsonString(block);
  res = Parser::ParseBlockFromJsonString(result, result_block);

  ASSERT_TRUE(res);
  EXPECT_EQ(block.color, result_block.color);
  EXPECT_EQ(block.author_name, result_block.author_name);
  EXPECT_EQ(block.description, result_block.description);
  EXPECT_EQ(block.name, result_block.name);
}

TEST(serializer_tests, from_blocks_to_string) {
  std::vector<Block> blocks;
  std::string result = Serializer::ToJsonString(blocks);
  EXPECT_EQ(result, "[]");

  std::vector<Parameter> empty_params;
  Block block("path", empty_params, empty_params, "block_name", "block_descr", "block_author_name",
              11);
  blocks.push_back(block);
  blocks.push_back(block);
  blocks.push_back(block);

  result = Serializer::ToJsonString(blocks);
  std::vector<Block> result_blocks;
  bool res = Parser::ParseBlocksFromJsonString(result, result_blocks);

  ASSERT_TRUE(res);
  ASSERT_EQ(result_blocks.size(), blocks.size());

  for (size_t i = 0; i < blocks.size(); ++i) {
    EXPECT_EQ(blocks[i].color, result_blocks[i].color);
    EXPECT_EQ(blocks[i].author_name, result_blocks[i].author_name);
    EXPECT_EQ(blocks[i].description, result_blocks[i].description);
    EXPECT_EQ(blocks[i].name, result_blocks[i].name);
  }
}
