// Copyright 2022 Adefe

#include <gtest/gtest.h>
#include <server_application.hpp>

TEST(MachineFactoryTest, ProcessMachineTest) {
  MachineFactory machine_factory;
  User u;
  EXPECT_NO_THROW(machine_factory.ProcessMachine(u));
  EXPECT_NE(machine_factory.ProcessMachine(u), std::string(""));
}
