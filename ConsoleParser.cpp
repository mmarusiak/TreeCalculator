#include "ConsoleParser.hpp"

std::vector<std::string> ConsoleParser::split(const std::string& s, const std::string& delimiter){
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

std::string ConsoleParser::readCommand(const std::string& cmd){
    std::vector<std::string> entries = split(cmd, " ");

    std::string cmdName = entries[0];
    auto it = availableCommands.find(cmdName);
    if (it != availableCommands.end()) return it->second(std::vector<std::string>(entries.begin() + 1, entries.begin() + entries.size()) );
    return "Unknown command...";
}

ConsoleParser::ConsoleParser() {
    availableCommands = {
        {"enter", [this](const std::vector<std::string>& args) {
            return enter(args);
        }},
        {"vars", [this](const std::vector<std::string>& args) {
            return vars();
        }},
        {"print", [this](const std::vector<std::string>& args) {
            return print();
        }},
        {"comp", [this](const std::vector<std::string>& args) {
            return comp(args);
        }},
        {"join", [this](const std::vector<std::string>& args) {
            return join(args);
        }}
    };
}


std::string ConsoleParser::enter(const std::vector<std::string>& args)
{
    if (args.size() < 1) return "Please provide formula!";
    std::string formula = args[0];
    if (args.size() > 1) {
        for(int i = 1; i < args.size(); ++ i)
        {
            formula += " " + args[i];
        }
    }
    tree.loadTreeFromString(formula);
    return "Tree loaded! \n" + tree.toString();
}

std::string ConsoleParser::vars()
{
    if (!tree.initialized) return "Please create tree first!";

    std::vector<std::string> vars = tree.getVars();
    std::string result = "";

    for (int i = 0; i < vars.size(); ++ i)
    {
        result += std::to_string(i + 1) + ". " + vars[i];
        if (i < vars.size() - 1) result += "\n";
    }

    return result;
}

std::string ConsoleParser::print()
{
    if (!tree.initialized) return "Please create tree first!";

    return tree.toString();
}

std::string ConsoleParser::comp(const std::vector<std::string>& args)
{
    if (!tree.initialized) return "Please create tree first!";

    std::vector<std::string> vars = tree.getVars();
    int missingArgs = vars.size() - args.size();
    if(missingArgs > 0) return "Missing " + std::to_string(missingArgs) + " arguments...";
    
    std::map<std::string, double> varsMap;

    for(int i = 0; i < vars.size(); i ++)
    {
        varsMap[vars[i]] = std::stod(args[i]);
    }
    bool success = true;
    std::string res = std::to_string(tree.calculateTree(varsMap, success));
    std::string error = success ? "\n OK" : "\n There was an error!";
    return res + error;
}

std::string ConsoleParser::join(const std::vector<std::string>& args)
{
    return "Hello world";
}