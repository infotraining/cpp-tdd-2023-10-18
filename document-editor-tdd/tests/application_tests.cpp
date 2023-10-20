#include <gtest/gtest.h>
#include "mocks/mock_console.hpp"
#include "application.hpp"

using namespace ::testing;

class ApplicationTests : public ::testing::Test
{
protected:
    NiceMock<MockConsole> console;
    Application app{console};// DI

    void SetUp() override
    {
        EXPECT_CALL(console, get_line()).WillOnce(Return("exit"));
    }
};

TEST_F(ApplicationTests, DisplaysPromptForCommand)
{
    
    EXPECT_CALL(console, print(_)).WillRepeatedly(Return());
    EXPECT_CALL(console, print("> Enter a command:")).Times(1).RetiresOnSaturation();    
    
    app.run();
}

TEST_F(ApplicationTests, GetsLineFromConsole)
{
    app.run();
}   

TEST_F(ApplicationTests, ExitEndsLoop)
{
    EXPECT_CALL(console, get_line())
        .Times(3)
        .WillRepeatedly(Return("cmd"))
        .RetiresOnSaturation();

    EXPECT_CALL(console, print("Bye!!!"));
    EXPECT_CALL(console, print(StartsWith(">"))).Times(4).RetiresOnSaturation();

    app.run();
}