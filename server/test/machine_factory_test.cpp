/*
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <server_application.hpp>

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

class MockMachineFactory : public MachineFactory {
public:
  MOCK_METHOD((std::string), MakeStartString, ());
  MOCK_METHOD(void, LaunchProcess, (std::string));
  MOCK_METHOD((std::string), ProcessMachine, ());
};

TEST(MachineFactoryTest, ProcessMachineTest) {
  MockMachineFactory mock_machine_factory;
  mock_machine_factory.ProcessMachine();
  EXPECT_CALL(mock_machine_factory, MakeStartString()).Times(AtLeast(1));
  EXPECT_CALL(mock_machine_factory, LaunchProcess("")).Times(AtLeast(1));*
}

*/
