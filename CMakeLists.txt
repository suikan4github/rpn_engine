cmake_minimum_required(VERSION 3.10)
project(rpn_test)

# Compiler option
set(CMAKE_CXX_STANDARD 11)

# Enable CMake 
enable_testing()

# Find and integrate the Google Test package
find_package(GTest REQUIRED)

# Include the CMake file from Google Test
include(GoogleTest)

# Subdirectories
add_subdirectory(src)
add_subdirectory(test)

