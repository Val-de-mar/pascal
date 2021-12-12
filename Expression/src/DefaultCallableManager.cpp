//
// Created by val-de-mar on 12/12/21.
//

#include "DefaultCallableManager.h"
#include "BuiltInTypesId.h"
#include <iostream>

auto Writeln = [](std::vector<std::shared_ptr<VariableT>> str) {
    std::cout << get<std::string>(*(str[0])) << '\n';
    return std::make_shared<VariableT>();
};
const static std::vector<size_t> WritelnSignature = {getId<std::string>};

const static FunctionOverloads WritelnMapElem = {
        .overloads = {
                {FunctionSignature{WritelnSignature},
                 FunctionOverload{.func = {Writeln}, .return_type = getId<void>}}
        }
};

auto scan = [](std::vector<std::shared_ptr<VariableT>> str) {
    std::string s;
    std::cin >> s;
    *(str[0]) = s;
    return std::make_shared<VariableT>();
};
const static std::vector<size_t> scanSignature = {getId<std::string>};

const static FunctionOverloads scanMapElem = {
        .overloads = {
                {FunctionSignature{scanSignature},
                 FunctionOverload{.func = {scan}, .return_type = getId<void>}}
        }
};

std::unordered_map<std::string, FunctionOverloads> DefaultCallableManager = {
        {"Writeln", WritelnMapElem},
        {"scan", scanMapElem}
};

std::unordered_map<std::string, FunctionOverloads> GetDefaultCallableManager() {
    return DefaultCallableManager;
}