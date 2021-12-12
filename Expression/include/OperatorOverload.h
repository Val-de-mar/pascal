//
// Created by val-de-mar on 9/12/21.
//

#ifndef EXPRESSIONMEMENTOCREATION_OPERATOROVERLOAD_H
#define EXPRESSIONMEMENTOCREATION_OPERATOROVERLOAD_H

#include "VariableT.h"
#include <functional>
#include <memory>

struct OperatorOverload {
    std::function<std::shared_ptr<VariableT>(VariableT&, VariableT&)> func;
    size_t return_type;
};

struct OperatorSignature {
    size_t left_type;
    size_t right_type;
    bool operator < (const OperatorSignature& other) const;
};
#endif //EXPRESSIONMEMENTOCREATION_OPERATOROVERLOAD_H
