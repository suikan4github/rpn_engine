cmake_minimum_required(VERSION 3.10)
project(rpn_test)

# Enable the testing features.
enable_testing()

# To use the googletest
find_package(GTest REQUIRED)

# Enable the GoogleTest integration.
include(GoogleTest)

# Subdirectories
# add_subdirectory(src)
add_subdirectory(test)

