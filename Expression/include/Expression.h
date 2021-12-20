//
// Created by val-de-mar on 8/12/21.
//

#ifndef EXPRESSIONMEMENTOCREATION_EXPRESSION_H
#define EXPRESSIONMEMENTOCREATION_EXPRESSION_H

#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <unordered_set>
#include "VariableManager.h"


class Expression {
public:
    virtual std::string calculate(VariableManager &manager) = 0;
};

class FunctionExpression : public Expression {
public:
    FunctionExpression(std::string name_, std::vector<std::unique_ptr<Expression>> args) : name(std::move(name_)),
                                                                                           arguments(std::move(args)) {}

    std::string name;
    std::vector<std::unique_ptr<Expression>> arguments;

    virtual std::string calculate(VariableManager &manager);
};

class BinaryOperation : public Expression {
public:
    std::string name;
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

    BinaryOperation(std::string name_,
                    std::unique_ptr<Expression> left_exp,
                    std::unique_ptr<Expression> right_exp);


    virtual std::string calculate(VariableManager &manager);
};

class AtomExpression : public Expression {
public:
    AtomExpression(std::string name_) : name(std::move(name_)) {}

    std::string name;

    std::string calculate(VariableManager &manager) override;
};

class ValueExpression : public Expression {
public:
    ValueExpression(size_t type, std::shared_ptr<VariableT> val) : type(type),
                                                                   val(std::move(val)) {}

    size_t type;
    std::shared_ptr<VariableT> val;

    std::string calculate(VariableManager &manager) override;
};

class SequenceExpression : public Expression {
public:
    std::vector<std::unique_ptr<Expression>> code;

    SequenceExpression() = default;

    std::string calculate(VariableManager &manager) override;

    void push_back(std::unique_ptr<Expression> next);
};


class CycleExpression : public Expression {
public:
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Expression> code;

    CycleExpression(std::unique_ptr<Expression> condition,
                    std::unique_ptr<Expression> code);

    std::string calculate(VariableManager &manager) override;
};

class ConditionExpression : public Expression {
public:
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Expression> if_branch;
    std::unique_ptr<Expression> else_branch;

    ConditionExpression(std::unique_ptr<Expression> condition,
                        std::unique_ptr<Expression> if_branch,
                        std::unique_ptr<Expression> else_branch
    );

    std::string calculate(VariableManager &manager) override;
};

class CustomFunction {
public:
    std::string self_name;
    size_t return_type;
    mutable VariableManager local;
    mutable std::unique_ptr<Expression> commands;
    std::vector<std::string> arg_names;
    std::vector<size_t> arg_types;
    std::vector<std::string> local_names;
    std::vector<size_t> local_types;

    CustomFunction(std::string self_name, size_t return_type, VariableManager manager, std::unique_ptr<Expression> commands, std::vector<std::string> arg_names, std::vector<size_t> arg_types, std::vector<std::string> local_names, std::vector<size_t> local_types)
            : self_name(std::move(self_name)),
              return_type(return_type),
              local(std::move(manager)),
              commands(std::move(commands)),
              arg_names(std::move(arg_names)),
              arg_types(std::move(arg_types)),
              local_names(std::move(local_names)),
              local_types(std::move(local_types)) {
    }

    std::shared_ptr<VariableT> operator()(const std::vector<std::shared_ptr<VariableT>> & values) const {
        local.declare(self_name, return_type, std::make_shared<VariableT>());
        for(int i = 0; i < values.size() && i < arg_names.size(); ++i) {
            auto ptr = std::make_shared<VariableT>(*values[i]);
            local.declare(arg_names[i], arg_types[i], ptr);
        }
        for(int i = 0; i < local_names.size(); ++i) {
            auto ptr = std::make_shared<VariableT>();
            local.declare(local_names[i], local_types[i], ptr);
        }
        auto tmp = commands->calculate(local);
        local.getVar(tmp);
        for (int i = 0; i < values.size() && i < arg_names.size(); ++i) {
            local.remove(arg_names[i]);
        }
        for (int i = 0; i < local_names.size(); ++i) {
            local.remove(local_names[i]);
        }
        auto ans = local.getVar(self_name);
        local.remove(self_name);
        return ans;
    }
};


#endif //EXPRESSIONMEMENTOCREATION_EXPRESSION_H
