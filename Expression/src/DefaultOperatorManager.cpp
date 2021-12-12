//
// Created by val-de-mar on 9/12/21.
//
#include "DefaultOperatorManager.h"



std::unordered_map<std::string, OperatorOverloads> DefaultOperatorManager = {
        {"+", {{MapElement<std::plus, int>, MapElement<std::plus, std::string>}}},
        {"-", {{MapElement<std::minus, int>}}},
        {"*", {{MapElement<std::multiplies, int>}}},
        {"/", {{MapElement<std::divides, int>}}},
        {"||", {{MapElement<std::logical_or, bool>}}},
        {"&&", {{MapElement<std::logical_and, bool>}}},
        {":=", {{MapAssign<int>, MapAssign<std::string>}}},
        {"==", {{MapElement<std::equal_to, int>}}},
        {"!=", {{MapElement<std::not_equal_to, int>}}},
        {"<", {{MapElement<std::less, int>}}},
        {"<=", {{MapElement<std::less_equal, int>}}}
};


std::unordered_map<std::string, OperatorOverloads> GetDefaultOperationManager() {
    return DefaultOperatorManager;
}
