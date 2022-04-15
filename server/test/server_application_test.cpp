// Copyright 2022 Adefe

#include <gtest/gtest.h>
#include <server_application.hpp>

TEST(ServerApplicationTest, ProcessEventsTest) {
  ServerApplication server;
  EXPECT_NO_THROW(server.ProcessEvents());
}

TEST(ServerApplicationTest, ProcessUserTest) {
  ServerApplication server;
  User u;
  // EXPECT_NO_THROW(server.ProcessUser(std::unique_ptr<User>(u)));
}

TEST(ServerApplicationTest, ProcessStatTest) {
  ServerApplication server;
  EXPECT_NO_THROW(server.ProcessStat());
}
