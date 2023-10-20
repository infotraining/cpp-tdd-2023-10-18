#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <map>

#include "console.hpp"
#include "command.hpp"

class Application
{
    Console& console_;
    std::map<std::string, std::shared_ptr<Command>> commands_;

    constexpr static auto EXIT = "exit";
public:
    Application(Console& console) : console_(console) {}

    void add_command(const std::string& name, std::shared_ptr<Command> command)
    {
        commands_[name] = command;
    }

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
                        
            if (auto it = commands_.find(line); it != commands_.end())
            {
                const auto& [name, cmd] = *it;

                cmd->execute();
            }
            else
            {
                console_.print("Unknown command: " + line);
            }                    
        }
        while(true);
    }
};

#endif // APPLICATION_HPP
