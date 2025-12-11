/**
 * Compilation:
 * clang++ -std=c++11 -g test_main.cpp node/ANode.cpp node/NumberNode.cpp node/OperatorNode.cpp node/VarNode.cpp Tree.cpp templates/Error.cpp templates/TreeBuilder.cpp -o full_test
 * 
 * Run:
 * ./full_test
 */

#include "templates_labs/Tests.hpp"

int main() {
    runAllTests();
    return 0;
}
