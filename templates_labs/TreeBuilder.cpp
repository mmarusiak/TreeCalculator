#include "TreeBuilder.hpp"
#include "../node/ANode.hpp"
#include <cctype>

// Trim function
static std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

Result<Tree*, Error> TreeBuilder::buildTree(const std::string& expression) {
    std::string trimmed = trim(expression);
    
    // Empty expression error
    if (trimmed.empty()) {
        Error* error = new Error("Expression cannot be empty");
        Result<Tree*, Error> result(error);
        return result;
    }
    
    int offset = 0;
    ANode* rootNode = ANode::parseFromString(trimmed, offset);
    
    if (rootNode == NULL) {
        Error* error = new Error("Failed to parse expression");
        Result<Tree*, Error> result(error);
        return result;
    }
    
    // Check if entire string was consumed (allowing trailing whitespace)
    while (offset < (int)trimmed.length() && std::isspace(trimmed[offset])) {
        offset++;
    }
    
    if (offset != (int)trimmed.length()) {
        delete rootNode;
        Error* error = new Error("Unexpected characters in expression");
        Result<Tree*, Error> result(error);
        return result;
    }
    
    Tree* tree = new Tree();
    std::string expr = expression;
    tree->loadTreeFromString(expr);
    
    Result<Tree*, Error> result(tree);
    return result;
}
