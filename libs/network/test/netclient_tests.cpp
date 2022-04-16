#include <gtest/gtest.h>

#include "netclient.hpp"

TEST(netclient_tests, set_address_test) {
  bool result = true;
  NetClient client;

  result = client.SetServerAddress("");
  EXPECT_FALSE(result);

  result = client.SetServerAddress("127.0.0.1");
  EXPECT_TRUE(result);

  result = client.SetServerAddress("127.0.");
  EXPECT_FALSE(result);

  result = client.SetServerAddress("127.0.0.1.");
  EXPECT_FALSE(result);
}
