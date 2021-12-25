//
// Created by val-de-mar on 12/12/21.
//

#ifndef EXPRESSIONMEMENTOCREATION_FUNCTIONOVERLOADS_H
#define EXPRESSIONMEMENTOCREATION_FUNCTIONOVERLOADS_H


#include <map>
#include "FunctionOverload.h"

class FunctionOverloads {
public:
    std::map<FunctionSignature, FunctionOverload> overloads;

    const FunctionOverload& get(const FunctionSignature &signature);

    inline const FunctionOverload& get(std::vector<size_t> signature) {
        return get(FunctionSignature{std::move(signature)});
    }
};


#endif //EXPRESSIONMEMENTOCREATION_FUNCTIONOVERLOADS_H
