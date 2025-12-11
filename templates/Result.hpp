#ifndef RESULT_H
#define RESULT_H

#include <vector>
#include <cstddef>

/**
 * Template class for wrapping result or error
 * T - type of successful result
 * E - type of error
 */
template<typename T, typename E>
class Result {
public:
    Result(const T& value);
    Result(E* error);
    Result(std::vector<E*>& errors);
    Result(const Result<T, E>& other);

    ~Result();

    static Result<T, E> ok(const T& value);
    static Result<T, E> fail(E* error);
    static Result<T, E> fail(std::vector<E*>& errors);

    Result<T, E>& operator=(const Result<T, E>& other);

    bool isSuccess() const;

    T getValue() const;
    std::vector<E*>& getErrors();
    const std::vector<E*>& getErrors() const;

private:
    T* value;
    std::vector<E*> errors;

    void cleanup();
    void copyFrom(const Result<T, E>& other);
};

// Template implementation

template<typename T, typename E>
Result<T, E>::Result(const T& val) : value(NULL) {
    value = new T(val);
}

template<typename T, typename E>
Result<T, E>::Result(E* error) : value(NULL) {
    if (error != NULL) {
        errors.push_back(error);
    }
}

template<typename T, typename E>
Result<T, E>::Result(std::vector<E*>& errs) : value(NULL) {
    for (size_t i = 0; i < errs.size(); ++i) {
        if (errs[i] != NULL) {
            errors.push_back(errs[i]);
        }
    }
}

template<typename T, typename E>
Result<T, E>::Result(const Result<T, E>& other) : value(NULL) {
    copyFrom(other);
}

template<typename T, typename E>
Result<T, E>::~Result() {
    cleanup();
}

template<typename T, typename E>
Result<T, E> Result<T, E>::ok(const T& value) {
    return Result<T, E>(value);
}

template<typename T, typename E>
Result<T, E> Result<T, E>::fail(E* error) {
    return Result<T, E>(error);
}

template<typename T, typename E>
Result<T, E> Result<T, E>::fail(std::vector<E*>& errors) {
    return Result<T, E>(errors);
}

template<typename T, typename E>
Result<T, E>& Result<T, E>::operator=(const Result<T, E>& other) {
    if (this != &other) {
        cleanup();
        copyFrom(other);
    }
    return *this;
}

template<typename T, typename E>
bool Result<T, E>::isSuccess() const {
    return value != NULL && errors.empty();
}

template<typename T, typename E>
T Result<T, E>::getValue() const {
    if (value != NULL) {
        return *value;
    }
    return T();
}

template<typename T, typename E>
std::vector<E*>& Result<T, E>::getErrors() {
    return errors;
}

template<typename T, typename E>
const std::vector<E*>& Result<T, E>::getErrors() const {
    return errors;
}

template<typename T, typename E>
void Result<T, E>::cleanup() {
    if (value != NULL) {
        delete value;
        value = NULL;
    }
    for (size_t i = 0; i < errors.size(); ++i) {
        if (errors[i] != NULL) {
            delete errors[i];
        }
    }
    errors.clear();
}

template<typename T, typename E>
void Result<T, E>::copyFrom(const Result<T, E>& other) {
    if (other.value != NULL) {
        value = new T(*other.value);
    }
    for (size_t i = 0; i < other.errors.size(); ++i) {
        if (other.errors[i] != NULL) {
            errors.push_back(new E(*other.errors[i]));
        }
    }
}

#endif
