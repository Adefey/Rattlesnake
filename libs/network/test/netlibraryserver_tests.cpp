#include <gtest/gtest.h>

#include "netlibraryserver.hpp"

TEST(netlibraryserver_tests, all_tests) {
  NetServer server;
  NetLibraryServer server_lib;
  std::string data;
  EXPECT_NO_THROW(server_lib.SendBlocksJson(server, data));
  EXPECT_NO_THROW(server_lib.SendResultsJson(server, data));
  EXPECT_NO_THROW(server_lib.ReceiveBlocksJson(server));
}
