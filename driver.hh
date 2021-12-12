#pragma once

#include <map>
#include <string>
#include <fstream>
#include <Expression.h>
#include "scanner.h"
#include "parser.hh"


class Driver {
 public:
    Driver();
    VariableManager global;
    std::unordered_map<std::string, size_t> declared_types;
    int parse(const std::string& f);
    std::string file;


    void scan_begin();
    void scan_end();

    bool trace_parsing;
    bool trace_scanning;
    yy::location location;

    friend class Scanner;
    Scanner scanner;
    yy::parser parser;
    bool location_debug;
 private:
    std::ifstream stream;

};

