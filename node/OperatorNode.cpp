#include "OperatorNode.hpp"
#include <iostream>

OperatorNode::OperatorNode(int& offset, const std::string& val)
{
    std::string op = "";
    for (; offset < val.length() && val[offset] != ' '; op += val[offset++]);

    operatorSign = op[0];

    if (op.compare("+") == 0 || op.compare("-") == 0 || op.compare("/") == 0 || op.compare("*") == 0) {
        appendChild(offset, val);
        appendChild(offset, val);
    }
    else
    {
        appendChild(offset, val);
    }
}

OperatorNode::~OperatorNode() {}

double OperatorNode::operator()(const std::map<std::string, double> &varValues, bool &success) const
{
    if(operatorSign == '+') return (*children[0])(varValues, success) + (*children[1])(varValues, success);
    if(operatorSign == '-') return (*children[0])(varValues, success) - (*children[1])(varValues, success);
    if(operatorSign == '*') return (*children[0])(varValues, success) * (*children[1])(varValues, success);
    if(operatorSign == '/') {
        float n = (*children[1])(varValues, success);
        if (n == 0) {
            std::cout << "Division by zero!" << std::endl;
            success = false;
        }
        return (*children[0])(varValues, success) / n;
    }

    if(operatorSign == 's' || operatorSign == 'S') return sin((*children[0])(varValues, success));
    if(operatorSign == 'c' || operatorSign == 'C') return cos((*children[0])(varValues, success));

    success = false;
    return 0;
}

std::string OperatorNode::toString() const 
{
    if (operatorSign == '+' || operatorSign == '-' || operatorSign == '*' || operatorSign == '/') 
        return {operatorSign};
    if(operatorSign == 's' || operatorSign == 'S') return "sin";
    if(operatorSign == 'c' || operatorSign == 'C') return "cos";

    return "unknown operator...";
}