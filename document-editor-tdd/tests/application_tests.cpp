#include <gtest/gtest.h>
#include "mocks/mock_console.hpp"
#include "mocks/mock_command.hpp"
#include "application.hpp"

using namespace ::testing;

class ApplicationTests : public ::testing::Test
{
protected:
    NiceMock<MockConsole> console;
    Application app{console};
    std::shared_ptr<MockCommand> cmd = std::make_shared<MockCommand>();
    
    void SetUp() override
    {
        app.add_command("cmd", cmd);

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

TEST_F(ApplicationTests, ExecutesCommands)
{
    EXPECT_CALL(console, get_line()).Times(1).WillOnce(Return("cmd")).RetiresOnSaturation();
    EXPECT_CALL(*cmd, execute()).Times(1);

    app.run();
}

TEST_F(ApplicationTests, UnknownCommandPrintsErrorMessage)
{
    
    EXPECT_CALL(console, get_line()).Times(1).WillOnce(Return("unknown_cmd")).RetiresOnSaturation();
    EXPECT_CALL(console, print("Bye!!!")).Times(1).RetiresOnSaturation();
    EXPECT_CALL(console, print(_)).Times(1).RetiresOnSaturation();    
    EXPECT_CALL(console, print("Unknown command: unknown_cmd")).Times(1).RetiresOnSaturation();
    EXPECT_CALL(console, print(_)).Times(1).RetiresOnSaturation();    

    app.run();
}

/////////////////////////////////////////////////////////////////////////



TEST(PrintCmdTests, DocumentContentIsPrintedInConsole)
{
    MockConsole console;
    Document doc{"abc"};

    PrintCmd print_cmd{console, doc};

    EXPECT_CALL(console, print("[abc]"));

    print_cmd.execute();
}