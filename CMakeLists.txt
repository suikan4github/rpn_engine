cmake_minimum_required(VERSION 3.14)
project(rpn_test)

# Compiler option
set(CMAKE_CXX_STANDARD 11)

# Enable CMake 
include(CTest)
enable_testing()

# Subdirectories
add_subdirectory(src)
add_subdirectory(test)

