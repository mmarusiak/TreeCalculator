#include "templates_labs/ResultSerializer.hpp"
#include "templates_labs/Result.hpp"
#include "templates_labs/Error.hpp"
#include "Tree.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

std::string readFile(const std::string& filename) {
    std::ifstream file(filename.c_str());
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main() {
    std::cout << "Test 1: Serialize error result (invalid type)\n";
    Result<int, Error> errorResult = Result<int, Error>::fail(new Error("Invalid input"));
    ResultSerializer::serialize(errorResult, "result_error.txt");
    std::cout << "Content:\n" << readFile("result_error.txt") << std::endl;
    
    std::cout << "\nTest 2: Serialize success result (integer)\n";
    Result<int, Error> successResult = Result<int, Error>::ok(42);
    ResultSerializer::serialize(successResult, "result_success.txt");
    std::cout << "Content:\n" << readFile("result_success.txt") << std::endl;
    
    std::cout << "\nTest 3: Serialize tree result (valid tree)\n";
    Tree* tree = new Tree();
    std::string expr = "+ 5 3";
    tree->loadTreeFromString(expr);
    Result<Tree*, Error> treeResult = Result<Tree*, Error>::ok(tree);
    ResultSerializer::serialize(treeResult, "result_tree.txt");
    std::cout << "Content:\n" << readFile("result_tree.txt") << std::endl;
    
    std::cout << "\nTest 4: Serialize tree with error\n";
    Result<Tree*, Error> treeErrorResult = Result<Tree*, Error>::fail(new Error("Failed to parse tree"));
    ResultSerializer::serialize(treeErrorResult, "result_tree_error.txt");
    std::cout << "Content:\n" << readFile("result_tree_error.txt") << std::endl;
    
    return 0;
}
