#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "parser.hpp"

TEST(parser_tests, string_to_int_test) {
  std::string empty_string = "";
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
  std::string empty_string = "";
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

  std::string incorrect_string = "";
  EXPECT_FALSE(Parser::ParseParameterFromJsonString(incorrect_string, param));

  std::string correct_string = "{\"key\":\"value\"}";
  EXPECT_TRUE(Parser::ParseParameterFromJsonString(correct_string, param));
  EXPECT_EQ(param.param_name, "key");
  EXPECT_EQ(param.param_value, "value");

  incorrect_string = "{}";
  EXPECT_FALSE(Parser::ParseParameterFromJsonString(incorrect_string, param));

  incorrect_string = "{\"key\";\"value\"}";
  EXPECT_FALSE(Parser::ParseParameterFromJsonString(incorrect_string, param));
}

TEST(parser_tests, parse_params) {
  std::vector<Parameter> params;

  std::string incorrect_string = "";
  EXPECT_FALSE(Parser::ParseParametersFromJsonString(incorrect_string, params));

  incorrect_string = "{[{\"key\";\"value\"},{\"key\";\"value\"},{\"key\";\"value\"}]}";
  EXPECT_FALSE(Parser::ParseParametersFromJsonString(incorrect_string, params));

  params.clear();
  std::string correct_string = "{[{\"key\":\"value\"},{\"key\":\"value\"},{\"key\":\"value\"}]}";
  EXPECT_TRUE(Parser::ParseParametersFromJsonString(correct_string, params));
  ASSERT_EQ(params.size(), 3);
  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(params[i].param_name, "key");
    EXPECT_EQ(params[i].param_value, "value");
  }
}
