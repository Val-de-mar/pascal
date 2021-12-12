//
// Created by val-de-mar on 12/12/21.
//

#ifndef EXPRESSIONMEMENTOCREATION_CALLABLEMANAGER_H
#define EXPRESSIONMEMENTOCREATION_CALLABLEMANAGER_H

#include <unordered_map>
#include <map>
#include <functional>
#include <memory>
#include "FunctionOverload.h"
#include "FunctionOverloads.h"
#include "DefaultCallableManager.h"

class CallableManager {
    std::unordered_map<std::string, FunctionOverloads> operators;
public:
    CallableManager() : operators(GetDefaultCallableManager()) {}

    const FunctionOverload &get(const std::string &name, std::vector<size_t> signature);
};


#endif //EXPRESSIONMEMENTOCREATION_CALLABLEMANAGER_H
