//
// Created by val-de-mar on 9/12/21.
//

#ifndef EXPRESSIONMEMENTOCREATION_VARIABLEMANAGER_H
#define EXPRESSIONMEMENTOCREATION_VARIABLEMANAGER_H

#include <unordered_map>
#include <vector>
#include "CustomType.h"
#include "UniTypeStorage.h"
#include "OperatorManager.h"
#include "CallableManager.h"

struct EmptyVariableManager {
};

class VariableManager {
public:
    std::vector<UniTypeStorage<Infinitive>> storage;
    std::unordered_map<std::string, size_t> types;
    std::vector<UniTypeStorage<Temporary>> temporary;

    OperatorManager operators;
    CallableManager callable;

public:
    std::shared_ptr<VariableT> getVar(const std::string &name);


    VariableManager() : storage(builtInIdNumber), temporary(builtInIdNumber), operators(), callable() {}

    VariableManager(EmptyVariableManager) : storage(builtInIdNumber), temporary(builtInIdNumber), operators(EmptyOperatorManager()),
                        callable(EmptyCallableManager()) {}

    std::string exec(const std::string &operator_name,
                     const std::string &operand_left,
                     const std::string &operand_right);

    std::string exec(const std::string &name, const std::vector<std::string> &arg_names);

    void declare(const std::string &name, size_t type, const std::shared_ptr<VariableT> &value);

    void declareFunction(std::string name, FunctionSignature sign, FunctionOverload func);

    bool remove(const std::string& name);

    std::string newRvalue(size_t type, const std::shared_ptr<VariableT> &value);
};


#endif //EXPRESSIONMEMENTOCREATION_VARIABLEMANAGER_H
