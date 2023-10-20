#ifndef MOCK_COMMAND_HPP
#define MOCK_COMMAND_HPP

#include "gmock/gmock.h"
#include "command.hpp"

struct MockCommand : public Command
{
    MOCK_METHOD(void, execute, (), (override));
};

#endif // MOCK_COMMAND_HPP
