//
// Created by val-de-mar on 13/12/21.
//

#ifndef PARSEREXAMPLE_FREEARCHIEVE_H
#define PARSEREXAMPLE_FREEARCHIEVE_H
#include <set>

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

#endif //PARSEREXAMPLE_FREEARCHIEVE_H
