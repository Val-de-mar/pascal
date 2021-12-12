//
// Created by val-de-mar on 12/12/21.
//

#include "FunctionOverload.h"

bool FunctionSignature::operator<(const FunctionSignature &other) const {
    if (signature.size() < other.signature.size()) {
        return true;
    }
    if (signature.size() > other.signature.size()) {
        return false;
    }
    for (int i = 0; i < signature.size(); ++i) {
        if (signature[i] < other.signature[i]) {
            return true;
        }
        if (signature[i] > other.signature[i]) {
            return false;
        }
    }
    return false;
}
