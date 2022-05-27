// Copyright 2022 Adefe

#include <gtest/gtest.h>
#include <server_application.hpp>

TEST(DBHelperTest, RequestAllBlocksTest) {
  EXPECT_ANY_THROW(DBHelper::RequestAllBlocks());
}

TEST(DBHelperTest, LogDataTest) { EXPECT_ANY_THROW(DBHelper::LogData("")); }

TEST(DBHelperTest, AddBlock) {
  std::string SolverPath = "";
  std::string GivenVars = "";
  std::string SolvedVars = "";
  std::string Name = "";
  std::string Description = "";
  std::string AuthorName = "";
  int Color = 0;
  EXPECT_ANY_THROW(DBHelper::AddBlock(SolverPath, GivenVars, SolvedVars, Name,
                                      Description, AuthorName, Color));
}
