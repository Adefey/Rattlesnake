  // Copyright 2022 Adefe

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <server_application.hpp>

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

class MockServerApplication : public ServerApplication {
public:
  MOCK_METHOD(void, ProcessEvents, ());
  MOCK_METHOD(void, ProcessUser, ());
  MOCK_METHOD(void, ProcessStat, ());

  MOCK_METHOD((std::string), RequestQuery, (std::string));
  MOCK_METHOD(Block, RequestBlock, (std::string));
  MOCK_METHOD((std::vector<Block>), RequestAllBlocks, ());
  MOCK_METHOD(void, LogData, (std::string));

  MOCK_METHOD((std::string), MakeStartString, ());
  MOCK_METHOD(void, LaunchProcess, (std::string));
  MOCK_METHOD((std::string), ProcessMachine, ());
};

TEST(ServerApplicationTest, ProcessUserTest) {
    MockServerApplication mock_server_application;
    mock_server_application.ProcessUser();
    EXPECT_CALL(mock_server_application, MakeStartString()).Times(AtLeast(1));
    EXPECT_CALL(mock_server_application, LaunchProcess("")).Times(AtLeast(1));
    EXPECT_CALL(mock_server_application, ProcessMachine()).Times(AtLeast(1));

    EXPECT_CALL(mock_server_application, RequestQuery("")).Times(AtLeast(1));
    EXPECT_CALL(mock_server_application, RequestBlock("")).Times(AtLeast(1));
}

TEST(ServerApplicationTest, ProcessStatTest) {
    MockServerApplication mock_server_application;
    mock_server_application.ProcessStat();

    EXPECT_CALL(mock_server_application, RequestQuery("")).Times(AtLeast(1));
    EXPECT_CALL(mock_server_application, RequestAllBlocks()).Times(AtLeast(1));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
