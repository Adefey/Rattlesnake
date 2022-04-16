#include <gtest/gtest.h>

#include "netserver.hpp"

TEST(netserver_and_socket_tests, netserver_test) {
  NetServer server;
  EXPECT_NO_THROW(server.InitializeServer(static_cast<uint32_t>(27651)));
}

TEST(netserver_and_socket_tests, netsocket_test) {
  NetSocket socket;
  EXPECT_NO_THROW(socket.CreateSocket());
  EXPECT_NO_THROW(socket.GetSocket());
}
