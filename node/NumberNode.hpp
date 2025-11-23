#ifndef NumberNode_H
#define NumberNode_H

#include "node/ANode.hpp"
#include <string>
#include <vector>
#include <map>

// ordered/unordered - tablica mieszajaca/drzewo

class NumberNode : public ANode {
    
public:
    NumberNode();
    NumberNode(int& offset, const std::string& val);
    ~NumberNode();
    
    NumberNode(const NumberNode& other);
    NumberNode& operator=(const ANode& other);
    
    double operator() (const std::map<std::string, double>& varValues, bool& success) const override;
    std::string toString() const;

    void addChild(ANode* child);
    int getChildrenCount() const;
    ANode* getChild(int index) const;
    
    int parseFromString(const std::string& input, int offset, bool& error, bool& fixed);
    void getPrefixString(std::string& result) const;
    void getVariables(std::vector<std::string>& vars) const;
    
    ANode* getFirstLeaf();
    void replaceChild(ANode* oldChild, ANode* newChild);
};

#endif
