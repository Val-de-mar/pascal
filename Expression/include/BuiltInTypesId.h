//
// Created by val-de-mar on 9/12/21.
//

#ifndef EXPRESSIONMEMENTOCREATION_BUILTINTYPESID_H
#define EXPRESSIONMEMENTOCREATION_BUILTINTYPESID_H
#include <cstdlib>
#include <string>

enum BuiltInTypesId {
    customId = 0,
    voidId = 1,
    intId = 2,
    stringId = 3,
    boolId = 4,
    functionId = 5,
    builtInIdNumber = 6
};

template<class T>
struct GetIdHelper;

template<>
struct GetIdHelper<void> {
    const static size_t id = voidId;
};

template<>
struct GetIdHelper<int> {
    const static size_t id = intId;
};

template<>
struct GetIdHelper<bool> {
    const static size_t id = boolId;
};

template<>
struct GetIdHelper<std::string> {
    const static size_t id = stringId;
};


template<class T>
const static size_t getId = GetIdHelper<T>::id;

const static std::unordered_map<std::string, size_t> defaultTypeTable = {
        {"integer", intId},
        {"string", stringId},
        {"bool", boolId},
        {"custom", customId}
};


#endif //EXPRESSIONMEMENTOCREATION_BUILTINTYPESID_H
