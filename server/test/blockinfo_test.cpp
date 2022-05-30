// Copyright 2022 Adefe

#include <gtest/gtest.h>
#include <server_application.hpp>

TEST(BlockInfoTest, GetBlockSolverPath) {
  EXPECT_ANY_THROW(BlockInfo::GetBlockSolverPath(""));
}

TEST(BlockInfoTest, GetBlockGivenVars) {
  EXPECT_ANY_THROW(BlockInfo::GetBlockGivenVars(""));
}

TEST(BlockInfoTest, GetBlockSolvedVars) {
  EXPECT_ANY_THROW(BlockInfo::GetBlockSolvedVars(""));
}

TEST(BlockInfoTest, GetBlockName) {
  EXPECT_ANY_THROW(BlockInfo::GetBlockName(""));
}

TEST(BlockInfoTest, GetBlockDescription) {
  EXPECT_ANY_THROW(BlockInfo::GetBlockDescription(""));
}

TEST(BlockInfoTest, GetBlockAuthorName) {
  EXPECT_ANY_THROW(BlockInfo::GetBlockAuthorName(""));
}

TEST(BlockInfoTest, GetBlockColor) {
  EXPECT_ANY_THROW(BlockInfo::GetBlockColor(""));
}
