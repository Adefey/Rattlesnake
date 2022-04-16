#include <gtest/gtest.h>

#include <string>

#include "serializer.hpp"

/*
 #include "serializer.hpp"

std::string Serializer::ToString(int value) {
 return "";
}

std::string Serializer::ToString(double value) {
 return "";
}

std::string Serializer::ToJsonString(Block value) {
 return "";
}

std::string Serializer::ToJsonString(Parameter value) {
 return "";
}

std::string Serializer::ToJsonString(std::vector<Block> value) {
 return "";
}

std::string Serializer::ToJsonString(std::vector<Parameter> value) {
 return "";
}

 */

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
  EXPECT_EQ(result, "0");

  val = 123.456;
  result = Serializer::ToString(val);
  EXPECT_EQ(result, "123.456");

  val = -9151.381;
  result = Serializer::ToString(val);
  EXPECT_EQ(result, "-9151.381");
}

TEST(serializer_tests, from_param_to_string) {
  Parameter empty_param;
  std::string result = Serializer::ToJsonString(empty_param);
  EXPECT_EQ(result, "{}");

  Parameter param("key", "value");
  result = Serializer::ToJsonString(param);
  std::string expected_result = R"({"key":"value"})";
  EXPECT_EQ(result, expected_result);
}

TEST(serializer_tests, from_params_to_string) {
  std::vector<Parameter> params;
  std::string result = Serializer::ToJsonString("params", params);
  EXPECT_EQ(result, R"({"params":[]})");

  params.push_back(Parameter("key", "value"));
  result = Serializer::ToJsonString("params", params);
  EXPECT_EQ(result, R"({"params":[{"key":"value"}]})");

  params.push_back(Parameter("name", "val"));
  result = Serializer::ToJsonString("params", params);
  EXPECT_EQ(result, R"({"params":[{"key":"value"},{"name":"val"}]})");

  result = Serializer::ToJsonString("", params);
  EXPECT_EQ(result, "");
}

TEST(serializer_tests, from_block_to_string) {
  Block empty_block;
  std::string result = Serializer::ToJsonString(empty_block);
  EXPECT_EQ(result, "");

  std::vector<Parameter> empty_params;
  Block block("path", empty_params, empty_params, "block_name", "block_descr", "block_author_name",
              11);
  result = Serializer::ToJsonString(block);
  EXPECT_EQ(result,
            "{\"solver_path\":\"path\",\"given_vars\":[{\"key\":\"value\"}],\"solved_vars\":[{}],"
            "\"name\":\"block_name\",\"description\":\"block_descr\",\"author_name\":\"block_"
            "author_name\",\"color\":\"11\"}");
}

TEST(serializer_tests, from_blocks_to_string) {
  std::vector<Block> blocks;
  std::string result = Serializer::ToJsonString("blocks", blocks);
  EXPECT_EQ(result, "");

  std::vector<Parameter> empty_params;
  Block block("path", empty_params, empty_params, "block_name", "block_descr", "block_author_name",
              11);
  blocks.push_back(block);
  result = Serializer::ToJsonString("blocks", blocks);
  EXPECT_EQ(result,
            R"({"blocks":[{"solver_path":"path","given_vars":[{"key":"value"}],"solved_vars":[{}],"
            ""name":"block_name","description":"block_descr","author_name":"block_"
            "author_name","color":"11"}]})");
}
