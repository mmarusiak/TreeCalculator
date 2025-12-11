#ifndef RESULT_VOID_H
#define RESULT_VOID_H

#include <vector>
#include <cstddef>


template<typename E>
class Result<void, E> {
public:
    Result();
    Result(E* error);
    Result(std::vector<E*>& errors);
    Result(const Result<void, E>& other);

    ~Result();

    static Result<void, E> ok();
    static Result<void, E> fail(E* error);
    static Result<void, E> fail(std::vector<E*>& errors);

    Result<void, E>& operator=(const Result<void, E>& other);

    bool isSuccess() const;

    std::vector<E*>& getErrors();
    const std::vector<E*>& getErrors() const;

private:
    std::vector<E*> errors;

    void cleanup();
    void copyFrom(const Result<void, E>& other);
};

// Template specialization implementation

template<typename E>
Result<void, E>::Result() {}

template<typename E>
Result<void, E>::Result(E* error) {
    if (error != NULL) {
        errors.push_back(error);
    }
}

template<typename E>
Result<void, E>::Result(std::vector<E*>& errs) {
    for (size_t i = 0; i < errs.size(); ++i) {
        if (errs[i] != NULL) {
            errors.push_back(errs[i]);
        }
    }
}

template<typename E>
Result<void, E>::Result(const Result<void, E>& other) {
    copyFrom(other);
}

template<typename E>
Result<void, E>::~Result() {
    cleanup();
}

template<typename E>
Result<void, E> Result<void, E>::ok() {
    return Result<void, E>();
}

template<typename E>
Result<void, E> Result<void, E>::fail(E* error) {
    return Result<void, E>(error);
}

template<typename E>
Result<void, E> Result<void, E>::fail(std::vector<E*>& errors) {
    return Result<void, E>(errors);
}

template<typename E>
Result<void, E>& Result<void, E>::operator=(const Result<void, E>& other) {
    if (this != &other) {
        cleanup();
        copyFrom(other);
    }
    return *this;
}

template<typename E>
bool Result<void, E>::isSuccess() const {
    return errors.empty();
}

template<typename E>
std::vector<E*>& Result<void, E>::getErrors() {
    return errors;
}

template<typename E>
const std::vector<E*>& Result<void, E>::getErrors() const {
    return errors;
}

template<typename E>
void Result<void, E>::cleanup() {
    for (size_t i = 0; i < errors.size(); ++i) {
        if (errors[i] != NULL) {
            delete errors[i];
        }
    }
    errors.clear();
}

template<typename E>
void Result<void, E>::copyFrom(const Result<void, E>& other) {
    for (size_t i = 0; i < other.errors.size(); ++i) {
        if (other.errors[i] != NULL) {
            errors.push_back(new E(*other.errors[i]));
        }
    }
}

#endif
