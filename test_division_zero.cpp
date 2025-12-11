#include "templates_labs/TreeBuilder.hpp"
#include <iostream>
#include <map>

int main() {
    // Test division by zero
    Result<ANode*, Error> result = TreeBuilder::buildTree("/ 10 0");
    
    if (result.isSuccess()) {
        std::map<std::string, double> vars;
        bool evalSuccess = false;
        double value = (*result.getValue())(vars, evalSuccess);
        
        std::cout << "Evaluation success: " << (evalSuccess ? "true" : "false") << std::endl;
        std::cout << "Result value: " << value << std::endl;
        
        delete result.getValue();
    } else {
        std::cout << "Failed to build tree:" << std::endl;
        const std::vector<Error*>& errors = result.getErrors();
        for (size_t i = 0; i < errors.size(); ++i) {
            std::cout << "  - " << errors[i]->getDescription() << std::endl;
        }
    }
    
    return 0;
}
