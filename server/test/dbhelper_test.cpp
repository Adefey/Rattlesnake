// Copyright 2022 Adefe

#include <gtest/gtest.h>
#include <server_application.hpp>

TEST(DBHelperTest, RequestAllBlocksTest) {
  EXPECT_NO_THROW(DBHelper::RequestAllBlocks());
}

TEST(DBHelperTest, LogDataTest) { EXPECT_NO_THROW(DBHelper::LogData("")); }
