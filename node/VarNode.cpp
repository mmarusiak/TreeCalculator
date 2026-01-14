#include "VarNode.hpp"

VarNode::VarNode()
{
    variable = "";
}

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

ANode* VarNode::clone() const
{
    VarNode* cloned = new VarNode();
    cloned->variable = this->variable;
    cloned->vars = this->vars;
    for (auto child : this->children) {
        cloned->children.push_back(child->clone());
    }
    return cloned;
}