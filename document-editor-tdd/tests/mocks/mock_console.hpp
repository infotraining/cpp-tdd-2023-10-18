#ifndef MOCK_CONSOLE_HPP
#define MOCK_CONSOLE_HPP

#include "console.hpp"
#include "gmock/gmock.h"

class MockConsole : public Console
{
public:
    MOCK_METHOD(std::string, get_line, (), (override));
    MOCK_METHOD(void, print, (const std::string&), (override));
};

#endif // MOCK_CONSOLE_HPP
