#include "NumberNode.hpp"
#include <iostream>

NumberNode::NumberNode()
{
    value = 1;
}

NumberNode::NumberNode(int& offset, const std::string& val)
{
    std::string number = "";
    for (; offset < val.length() && val[offset] != ' '; number += val[offset++]);
    
    try {
        value = std::stod(number);   
    }
    catch (int errorCode)
    {
        std::cout << "There was an error while parsing " << number << " to double. Replaced with 1." << std::endl;
        value = 1;
    }
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