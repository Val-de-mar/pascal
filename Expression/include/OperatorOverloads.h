//
// Created by val-de-mar on 9/12/21.
//

#ifndef EXPRESSIONMEMENTOCREATION_OPERATOROVERLOADS_H
#define EXPRESSIONMEMENTOCREATION_OPERATOROVERLOADS_H

#include <map>
#include "OperatorOverload.h"
#include <iostream>


class OperatorOverloads {
public:
    std::map<OperatorSignature, OperatorOverload> overloads;

    const OperatorOverload& get(OperatorSignature signature);

    inline const OperatorOverload& get(size_t left_type, size_t right_type) {
        return get({left_type, right_type});
    }
};



#endif //EXPRESSIONMEMENTOCREATION_OPERATOROVERLOADS_H
