#ifndef ERROR_H
#define ERROR_H

#include <string>

/**
 * Class representing an error with description
 */
class Error {
private:
    std::string description;

public:
    Error();
    Error(const std::string& desc);
    Error(const Error& other);
    ~Error();

    Error& operator=(const Error& other);

    const std::string& getDescription() const;
    void setDescription(const std::string& desc);
};

#endif
