#ifndef NumberNode_H
#define NumberNode_H

#include "ANode.hpp"
#include <string>
#include <vector>
#include <map>

// ordered/unordered - tablica mieszajaca/drzewo

class NumberNode : public ANode {
    double value;
public:
    NumberNode();
    NumberNode(int& offset, const std::string& val);
    ~NumberNode();
    
    double operator() (const std::map<std::string, double>& varValues, bool& success) const override;
    std::string toString() const override;
};

#endif
