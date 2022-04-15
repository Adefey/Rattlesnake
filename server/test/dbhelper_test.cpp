// Copyright 2022 Adefe

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <server_application.hpp>

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

class MockDBHelper : public DBHelper {
public:
  MOCK_METHOD((std::string), RequestQuery, (std::string));
  MOCK_METHOD(Block, RequestBlock, (std::string));
  MOCK_METHOD((std::vector<Block>), RequestAllBlocks, ());
  MOCK_METHOD(void, LogData, (std::string));
};

TEST(DBHelperTest, RequestBlockTest) {
  MockDBHelper mock_dbhelper;
  mock_dbhelper.RequestBlock("");
  EXPECT_CALL(mock_dbhelper, RequestQuery("")).Times(AtLeast(1));
}

TEST(DBHelperTest, RequestAllBlocksTest) {
  MockDBHelper mock_dbhelper;
  mock_dbhelper.RequestAllBlocks();
  EXPECT_CALL(mock_dbhelper, RequestQuery("")).Times(AtLeast(1));
}

TEST(DBHelperTest, LogDataTest) {
  MockDBHelper mock_dbhelper;
  mock_dbhelper.LogData("");
  EXPECT_CALL(mock_dbhelper, RequestQuery("")).Times(AtLeast(1));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
