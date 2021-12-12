//
// Created by val-de-mar on 9/12/21.
//
#pragma once

#include <unordered_map>
#include "OperatorOverloads.h"
#include "BuiltInOperations.h"

std::unordered_map<std::string, OperatorOverloads> GetDefaultOperationManager();

