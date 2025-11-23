#ifndef ANode_H
#define ANode_H

#include <string>
#include <vector>
#include <map>

// ordered/unordered - tablica mieszajaca/drzewo

class ANode {
private:
    std::vector<ANode*> children;
    std::vector<std::string> vars;

public:
    ANode();
    ANode(int& offset, const std::string& val);
    ~ANode();
    
    ANode(const ANode& other);
    ANode& operator=(const ANode& other);
    
    virtual double operator() (const std::map<std::string, double>& varValues, bool& success) const;
    virtual std::string toString() const;

    void addChild(ANode* child);
    int getChildrenCount() const;
    ANode* getChild(int index) const;
    
    ANode parseFromString(const std::string& input, int& offset, bool& error, bool& fixed, std::string& fixMessage);
    std::vector<std::string>& getVariables(std::vector<std::string>& vars) const {
        return vars;
    };
    
    ANode* getFirstLeaf();
    void replaceChild(ANode* oldChild, ANode* newChild);
};

#endif
