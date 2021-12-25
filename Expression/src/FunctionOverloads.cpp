//
// Created by val-de-mar on 12/12/21.
//

#include "FunctionOverloads.h"

bool operator < (const std::vector<size_t> &left, const std::vector<size_t> &right) {
    if (left.size() < right.size()) {
        return true;
    }
    if (left.size() > right.size()) {
        return false;
    }
    for (int i = 0; i < left.size(); ++i) {
        if (left[i] < right[i]) {
            return true;
        }
        if (left[i] > right[i]) {
            return false;
        }
    }
    return false;
}

bool operator < (const std::vector<size_t> &left, const FunctionSignature &right) {
    return left < right.signature;
}
bool operator < (const FunctionSignature &left, const std::vector<size_t> &right) {
    return left.signature < right;
}

const FunctionOverload &FunctionOverloads::get(const FunctionSignature &signature) {
    auto iter = overloads.find(signature);
    if (iter == overloads.end()) {
        throw std::out_of_range("There is no such overload for operator ");
    }
    return iter->second;
}


