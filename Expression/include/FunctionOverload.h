//
// Created by val-de-mar on 12/12/21.
//

#ifndef EXPRESSIONMEMENTOCREATION_FUNCTIONOVERLOAD_H
#define EXPRESSIONMEMENTOCREATION_FUNCTIONOVERLOAD_H


#include "VariableT.h"
#include <vector>
#include <functional>
#include <memory>

struct FunctionOverload {
    std::function<std::shared_ptr<VariableT>(std::vector<std::shared_ptr<VariableT>>)> func;
    size_t return_type;
};
struct FunctionSignature {
    std::vector<size_t> signature;
    bool operator < (const FunctionSignature& other) const;
};


#endif //EXPRESSIONMEMENTOCREATION_FUNCTIONOVERLOAD_H
