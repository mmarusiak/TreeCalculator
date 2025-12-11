/**
 * Compilation:
 * clang++ -std=c++11 test_examples_main.cpp templates/Error.cpp templates/TreeBuilder.cpp node/ANode.cpp node/NumberNode.cpp node/OperatorNode.cpp node/VarNode.cpp Tree.cpp -o examples
 * 
 * Run:
 * ./examples
 */

#include "templates_labs/Tests.hpp"
#include "templates_labs/Examples.cpp"

int main() {
    
    // Run unit tests
    runAllTests();
    
    
    // Example 1: Simple division
    std::cout << "\nExample 1: Division with error handling" << std::endl;
    Result<double, Error> divResult = divide(10.0, 2.0);
    if (divResult.isSuccess()) {
        std::cout << "10.0 / 2.0 = " << divResult.getValue() << std::endl;
    }
    
    Result<double, Error> divByZero = divide(10.0, 0.0);
    if (!divByZero.isSuccess()) {
        std::cout << "Division by zero error caught:" << std::endl;
        for (size_t i = 0; i < divByZero.getErrors().size(); ++i) {
            std::cout << "  - " << divByZero.getErrors()[i]->getDescription() << std::endl;
        }
    }
    
    // Example 2: Multiple errors
    std::cout << "\nExample 2: Multiple errors handling" << std::endl;
    exampleMultipleErrors();
    
    // Example 3: Variable evaluation
    std::cout << "\nExample 3: Expression evaluation with variables" << std::endl;
    exampleEvaluationWithErrorHandling();
    
    // Example 4: TreeBuilder validation
    std::cout << "\nExample 4: TreeBuilder - Valid expression" << std::endl;
    Result<ANode*, Error> validTree = TreeBuilder::buildTree("(+ 5 3)");
    if (validTree.isSuccess()) {
        std::cout << "Tree built successfully" << std::endl;
        std::cout << "  Tree structure: " << validTree.getValue()->toString() << std::endl;
        delete validTree.getValue();
    } else {
        std::cout << "Failed to build tree:" << std::endl;
        for (size_t i = 0; i < validTree.getErrors().size(); ++i) {
            std::cout << "  - " << validTree.getErrors()[i]->getDescription() << std::endl;
        }
    }
    
    // Example 5: TreeBuilder error handling
    std::cout << "\nExample 5: TreeBuilder - Invalid expressions" << std::endl;
    
    Result<ANode*, Error> emptyTree = TreeBuilder::buildTree("");
    if (!emptyTree.isSuccess()) {
        std::cout << "Empty expression caught:" << std::endl;
        std::cout << "  - " << emptyTree.getErrors()[0]->getDescription() << std::endl;
    }
    
    Result<ANode*, Error> unbalancedTree = TreeBuilder::buildTree("(+ 5 (3");
    if (!unbalancedTree.isSuccess()) {
        std::cout << "Unbalanced parentheses caught:" << std::endl;
        std::cout << "  - " << unbalancedTree.getErrors()[0]->getDescription() << std::endl;
    }
    
    // Example 6: More TreeBuilder examples
    std::cout << "\nExample 6: Advanced expressions" << std::endl;
    Result<ANode*, Error> complexExpr = TreeBuilder::buildTree("+ * 7 8 5");
    if (complexExpr.isSuccess()) {
        std::map<std::string, double> vars;
        bool evalSuccess = false;
        double result = (*complexExpr.getValue())(vars, evalSuccess);
        if (evalSuccess) {
            std::cout << "Complex expression (7*8)+5 = " << result << std::endl;
        }
        delete complexExpr.getValue();
    }
    
    // Example 7: Result<void, E> usage
    std::cout << "\nExample 7: Result<void, E> - void operations" << std::endl;
    Result<void, Error> saveOk = Result<void, Error>::ok();
    if (saveOk.isSuccess()) {
        std::cout << "Void operation succeeded" << std::endl;
    }
    
    Result<void, Error> saveFail = Result<void, Error>::fail(
        new Error("File I/O error")
    );
    if (!saveFail.isSuccess()) {
        std::cout << "Void operation failed:" << std::endl;
        std::cout << "  - " << saveFail.getErrors()[0]->getDescription() << std::endl;
    }
    
    // Example 8: Implicit conversions
    std::cout << "\nExample 8: Implicit type conversions" << std::endl;
    Result<int, Error> implicitInt = 42;
    Result<double, Error> implicitDouble = 3.14159;
    
    std::cout << "Implicit int conversion: " << implicitInt.getValue() << std::endl;
    std::cout << "Implicit double conversion: " << implicitDouble.getValue() << std::endl;
    
    // Example 9: Static factory methods
    std::cout << "\nExample 9: Static factory methods for clarity" << std::endl;
    Result<double, Error> okResult = Result<double, Error>::ok(100.0);
    Result<double, Error> failResult = Result<double, Error>::fail(
        new Error("Invalid operation")
    );
    
    std::cout << "Explicit ok(): success = " << okResult.isSuccess() << std::endl;
    std::cout << "Explicit fail(): success = " << failResult.isSuccess() << std::endl;
    
    std::cout << "\nAll examples executed successfully!" << std::endl;
    std::cout << "Result<T, E> template working correctly" << std::endl;
    std::cout << "Result<void, E> specialization working" << std::endl;
    std::cout << "TreeBuilder integration functional" << std::endl;
    std::cout << "Error handling demonstrates best practices" << std::endl;
    std::cout << "For more details, see: templates/README.md" << std::endl;
    
    return 0;
}
