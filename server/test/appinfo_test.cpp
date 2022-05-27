// Copyright 2022 Adefe

#include <gtest/gtest.h>
#include <server_application.hpp>

TEST(AppInfoTest, GetDBAddressTest) {
  EXPECT_ANY_THROW(AppInfo::GetDBAddress());
}

TEST(AppInfoTest, GetDBUsernameTest) {
  EXPECT_ANY_THROW(AppInfo::GetDBUsername());
}

TEST(AppInfoTest, GetDBPasswordTest) {
  EXPECT_ANY_THROW(AppInfo::GetDBPassword());
}

TEST(AppInfoTest, GetDBDatabaseTest) {
  EXPECT_ANY_THROW(AppInfo::GetDBDatabase());
}

TEST(AppInfoTest, GetDBBlockTableTest) {
  EXPECT_ANY_THROW(AppInfo::GetDBBlockTable());
}

TEST(AppInfoTest, GetDBLogTableTest) {
  EXPECT_ANY_THROW(AppInfo::GetDBLogTable());
}

TEST(AppInfoTest, GetMaxMachinesCountTest) {
  EXPECT_ANY_THROW(AppInfo::GetMaxMachinesCount());
}

TEST(AppInfoTest, GetRefreshPeriodTest) {
  EXPECT_ANY_THROW(AppInfo::GetRefreshPeriod());
}
