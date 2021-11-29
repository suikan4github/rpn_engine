# Compiler option
set(CMAKE_CXX_STANDARD 11)

# Add the executable for the testcase which is using googletest
add_executable(rpn_test test_all.cpp 
                test_basics.cpp 
                test_basic_math.cpp 
                test_double_math.cpp
                test_complex.cpp
                test_basic_bitwise.cpp
                test_complex_bitwise.cpp)
target_link_libraries(rpn_test GTest::GTest GTest::Main ) 

# Add the include directory for test project.
target_include_directories(rpn_test
    PUBLIC ${PROJECT_SOURCE_DIR}/src
)



# Search Google Test test cases and link.
gtest_discover_tests(rpn_test)