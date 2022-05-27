// Copyright 2022 Adefe

#include <gtest/gtest.h>
#include <server_application.hpp>

TEST(ServerApplicationTest, ProcessEventsTest) {
  EXPECT_ANY_THROW({
    ServerApplication server;
    server.ProcessEvents();
  });
}

TEST(ServerApplicationTest, ProcessUser) {
  User u;
  NetMessage message;
  EXPECT_ANY_THROW({
    ServerApplication server;
    server.ProcessUser(u, message);
  });
}

TEST(ServerApplicationTest, ProcessStat) {
  User u;
  NetMessage message;
  EXPECT_ANY_THROW({
    ServerApplication server;
    server.ProcessStat(u);
  });
}
