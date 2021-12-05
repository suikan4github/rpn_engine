cmake_minimum_required(VERSION 3.14)

# Compiler option
set(CMAKE_CXX_STANDARD 11)

# Add the executable for the testcase which is using googletest
add_executable(rpn_test test_all.cpp
                test_basics.cpp 
                test_basic_math.cpp 
                test_double_math.cpp
                test_complex.cpp
                test_basic_bitwise.cpp
                test_complex_bitwise.cpp
                test_antichattering.cpp)

# Add the include directory for test project.
target_include_directories(rpn_test
    PUBLIC ${PROJECT_SOURCE_DIR}/src
)

# Which library have to be linked?
target_link_libraries(rpn_test 
                        gtest_main
                        rpn_engine
                        ) 

                        # Find and integrate the Google Test package

# Load the FetchContent module
include(FetchContent)

# Declaration of googletest as content
FetchContent_Declare(
  	googletest
  	GIT_REPOSITORY https://github.com/google/googletest.git
  	GIT_TAG release-1.10.0
)

# Fetch the googletest
FetchContent_MakeAvailable(googletest)

# Include the GoogleTest
include(GoogleTest)

# Search Google Test test cases and link to CMake
gtest_discover_tests(rpn_test)