#include <gtest/gtest.h>

#include "netlibraryclient.hpp"

TEST(netlibraryclient_tests, all_tests) {
  NetClient client;
  NetLibraryClient client_lib;
  std::string data;
  EXPECT_NO_THROW(client_lib.SendBlocksRequest(client));
  EXPECT_NO_THROW(client_lib.SendBlocksJson(client, data));
  EXPECT_NO_THROW(client_lib.SendSchemeJson(client, data));
  EXPECT_NO_THROW(client_lib.ReceiveBlocksJson(client));
}