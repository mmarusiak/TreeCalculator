#ifndef TREE_BUILDER_H
#define TREE_BUILDER_H

#include "../node/ANode.hpp"
#include "Result.hpp"
#include "Error.hpp"
#include <string>
#include <vector>

/**
 * TreeBuilder - creates expression trees from strings using Result pattern
 * Parses prefix notation expressions without parentheses (e.g., "+ 5 3")
 */
class TreeBuilder {
public:
    /**
     * Builds a tree from an expression string in prefix notation
     * Format: "operator operand1 operand2" or nested expressions
     * Example: "+ 5 3" means 5 + 3, "+ * 2 3 4" means (2*3) + 4
     * Returns Result with ANode* on success or Error on failure
     */
    static Result<ANode*, Error> buildTree(const std::string& expression);
};

#endif
