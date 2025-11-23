#ifndef VarNode_H
#define VarNode_H

#include "ANode.hpp"
#include <string>
#include <vector>
#include <map>

// ordered/unordered - tablica mieszajaca/drzewo

class VarNode : public ANode {
    std::string variable;
public:
    VarNode();
    VarNode(int& offset, const std::string& val);
    ~VarNode();
    
    VarNode(const VarNode& other);
    VarNode& operator=(const VarNode& other);
    
    double operator() (const std::map<std::string, double>& varValues, bool& success) const override;
    std::string toString() const override;
};

#endif
