//
// Created by val-de-mar on 12/12/21.
//

#include "CallableManager.h"

const FunctionOverload &CallableManager::get(const std::string &name, std::vector<size_t> signature) {
    auto iter = operators.find(name);
    if (iter == operators.end()) {
        throw std::out_of_range("There is no operator " + name);
    }
    return iter->second.get(std::move(signature));
}
