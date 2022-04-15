// Copyright 2022 Adefe

#include <gtest/gtest.h>
#include <server_application.hpp>

TEST(AppInfoTest, GetDBAddressTest) {
  EXPECT_EQ(AppInfo::GetDBAddress(), "addr_here");
}

TEST(AppInfoTest, GetDBUsernameTest) {
  EXPECT_EQ(AppInfo::GetDBUsername(), "User");
}

TEST(AppInfoTest, GetDBPasswordTest) {
  EXPECT_EQ(AppInfo::GetDBPassword(), "password");
}

TEST(AppInfoTest, GetDBDatabaseTest) {
  EXPECT_EQ(AppInfo::GetDBDatabase(), "Rattlesnake");
}

TEST(AppInfoTest, GetDBBlockTableTest) {
  EXPECT_EQ(AppInfo::GetDBBlockTable(), "Blocks");
}

TEST(AppInfoTest, GetDBLogTableTest) {
  EXPECT_EQ(AppInfo::GetDBLogTable(), "Log");
}

TEST(AppInfoTest, GetMaxMachinesCountTest) {
  EXPECT_EQ(AppInfo::GetMaxMachinesCount(), 10);
}

TEST(AppInfoTest, GetRefreshPeriodTest) {
  EXPECT_EQ(AppInfo::GetRefreshPeriod(), 20);
}
