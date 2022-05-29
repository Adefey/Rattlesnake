#include <gtest/gtest.h>

#include "netlibraryserver.hpp"

TEST(netlibraryserver_tests, all_tests) {
  NetSocket receiver;
  std::string data;
  NetMessage msg;
  EXPECT_NO_THROW(NetLibraryServer::SendBlocksJson(receiver, data));
  EXPECT_NO_THROW(NetLibraryServer::SendResultsJson(receiver, data));
  EXPECT_NO_THROW(NetLibraryServer::ReceiveMessage(receiver, msg));
}
