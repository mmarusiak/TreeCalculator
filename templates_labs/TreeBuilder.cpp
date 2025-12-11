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

Result<ANode*, Error> TreeBuilder::buildTree(const std::string& expression) {
    std::string trimmed = trim(expression);
    
    // Empty expression error
    if (trimmed.empty()) {
        Error* error = new Error("Expression cannot be empty");
        Result<ANode*, Error> result(error);
        // Don't delete - Result takes ownership
        return result;
    }
    
    int offset = 0;
    ANode* tree = ANode::parseFromString(trimmed, offset);
    
    if (tree == NULL) {
        Error* error = new Error("Failed to parse expression");
        Result<ANode*, Error> result(error);
        // Don't delete - Result takes ownership
        return result;
    }
    
    // Check if entire string was consumed (allowing trailing whitespace)
    while (offset < (int)trimmed.length() && std::isspace(trimmed[offset])) {
        offset++;
    }
    
    if (offset != (int)trimmed.length()) {
        delete tree;
        Error* error = new Error("Unexpected characters in expression");
        Result<ANode*, Error> result(error);
        // Don't delete - Result takes ownership
        return result;
    }
    
    Result<ANode*, Error> result(tree);
    return result;
}
