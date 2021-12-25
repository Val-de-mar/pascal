//
// Created by val-de-mar on 12/12/21.
//

#include "DefaultCallableManager.h"
#include "BuiltInTypesId.h"
#include <iostream>

template<class T>
auto Writeln = [](std::vector<std::shared_ptr<VariableT>> str) {
    std::cout << std::get<T>(*(str[0])) << '\n';
    return std::make_shared<VariableT>();
};

const static FunctionOverloads WritelnMapElem = {
        .overloads = {
                {FunctionSignature{{getId<std::string>}},
                 FunctionOverload{.func = {Writeln<std::string>}, .return_type = getId<void>}},
                {FunctionSignature{{getId<int>}},
                 FunctionOverload{.func = {Writeln<int>}, .return_type = getId<void>}}

        }
};

template<class T>
auto scan = [](std::vector<std::shared_ptr<VariableT>> str) {
    T s;
    std::cin >> s;
    *(str[0]) = s;
    return std::make_shared<VariableT>();
};

const static FunctionOverloads scanMapElem = {
        .overloads = {
                {FunctionSignature{{getId<std::string>}},
                 FunctionOverload{.func = {scan<std::string>}, .return_type = getId<void>}},
                {FunctionSignature{{getId<int>}},
                 FunctionOverload{.func = {scan<int>}, .return_type = getId<void>}}
        }
};

std::unordered_map<std::string, FunctionOverloads> DefaultCallableManager = {
        {"Writeln", WritelnMapElem},
        {"scan", scanMapElem}
};

std::unordered_map<std::string, FunctionOverloads> GetDefaultCallableManager() {
    return DefaultCallableManager;
}
