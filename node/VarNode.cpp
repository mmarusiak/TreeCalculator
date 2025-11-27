#include "VarNode.hpp"

VarNode::VarNode(int& offset, const std::string& val)
{
    std::string var = "";
    for (; offset < val.length() && val[offset] != ' '; var += val[offset++]);

    variable = var;
    vars.push_back(var);    
}

VarNode::~VarNode() {}


double VarNode::operator()(const std::map<std::string, double> &varValues, bool &success) const
{
    int value = 0;
    auto it = varValues.find(variable);
    if (it != varValues.end()) return it->second;    
    
    success = false;
    return 1;    
}

std::string VarNode::toString() const 
{
    return variable;
}