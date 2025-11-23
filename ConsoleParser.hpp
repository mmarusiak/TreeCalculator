#ifndef ConsoleParser_H
#define ConsoleParser_H

#include <string>
#include <vector>
#include <map>
#include <functional>
#include "Tree.hpp"


class ConsoleParser
{
private:
    Tree tree;
    std::vector<std::string> split(const std::string& s, const std::string& delimiter);
    std::map<std::string, std::function<std::string(const std::vector<std::string>&)>> availableCommands;
public:
    ConsoleParser();
    std::string readCommand(const std::string& cmd);
    std::string enter(const std::vector<std::string>& args);
    std::string vars();
    std::string print();
    std::string comp(const std::vector<std::string>& args);
    std::string join(const std::vector<std::string>& args);
};

#endif
