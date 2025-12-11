#ifndef TREE_BUILDER_H
#define TREE_BUILDER_H

#include "../Tree.hpp"
#include "Result.hpp"
#include "Error.hpp"
#include <string>
#include <vector>

class TreeBuilder {
public:

    static Result<Tree*, Error> buildTree(const std::string& expression);
};

#endif
