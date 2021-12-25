//
// Created by val-de-mar on 9/12/21.
//

#ifndef EXPRESSIONMEMENTOCREATION_VARIABLET_H
#define EXPRESSIONMEMENTOCREATION_VARIABLET_H

#include <variant>
#include <string>
#include "CustomType.h"

using VariableT = std::variant<int, std::string, bool, CustomType>;

#endif //EXPRESSIONMEMENTOCREATION_VARIABLET_H
