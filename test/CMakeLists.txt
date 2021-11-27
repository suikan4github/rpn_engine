
# Add the executable for the testcase which is using googletest
add_executable(rpn_test test_all.cpp test_basics.cpp test_basic_math.cpp)
target_link_libraries(rpn_test GTest::GTest GTest::Main ) 

# Add the include directory for test project.
target_include_directories(rpn_test
    PUBLIC ${PROJECT_SOURCE_DIR}/src
)



# Add the test case use the gtest feature.
gtest_discover_tests(rpn_test)