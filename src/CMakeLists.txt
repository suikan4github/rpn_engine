# Project Parameters.

# The PROJECT_NAME_STRING must be identical witht the project name of the ABOVE diredtory.
# If this directory is included by other directory, the library name is fiexed as PROJECT_NAME_STRING
set(PROJECT_NAME_STRING rpn_engine)
# File name of main()
set(MAIN_FILE_PATTERN ".*/main.cpp$")

# Do not edit the lines below 

# List up all source files including main.cpp
file(GLOB ALL_SRCS *.cpp)
message(${ALL_SRCS})

# If this directory is included by above direcotry
if (${PROJECT_NAME} STREQUAL ${PROJECT_NAME_STRING})
    # Build an application
    if(  DEFINED EXECUTABLE_NAME)
        add_executable(${EXECUTABLE_NAME} ${ALL_SRCS})
    endif()
else()
    # Enforce the name
    set(TEST_LIBRARY_NAME ${PROJECT_NAME_STRING})
endif()

# Remove the "main file" from list to create a library for test
set( LIB_SRCS ${ALL_SRCS})                                  # create a new list as copy
list(FILTER LIB_SRCS EXCLUDE REGEX ${MAIN_FILE_PATTERN})    # Filter out the main file

# Library for testing ( without main file)
add_library(${TEST_LIBRARY_NAME} STATIC
    ${LIB_SRCS})
