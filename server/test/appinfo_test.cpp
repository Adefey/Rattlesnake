// Copyright 2022 Adefe

#include <gtest/gtest.h>
#include <server_application.hpp>

TEST(AppInfoTest, GetDBAddressTest) {
  EXPECT_NO_THROW(AppInfo::GetDBAddress());
  EXPECT_NE(AppInfo::GetDBAddress(), "");
}

TEST(AppInfoTest, GetDBUsernameTest) {
  EXPECT_NO_THROW(AppInfo::GetDBUsername());
  EXPECT_NE(AppInfo::GetDBAddress(), "");
}

TEST(AppInfoTest, GetDBPasswordTest) {
  EXPECT_NO_THROW(AppInfo::GetDBPassword());
}

TEST(AppInfoTest, GetDBDatabaseTest) {
  EXPECT_NO_THROW(AppInfo::GetDBDatabase());
}

TEST(AppInfoTest, GetDBBlockTableTest) {
  EXPECT_NO_THROW(AppInfo::GetDBBlockTable());
}

TEST(AppInfoTest, GetDBLogTableTest) {
  EXPECT_NO_THROW(AppInfo::GetDBLogTable());
}

TEST(AppInfoTest, GetMaxMachinesCountTest) {
  EXPECT_NO_THROW(AppInfo::GetMaxMachinesCount());
}

TEST(AppInfoTest, GetRefreshPeriodTest) {
  EXPECT_NO_THROW(AppInfo::GetRefreshPeriod());
}
