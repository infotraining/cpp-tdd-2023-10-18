#ifndef MOCK_COMMAND_HPP
#define MOCK_COMMAND_HPP

#include "gmock/gmock.h"

struct MockCommand : public Command
{
    MOCK_METHOD(void, execute, (), (override));
};

struct MockUndoableCommand : public UndoableCommand
{
    MOCK_METHOD(void, execute, (), (override));
    MOCK_METHOD(void, undo, (), (override));
    MOCK_METHOD(std::unique_ptr<UndoableCommand>, clone, (), (const, override));
};

#endif // MOCK_COMMAND_HPP
