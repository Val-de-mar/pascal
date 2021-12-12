//
// Created by val-de-mar on 8/12/21.
//

#ifndef EXPRESSIONMEMENTOCREATION_EXPRESSION_H
#define EXPRESSIONMEMENTOCREATION_EXPRESSION_H

#include <string>
#include <utility>
#include <vector>
#include <memory>
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

class SequenceExpression: public Expression {
public:
    std::vector<std::unique_ptr<Expression>> code;
    SequenceExpression() = default;
    std::string calculate(VariableManager &manager) override;
    void push_back(std::unique_ptr<Expression> next);
};


class CycleExpression: public Expression {
public:
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Expression> code;
    CycleExpression(std::unique_ptr<Expression> condition,
                    std::unique_ptr<Expression> code);
    std::string calculate(VariableManager &manager) override;
};

class ConditionExpression: public Expression {
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


#endif //EXPRESSIONMEMENTOCREATION_EXPRESSION_H
