# Project Parameters.
include("parameters.cmake")

# File name of main(), if needed
set(MAIN_FILE_PATTERN ".*/main.cpp$")

# Do not edit the lines below 

set(TEST_LIBRARY_NAME ${MY_LIBRARY_NAME} PARENT_SCOPE)


# List up all source files including main.cpp
file(GLOB ALL_SRCS "*.cpp")

# Remove the "main file" from list to create a library for test
set( LIB_SRCS ${ALL_SRCS})                                  # create a new list as copy
list(FILTER LIB_SRCS EXCLUDE REGEX ${MAIN_FILE_PATTERN})    # Filter out the main file

# Library for testing ( without main file)
add_library(${MY_LIBRARY_NAME} STATIC
    ${LIB_SRCS})

add_executable("exec_${MY_LIBRARY_NAME}" 
    ${ALL_SRCS})


