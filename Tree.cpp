#include "Tree.hpp"
#include <sstream>
#include <string>

namespace {

    // Recursive helper to print node and its children
    void printNode(const ANode* node, const std::string& prefix, bool isLast, std::stringstream& ss) {
        if (!node) return;

        ss << prefix;

        ss << (isLast ? "└──" : "├──");
        ss << node->toString() << "\n";

        // New prefix for children
        std::string childPrefix = prefix + (isLast ? "    " : "│   ");

        // Iterate over children
        for (size_t i = 0; i < node->getChildren().size(); ++i) {
            printNode(node->getChildren()[i], childPrefix, i == node->getChildren().size() - 1, ss);
        }
    }

    void preorderWalkFormula(const ANode* node, std::string& string)
    {
        string += " " + node->toString();
        for(int i = 0; i < node->getChildren().size(); ++ i) preorderWalkFormula(node->getChildren()[i], string);
    }
}

void Tree::loadTreeFromString(std::string& input)
{
    int offset = 0;
    root = ANode::parseFromString(input, offset);
    initialized = true;
}

const std::vector<std::string>& Tree::getVars() const
{
    if (!initialized) return {};
    return root->getVars();
}


std::string Tree::toString() {
    std::stringstream ss;
    printNode(root, "", true, ss);  // root is considered last at top level
    std::string outcome = ss.str() + "\n";
    preorderWalkFormula(root, outcome);
    return outcome;
}

double Tree::calculateTree(std::map<std::string, double>& vars, bool& success)
{
    return (*root)(vars, success);
}

Tree& Tree::operator+=(Tree& other)
{
    if (!initialized)
    {
        root = other.root;
        initialized = true;
    }
    else if (root->getChildren().size() == 0)
        root = other.root;
    else root->replaceLeaf(*(other.root));

    // nie chcemy przy zwalnianiu drzewa zwalniać roota!
    other.root = nullptr;
    
    return *this;
}