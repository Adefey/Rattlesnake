// Copyright 2022 Adefe

#include <gtest/gtest.h>
#include <server_application.hpp>

TEST(AppInfoTest, GetDBAddressTest) {
  EXPECT_NO_THROW(AppInfo::GetDBAddress());
  EXPECT_NE(AppInfo::GetDBAddress(), "");
}

TEST(AppInfoTest, GetDBUsernameTest) {
  EXPECT_NO_THROW(AppInfo::GetDBUsername());
  EXPECT_NE(AppInfo::GetDBUsername(), "");
}

TEST(AppInfoTest, GetDBPasswordTest) {
  EXPECT_NO_THROW(AppInfo::GetDBPassword());
  EXPECT_NE(AppInfo::GetDBPassword(), "");
}

TEST(AppInfoTest, GetDBDatabaseTest) {
  EXPECT_NO_THROW(AppInfo::GetDBDatabase());
  EXPECT_NE(AppInfo::GetDBDatabase(), "");
}

TEST(AppInfoTest, GetDBBlockTableTest) {
  EXPECT_NO_THROW(AppInfo::GetDBBlockTable());
  EXPECT_NE(AppInfo::GetDBBlockTable(), "");
}

TEST(AppInfoTest, GetDBLogTableTest) {
  EXPECT_NO_THROW(AppInfo::GetDBLogTable());
  EXPECT_NE(AppInfo::GetDBLogTable(), "");
}

TEST(AppInfoTest, GetMaxMachinesCountTest) {
  EXPECT_NO_THROW(AppInfo::GetMaxMachinesCount());
  EXPECT_NE(AppInfo::GetMaxMachinesCount(), 0);
}

TEST(AppInfoTest, GetRefreshPeriodTest) {
  EXPECT_NO_THROW(AppInfo::GetRefreshPeriod());
  EXPECT_NE(AppInfo::GetRefreshPeriod(), 0);
}
