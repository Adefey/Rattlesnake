// Copyright 2022 Adefe

#include <gtest/gtest.h>
#include <server_application.hpp>

TEST(DBHelperTest, RequestBlockTest) {
  DBHelper helper;
  EXPECT_NO_THROW(helper.RequestBlock(""));
}

TEST(DBHelperTest, RequestAllBlocksTest) {
  DBHelper helper;
  EXPECT_NO_THROW(helper.RequestAllBlocks());
}

TEST(DBHelperTest, LogDataTest) {
  DBHelper helper;
  EXPECT_NO_THROW(helper.LogData(""));
}
