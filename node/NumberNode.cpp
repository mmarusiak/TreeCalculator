#include "NumberNode.hpp"

NumberNode::NumberNode()
{
    value = 1;
}

NumberNode::NumberNode(int& offset, const std::string& val)
{
    std::string number = "";
    for (; offset < val.length() && val[offset] != ' '; number += val[offset++]);

    value = std::stod(number);   
}

NumberNode::~NumberNode() {}

double NumberNode::operator()(const std::map<std::string, double> &varValues, bool &success) const
{
    return value;
}

std::string NumberNode::toString() const 
{
    return std::to_string(value);
}