/**
 * Compilation:
 * clang++ -std=c++11 -g test_main.cpp node/ANode.cpp node/NumberNode.cpp node/OperatorNode.cpp node/VarNode.cpp Tree.cpp templates_labs/Error.cpp templates_labs/TreeBuilder.cpp -o full_test
 * 
 * Run:
 * ./full_test
 */

#include "templates_labs/Tests.hpp"

int main() {
    runAllTests();

    //Result<int, int> test = Result<int, int>::ok(5);
    Result<int, char> test2 = Result<int, char>::ok(10);
    return 0;
}
