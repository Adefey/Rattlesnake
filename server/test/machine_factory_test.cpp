// Copyright 2022 Adefe

#include <gtest/gtest.h>
#include <server_application.hpp>

TEST(MachineFactoryTest, MakeStartString) {
  MachineFactory machine_factory;
  User u;
  EXPECT_ANY_THROW(machine_factory.ProcessMachine(u));
}
