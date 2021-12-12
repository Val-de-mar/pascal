//
// Created by val-de-mar on 9/12/21.
//

#ifndef EXPRESSIONMEMENTOCREATION_UNITYPESTORAGE_H
#define EXPRESSIONMEMENTOCREATION_UNITYPESTORAGE_H

#define debugv


#include <unordered_map>
#include <variant>
#include <memory>
#include <set>
#include <iostream>
#include "VariableT.h"

enum StorageLifetime {
    Infinitive = true,
    Temporary = false
};

template<bool Lifetime>
struct FreeArchive;

template<>
struct FreeArchive<Temporary> {
    std::set<std::string> free_names;
};

template<>
struct FreeArchive<Infinitive> {
};

template<bool Lifetime>
class UniTypeStorage {
    std::unordered_map<std::string, std::shared_ptr<VariableT>> dictionary;
    FreeArchive<Lifetime> archive;

    std::string generate_name(size_t type);
public:

    UniTypeStorage() = default;

    auto get(const std::string &name);

    bool contains(const std::string &name);


    void insert(const std::string &name, const std::shared_ptr<VariableT> &element);

    std::string giveNew(size_t type, const std::shared_ptr<VariableT>& ptr);
};


#endif //EXPRESSIONMEMENTOCREATION_UNITYPESTORAGE_H
