#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <unordered_map>

#include "console.hpp"
#include "command.hpp"

class Application
{
    Console& console_;
public:
    Application(Console& console) : console_(console) {}

    void run()
    {
        console_.print("> Enter a command:");
        auto line = console_.get_line();        
    }
};

#endif // APPLICATION_HPP
