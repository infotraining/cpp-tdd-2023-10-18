#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <unordered_map>

#include "console.hpp"
#include "command.hpp"

class Application
{
    Console& console_;

    constexpr static auto EXIT = "exit";
public:
    Application(Console& console) : console_(console) {}

    void run()
    {
        do
        {
            console_.print("> Enter a command:");
            
            auto line = console_.get_line();
            if (line == EXIT)
            {
                console_.print("Bye!!!");
                return;
            }
        }
        while(true);
    }
};

#endif // APPLICATION_HPP
