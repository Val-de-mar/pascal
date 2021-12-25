//
// Created by val-de-mar on 13/12/21.
//

#include "OperatorOverload.h"

bool OperatorSignature::operator<(const OperatorSignature &other) const {
    return (left_type != other.left_type) ? (left_type < other.left_type) : (right_type < other.right_type);
}
