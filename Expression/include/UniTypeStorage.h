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
#include "FreeArchieve.h"

template<bool Lifetime>
class UniTypeStorage {
    std::unordered_map<std::string, std::shared_ptr<VariableT>> dictionary;
    FreeArchive<Lifetime> archive;

    std::string generate_name(size_t type) {
        static_assert(!Lifetime);
        if (archive.free_names.empty()) {
            return "." + std::to_string(dictionary.size()) + "_" + std::to_string(type);
        }
        auto iter = archive.free_names.begin();
        auto ans = *iter;
        archive.free_names.erase(iter);
        return ans;
    }
public:

    UniTypeStorage() = default;

    std::shared_ptr<VariableT> get(const std::string &name) {
        auto iter = dictionary.find(name);
        if (iter == dictionary.end()) {
            throw std::out_of_range("There is no such variable of that type");
        }
        if constexpr(Lifetime) {
            return iter->second;
        } else {
            auto copy = iter->second;
            dictionary.erase(iter);
            archive.free_names.insert(name);
            return copy;
        }
    }

    bool contains(const std::string &name) {
        return dictionary.find(name) != dictionary.end();
    }


    void insert(const std::string &name, const std::shared_ptr<VariableT> &element) {
        static_assert(Lifetime);
        if (dictionary.contains(name)) {
            throw std::invalid_argument("You try to insert variable, that already exists");
        }
        dictionary.insert({name, element});
    }


    std::string giveNew(size_t type, const std::shared_ptr<VariableT>& ptr) {
        static_assert(!Lifetime);
        auto name = generate_name(type);
#ifdef debugv
        if (dictionary.contains(name)) {
            throw std::invalid_argument("###DEBUG### already existing name in temporary storage");
        }
#endif
        dictionary.insert({name, ptr});
        return name;
    }

};


#endif //EXPRESSIONMEMENTOCREATION_UNITYPESTORAGE_H
