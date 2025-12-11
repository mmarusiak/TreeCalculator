/**
 * Examples of using Result<T, E> template with TreeCalculator
 * 
 * This file demonstrates the usage patterns of the Result template
 * for error handling in expression tree building and evaluation.
 */

#include "Result.hpp"
#include "ResultVoid.hpp"
#include "Error.hpp"
#include "TreeBuilder.hpp"
#include "../Tree.hpp"
#include <iostream>
#include <map>

/**
 * Example 1: Simple calculation with Result
 * Demonstrates implicit conversion using constructors
 */
Result<double, Error> divide(double dividend, double divisor) {
    if (divisor == 0.0) {
        // Implicit conversion: Error* -> Result<double, Error>
        return new Error("Cannot divide by zero");
    }
    
    // Implicit conversion: double -> Result<double, Error>
    return dividend / divisor;
}

/**
 * Example 2: Building a tree from user input
 * Demonstrates explicit success/failure with cOk() and cFail()
 */
Result<ANode*, Error> buildTreeFromInput(const std::string& expression) {
    Result<ANode*, Error> result = TreeBuilder::buildTree(expression);
    
    if (result.isSuccess()) {
        return Result<ANode*, Error>::ok(result.getValue());
    } else {
        return result;  // Propagate errors
    }
}

/**
 * Example 3: Operation with void return type
 * Demonstrates Result<void, E> specialization
 */
Result<void, Error> saveTreeToFile(const std::string& filename, ANode* tree) {
    if (tree == NULL) {
        return Result<void, Error>::fail(
            new Error("Cannot save null tree")
        );
    }
    
    // ... save logic ...
    
    return Result<void, Error>::ok();
}

/**
 * Example 4: Multiple errors handling
 */
void exampleMultipleErrors() {
    Result<double, Error> result = divide(10.0, 0.0);
    
    if (!result.isSuccess()) {
        std::vector<Error*>& errors = result.getErrors();
        for (size_t i = 0; i < errors.size(); ++i) {
            std::cout << "Error: " << errors[i]->getDescription() << std::endl;
        }
    }
}

/**
 * Example 5: Expression evaluation with error handling
 */
void exampleEvaluationWithErrorHandling() {
    // Create variable map
    std::map<std::string, double> variables;
    variables["x"] = 5.0;
    variables["y"] = 2.0;
    
    // Build tree from expression
    Result<ANode*, Error> treeResult = TreeBuilder::buildTree("+ x y");
    
    if (treeResult.isSuccess()) {
        ANode* tree = treeResult.getValue();
        bool evalSuccess = false;
        double result = (*tree)(variables, evalSuccess);
        
        if (evalSuccess) {
            std::cout << "Result: " << result << std::endl;
        } else {
            std::cout << "Evaluation failed" << std::endl;
        }
        
        delete tree;
    } else {
        std::cout << "Tree building failed:" << std::endl;
        const std::vector<Error*>& errors = treeResult.getErrors();
        for (size_t i = 0; i < errors.size(); ++i) {
            std::cout << "  - " << errors[i]->getDescription() << std::endl;
        }
    }
}

// Note: These are example function signatures showing how to use Result<T, E>
// In actual implementation, you would integrate these with your existing Tree class
