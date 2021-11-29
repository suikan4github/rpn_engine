cmake_minimum_required(VERSION 3.10)

# Compiler option
set(CMAKE_CXX_STANDARD 11)

add_library(rpn_engine STATIC
  antichattering.cpp
)
