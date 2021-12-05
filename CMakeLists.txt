cmake_minimum_required(VERSION 3.14)
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

include(FetchContent)

FetchContent_Declare(
  	googletest
  	GIT_REPOSITORY https://github.com/google/googletest.git
  	GIT_TAG release-1.10.0
)

FetchContent_MakeAvailable(googletest)