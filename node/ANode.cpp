#include "ANode.hpp"
#include "NumberNode.hpp"
#include "OperatorNode.hpp"
#include "VarNode.hpp"

#include <iostream>


namespace {
    ANode* loadOperatorOrVarNode(const std::string& input, int& offset)
    {
        std::string entry = "";
        for (int i = offset; i < input.size() && input[i] != ' '; ++i) {
            char ch = input[i];
            if (ch >= 'A' && ch <= 'Z') ch = ch - 'A' + 'a';
            entry += ch;
        }

        if (entry.compare("+") == 0 || entry.compare("-") == 0 || entry.compare("/") == 0 || 
            entry.compare("*") == 0 || entry.compare("sin") == 0 || entry.compare("cos") == 0) {
            return new OperatorNode(offset, input);
        }

        return new VarNode(offset, input);
    }
}

ANode* ANode::parseFromString(const std::string& input, int& offset)
{
    while (offset < input.length() && input[offset] == ' ') ++offset;

    char currentChar = input[offset];
    if (currentChar >= '0' && currentChar <= '9')
        return new NumberNode(offset, input);

    if (offset >= input.length() - 1 && (currentChar == 0 || currentChar == ' '))
    {
        std::cout << "Missing number, fixed with 1." << std::endl;
        return new NumberNode();
    }
    return loadOperatorOrVarNode(input, offset);
}


void ANode::appendChild(int& offset, const std::string& val)
{
    ANode* child = ANode::parseFromString(val, offset);
    mergeVars(child->getVars());
    children.push_back(child);
}

void ANode::mergeVars(const std::vector<std::string>& otherVars)
{
    for(int i = 0; i < otherVars.size(); ++ i)
    {
        bool contains;
        for (int j = 0; j < vars.size(); ++ j)
        {
            if (vars[j].compare(otherVars[i]) == 0) contains = true;
        }
        if (!contains) vars.push_back(otherVars[i]);       
    }
}