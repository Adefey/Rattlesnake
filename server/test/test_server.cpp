/*
 * Компилируется с appinfo_test, dbhelper_test, machine_factory_test,
 * server_application_test
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <server_application.hpp>

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
