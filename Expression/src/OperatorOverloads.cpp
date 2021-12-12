//
// Created by val-de-mar on 9/12/21.
//

#include "OperatorOverloads.h"
#include <iostream>

const OperatorOverload &OperatorOverloads::get(OperatorSignature signature) {
    auto iter = overloads.find(signature);
    if (iter == overloads.end()) {
        throw std::out_of_range("There is no such overload for operator ");
    }
    return iter->second;
}

