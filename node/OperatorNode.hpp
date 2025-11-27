#ifndef OperatorNode_H
#define OperatorNode_H

#include "ANode.hpp"
#include <string>
#include <vector>
#include <map>
#include <cmath>

// ordered/unordered - tablica mieszajaca/drzewo

class OperatorNode : public ANode {
    char operatorSign;
public:
    OperatorNode();
    OperatorNode(int& offset, const std::string& val);
    ~OperatorNode();
    
    double operator() (const std::map<std::string, double>& varValues, bool& success) const override;
    std::string toString() const override;
};

#endif
