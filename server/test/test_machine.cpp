/*
 * Компилируется с machine_test
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <machine.hpp>

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
