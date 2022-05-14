#include <gtest/gtest.h>

#include "netlibraryclient.hpp"

TEST(netlibraryclient_tests, all_tests) {
  NetClient client;
  std::string data;
  EXPECT_NO_THROW(NetLibraryClient::SendBlocksRequest(client));
  EXPECT_NO_THROW(NetLibraryClient::SendSchemeJson(client, data));
  EXPECT_NO_THROW(NetLibraryClient::ReceiveBlocksJson(client, data));
  EXPECT_NO_THROW(NetLibraryClient::ReceiveResultsJson(client, data));
}
