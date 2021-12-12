cmake_minimum_required(VERSION 3.16)
project(ExpressionMementoCreation)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -g)

add_library(Expressions SHARED src/Expression.cpp include/Expression.h src/VariableManager.cpp include/VariableManager.h src/CustomType.cpp include/CustomType.h src/UniTypeStorage.cpp include/UniTypeStorage.h include/BuiltInTypesId.h src/OperatorManager.cpp include/OperatorManager.h include/VariableT.h include/BuiltInOperations.h include/OperatorOverload.h include/DefaultOperatorManager.h src/OperatorOverloads.cpp include/OperatorOverloads.h src/DefaultOperatorManager.cpp src/CallableManager.cpp include/CallableManager.h src/FunctionOverloads.cpp include/FunctionOverloads.h src/FunctionOverload.cpp include/FunctionOverload.h src/DefaultCallableManager.cpp include/DefaultCallableManager.h src/OperatorOverload.cpp include/FreeArchieve.h)


target_include_directories(Expressions PUBLIC include)

set_target_properties( Expressions
        PROPERTIES
        PUBLIC_HEADER include/*
)
