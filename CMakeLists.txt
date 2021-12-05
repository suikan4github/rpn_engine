# To use the FetchContent_* command, version 3.11 is required.
cmake_minimum_required(VERSION 3.11)
project(rpn_test)

# Compiler option
# GoogleTest requirest C++11 or later
set(CMAKE_CXX_STANDARD 11)

# Enable CTest
# This command automatically run the enable_test() command.
# And the CMake specification requires to place the enable_test() at the
# root of the project, to run the ctest correctly. 
# Thus, place this command at the root of project.
include(CTest)


# Subdirectories
add_subdirectory(src)
add_subdirectory(test)

