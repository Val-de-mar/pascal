//
// Created by val-de-mar on 9/12/21.
//

#include "VariableManager.h"
#include <iostream>

std::shared_ptr<VariableT> VariableManager::getVar(const std::string &name) {
    size_t type;
    {
        auto iter = types.find(name);
        if (iter == types.end()) {
            throw std::out_of_range("The variable " + name + " has not been declared");
        }
        type = iter->second;
    }
    if (name[0] == '.') {
        types.erase(name);
        return temporary[type].get(name);
    } else {
        return storage[type].get(name);
    }
}

std::string VariableManager::exec(const std::string &operator_name, const std::string &operand_left,
                                  const std::string &operand_right) {
    if (!types.contains(operand_left) || ! types.contains(operand_right)) {
        throw std::invalid_argument("there is no such variables for operator " + operator_name);
    }
    auto type_l = types[operand_left];
    auto type_r = types[operand_right];
    auto left = getVar(operand_left);
    auto right = getVar(operand_right);
    const auto &operate =
            operators.get(operator_name, type_l, type_r);
    auto res = operate.func(*left, *right);
    auto ans = newRvalue(operate.return_type, res);
    return ans;
}

void VariableManager::declare(const std::string &name, size_t type, const std::shared_ptr<VariableT> &value) {
    if (types.contains(name)) {
        throw std::invalid_argument("Variable " + name + " has already been declared");
    }

    types.insert({name, type});
    storage[type].insert(name, value);
}

std::string VariableManager::exec(const std::string &name, const std::vector<std::string> &arg_names) {
    std::vector<size_t> signature(0);
    for (int i = 0; i < arg_names.size(); ++i) {
        if (!types.contains(arg_names[i])) {
            throw std::invalid_argument("There is no variable named " + arg_names[i]);
        }
        signature.push_back(types[arg_names[i]]);
    }
    std::vector<std::shared_ptr<VariableT>> args(0);
    for (int i = 0; i < arg_names.size(); ++i) {
        args.push_back(getVar(arg_names[i]));
    }

    const auto &operate =
            callable.get(name, std::move(signature));
    auto res = operate.func(std::move(args));
    auto ans = newRvalue(operate.return_type, res);
    return ans;
}

std::string VariableManager::newRvalue(size_t type, const std::shared_ptr<VariableT> &value) {
    auto ans = temporary[type].giveNew(type, value);
    if (types.contains(ans)) {
        throw std::invalid_argument("Give New Incorrect!");
    }
    types.insert({ans, type});
    return ans;
}
