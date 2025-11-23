#include "ConsoleParser.hpp"
#include <iostream>

// g++ -std=c++11 main.cpp node/ANode.cpp node/NumberNode.cpp node/VarNode.cpp node/OperatorNode.cpp Tree.cpp ConsoleParser.cpp -o ./test

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
