//
// Created by val-de-mar on 9/12/21.
//

#ifndef EXPRESSIONMEMENTOCREATION_BUILTINOPERATIONS_H
#define EXPRESSIONMEMENTOCREATION_BUILTINOPERATIONS_H

#define debugv

#include "OperatorOverload.h"
#include "BuiltInTypesId.h"

template<template<class> class Function, class T>
const static OperatorOverload Varianted = {
        .func = [](VariableT &left_v, VariableT &right_v) {
            try {
                auto &left = std::get<T>(left_v);
                auto &right = std::get<T>(right_v);
                auto res = std::make_shared<VariableT>(Function < T > {}(left, right));
                return res;
            } catch (std::bad_variant_access &err) {
#ifdef debugv
                throw;
#endif
            }
        },
        .return_type = getId<decltype(Function<T>{}(std::declval<T &>(), std::declval<T &>()))>
};

template<template<class> class Function, class T>
const static std::pair<const OperatorSignature, OperatorOverload> MapElement = {OperatorSignature{getId<T>, getId<T>}, Varianted<Function, T>};

template<class T>
const static OperatorOverload assign = {
        .func = [](VariableT &left_v, VariableT &right_v) {
            try {
                left_v = right_v;
                auto res = std::make_shared<VariableT>();
                return res;
            } catch (std::bad_variant_access &err) {
#ifdef debugv
                throw;
#endif
            }
        },
        .return_type = getId<void>
};

template<class T>
const static std::pair<const OperatorSignature, OperatorOverload> MapAssign = {OperatorSignature{getId<T>, getId<T>}, assign<T>};

#endif //EXPRESSIONMEMENTOCREATION_BUILTINOPERATIONS_H
