#ifndef MOCK_CONSOLE_HPP
#define MOCK_CONSOLE_HPP

#include <trompeloeil.hpp>

class MockConsole : public Console
{
public:
    MAKE_MOCK0(get_line, std::string());
    MAKE_MOCK1(print, void (const std::string&));
};

#endif // MOCK_CONSOLE_HPP
