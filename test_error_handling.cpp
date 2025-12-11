#include "templates_labs/TreeBuilder.hpp"
#include <iostream>
#include <map>

int main() {
    std::cout << "Test 1: Division by zero during evaluation\n" << std::endl;
    
    Result<ANode*, Error> result = TreeBuilder::buildTree("/ 10 0");
    
    if (result.isSuccess()) {
        std::cout << "Tree built successfully\n" << std::endl;
        
        std::map<std::string, double> vars;
        bool evalSuccess = false;
        double value = (*result.getValue())(vars, evalSuccess);
        
        if (!evalSuccess) {
            std::cout << "Evaluation failed with division by zero\n" << std::endl;
            std::cout << "Return value: " << value << std::endl;
        }
        
        delete result.getValue();
    }
    
    std::cout << "\nTest 2: Invalid expression (no operands)\n" << std::endl;
    
    Result<ANode*, Error> badResult = TreeBuilder::buildTree("");
    
    if (!badResult.isSuccess()) {
        std::cout << "Tree building failed (expected):\n" << std::endl;
        const std::vector<Error*>& errors = badResult.getErrors();
        for (size_t i = 0; i < errors.size(); ++i) {
            std::cout << "Error: " << errors[i]->getDescription() << std::endl;
        }
    }
    
    std::cout << "\nTest 3: Valid expression but missing variable\n" << std::endl;
    
    Result<ANode*, Error> varResult = TreeBuilder::buildTree("+ x 5");
    
    if (varResult.isSuccess()) {
        std::cout << "Tree built successfully\n" << std::endl;
        
        std::map<std::string, double> vars;
        // Note: 'x' is not defined
        bool evalSuccess = false;
        double value = (*varResult.getValue())(vars, evalSuccess);
        
        std::cout << "Evaluation success: " << (evalSuccess ? "true" : "false") << std::endl;
        std::cout << "Result: " << value << std::endl;
        
        delete varResult.getValue();
    }
    
    return 0;
}
