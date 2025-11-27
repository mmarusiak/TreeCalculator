#include "OperatorNode.hpp"

OperatorNode::OperatorNode(int& offset, const std::string& val)
{
    std::string op = "";
    for (; offset < val.length() && val[offset] != ' '; op += val[offset++]);

    if (op.compare("+") == 0 || op.compare("-") == 0 || op.compare("/") == 0 || op.compare("*") == 0) {
        operatorSign = op[0];

        appendChild(offset, val);
        appendChild(offset, val);
    }
    else
    {
        operatorSign = op[0];

        appendChild(offset, val);
    }
}

OperatorNode::~OperatorNode() {}

double OperatorNode::operator()(const std::map<std::string, double> &varValues, bool &success) const
{
    if(operatorSign == '+') return (*children[0])(varValues, success) + (*children[1])(varValues, success);
    if(operatorSign == '-') return (*children[0])(varValues, success) - (*children[1])(varValues, success);
    if(operatorSign == '*') return (*children[0])(varValues, success) * (*children[1])(varValues, success);
    if(operatorSign == '/') return (*children[0])(varValues, success) / (*children[1])(varValues, success);

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