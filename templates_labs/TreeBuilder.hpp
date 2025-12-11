#ifndef TREE_BUILDER_H
#define TREE_BUILDER_H

#include "../node/ANode.hpp"
#include "Result.hpp"
#include "Error.hpp"
#include <string>
#include <vector>

class TreeBuilder {
public:
    /**
     * Returns Result with ANode* on success or Error on failure
     */
    static Result<ANode*, Error> buildTree(const std::string& expression);
};

#endif
