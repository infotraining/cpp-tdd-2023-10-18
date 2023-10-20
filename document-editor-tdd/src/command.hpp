#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "clipboard.hpp"
#include "console.hpp"
#include "document.hpp"
#include <memory>
#include <stack>

class Command
{
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

#endif // COMMAND_HPP