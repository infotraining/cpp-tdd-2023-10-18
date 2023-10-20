#include <gtest/gtest.h>
#include "mocks/mock_console.hpp"
#include "application.hpp"

using namespace ::testing;

TEST(ApplicationTests, DisplaysPromptForCommand)
{
    MockConsole console;
    Application app(console); // DI

    EXPECT_CALL(console, print("> Enter a command:"));
    
    app.run();
}

TEST(ApplicationTests, GetsLineFromConsole)
{
    MockConsole console;
    Application app(console);

    EXPECT_CALL(console, get_line());

    app.run();
}   