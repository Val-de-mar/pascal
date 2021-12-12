//
// Created by val-de-mar on 8/12/21.
//

#include "Expression.h"
#include <iostream>

std::string FunctionExpression::calculate(VariableManager &manager) {
    std::vector<std::string> arg_names;
    arg_names.reserve(arguments.size());
    for (auto & argument : arguments) {
        arg_names.push_back(argument->calculate(manager));
    }
    return manager.exec(name, arg_names);
}

std::string BinaryOperation::calculate(VariableManager &manager) {
    auto h =  left->calculate(manager);
    auto h2 = right->calculate(manager);
    return manager.exec(name, h, h2);
}

BinaryOperation::BinaryOperation(std::string name_, std::unique_ptr<Expression> left_exp,
                                 std::unique_ptr<Expression> right_exp) :
        name(std::move(name_)),
        left(std::move(left_exp)),
        right(std::move(right_exp)) {

}

std::string AtomExpression::calculate(VariableManager &manager) {
    return name;
}

std::string CycleExpression::calculate(VariableManager &manager) {
    while (std::get<bool>(*(manager.getVar(condition->calculate(manager))))) {
        code->calculate(manager);
    }
    return manager.newRvalue(getId<void>, std::make_shared<VariableT>());
}

CycleExpression::CycleExpression(std::unique_ptr<Expression> condition, std::unique_ptr<Expression> code) :
        condition(std::move(condition)),
        code(std::move(code)) {}

std::string ConditionExpression::calculate(VariableManager &manager) {
    if (std::get<bool>(*(manager.getVar(condition->calculate(manager))))) {
        if_branch->calculate(manager);
    } else {
        else_branch->calculate(manager);
    }
    return manager.newRvalue(getId<void>, std::make_shared<VariableT>());
}

ConditionExpression::ConditionExpression(std::unique_ptr<Expression> condition, std::unique_ptr<Expression> if_branch,
                                         std::unique_ptr<Expression> else_branch) :
        condition(std::move(condition)),
        if_branch(std::move(if_branch)),
        else_branch(std::move(else_branch)){}

std::string SequenceExpression::calculate(VariableManager &manager) {
    for (auto & i: code) {
        i->calculate(manager);
    }
    return manager.newRvalue(getId<void>, std::make_shared<VariableT>());
}

void SequenceExpression::push_back(std::unique_ptr<Expression> next) {
    code.push_back(std::move(next));
}

std::string ValueExpression::calculate(VariableManager &manager) {
    return manager.newRvalue(type, val);
}
