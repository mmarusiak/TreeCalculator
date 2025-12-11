#include "Error.hpp"

Error::Error() : description("") {}

Error::Error(const std::string& desc) : description(desc) {}

Error::Error(const Error& other) : description(other.description) {}

Error::~Error() {}

Error& Error::operator=(const Error& other) {
    if (this != &other) {
        description = other.description;
    }
    return *this;
}

const std::string& Error::getDescription() const {
    return description;
}

void Error::setDescription(const std::string& desc) {
    description = desc;
}
