// Copyright 2022 Adefe

#include <gtest/gtest.h>
#include <server_application.hpp>

TEST(ServerApplicationTest, ProcessEventsTest) {
  ServerApplication server;
  EXPECT_NO_THROW(server.ProcessEvents());
}
