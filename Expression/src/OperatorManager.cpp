//
// Created by val-de-mar on 9/12/21.
//

#include "OperatorManager.h"


const OperatorOverload &OperatorManager::get(const std::string &operator_name, size_t left_type, size_t right_type) {
    auto iter = operators.find(operator_name);
    if (iter == operators.end()) {
        throw std::out_of_range("There is no operator " + operator_name);
    }
    return iter->second.get(left_type, right_type);
}
