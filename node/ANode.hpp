#ifndef ANODE_H
#define ANODE_H

#include <string>
#include <vector>
#include <map>

class ANode {
protected:
    std::vector<ANode*> children;
    std::vector<std::string> vars;
    std::string fixMessage;

public:
    // Abstract interface
    virtual double operator()(const std::map<std::string, double>& varValues, bool& success) const = 0;
    virtual std::string toString() const = 0;

    // Parsing function returns pointer
    static ANode* parseFromString(const std::string& input, int& offset);

    ANode() = default;
    virtual ~ANode() {
        for (auto child : children) delete child;
    }

    ANode(const ANode&) = delete;
    ANode& operator=(const ANode&) = delete;

    void appendChild(int& offset, const std::string& val);

    void mergeVars(const std::vector<std::string>& otherVars);

    void replaceLeaf(ANode& leaf);

    const std::vector<std::string>& getVars() const { return vars; }
    const std::vector<ANode*>& getChildren() const { return children; }
};

#endif
