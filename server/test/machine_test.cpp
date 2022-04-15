#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <machine.hpp>

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

class MockMachine : public Machine {
public:
  MOCK_METHOD(void, ProcessOneBlock, (std::string));
  MOCK_METHOD((std::string), MakeProcessStartString, (std::string));
  MOCK_METHOD((std::string), ProcessAllBlocks, ());
};

TEST(MachineTest, ProcessAllBlocksTest) {
  MockMachine mock_machine;
  mock_machine.ProcessAllBlocks();
  EXPECT_CALL(mock_machine, ProcessOneBlock("")).Times(AtLeast(1));
  EXPECT_CALL(mock_machine, MakeProcessStartString("")).Times(AtLeast(1));
}
