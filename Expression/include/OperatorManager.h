//
// Created by val-de-mar on 9/12/21.
//

#ifndef EXPRESSIONMEMENTOCREATION_OPERATORMANAGER_H
#define EXPRESSIONMEMENTOCREATION_OPERATORMANAGER_H

#include <unordered_map>
#include <map>
#include <functional>
#include <memory>
#include "VariableT.h"
#include "OperatorOverload.h"
#include "BuiltInOperations.h"
#include "DefaultOperatorManager.h"
#include "OperatorOverloads.h"


class OperatorManager {
    std::unordered_map<std::string, OperatorOverloads> operators;
public:
    OperatorManager() : operators(GetDefaultOperationManager()) {}

    const OperatorOverload &get(const std::string &operator_name, size_t left_type, size_t right_type);
};


#endif //EXPRESSIONMEMENTOCREATION_OPERATORMANAGER_H
