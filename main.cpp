#include "ConsoleParser.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    ConsoleParser parser;

    std::string command = "";
    while (command != "q" && command != "quit"){
        std::cout << "Please provide a command: \n";
        std::getline(std::cin, command);

        while (command.empty())      // skip empty line if needed
            std::getline(std::cin, command);
        
        std::cout << parser.readCommand(command) << std::endl;
    }

    return 0;
}
