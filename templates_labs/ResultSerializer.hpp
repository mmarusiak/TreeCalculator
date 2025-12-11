#ifndef RESULT_SERIALIZER_H
#define RESULT_SERIALIZER_H

#include "Result.hpp"
#include "ResultVoid.hpp"
#include "Error.hpp"
#include "../Tree.hpp"
#include <string>
#include <fstream>

class ResultSerializer {
public:
    template<typename T>
    static void serialize(const Result<T, Error>& result, const std::string& filename) {
        std::ofstream file(filename.c_str());
        
        if (!file.is_open()) {
            return;
        }
        
        if (result.isSuccess()) {
            file << "Status: SUCCESS\n";
        } else {
            file << "Status: ERROR\n";
            const std::vector<Error*>& errors = result.getErrors();
            for (size_t i = 0; i < errors.size(); ++i) {
                file << "Error: " << errors[i]->getDescription() << "\n";
            }
        }
        
        file.close();
    }
    
    static void serialize(const Result<Tree*, Error>& result, const std::string& filename) {
        std::ofstream file(filename.c_str());
        
        if (!file.is_open()) {
            return;
        }
        
        if (result.isSuccess()) {
            file << "Status: SUCCESS\n";
            file << "Tree: " << result.getValue()->toString() << "\n";
        } else {
            file << "Status: ERROR\n";
            const std::vector<Error*>& errors = result.getErrors();
            for (size_t i = 0; i < errors.size(); ++i) {
                file << "Error: " << errors[i]->getDescription() << "\n";
            }
        }
        
        file.close();
    }
    
    // Specialization for Result<void, Error>
    static void serialize(const Result<void, Error>& result, const std::string& filename) {
        std::ofstream file(filename.c_str());
        
        if (!file.is_open()) {
            return;
        }
        
        if (result.isSuccess()) {
            file << "Status: SUCCESS\n";
        } else {
            file << "Status: ERROR\n";
            const std::vector<Error*>& errors = result.getErrors();
            for (size_t i = 0; i < errors.size(); ++i) {
                file << "Error: " << errors[i]->getDescription() << "\n";
            }
        }
        
        file.close();
    }
};

#endif
