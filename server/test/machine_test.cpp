// Copyright 2022 Adefe

#include <gtest/gtest.h>
#include <machine.hpp>

TEST(MachineTest, ProcessEvents) {
  Machine machine;
  EXPECT_NO_THROW(machine.ProcessAllBlocks());
  EXPECT_NE(machine.ProcessAllBlocks(), "");
}
