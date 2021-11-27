
# Add the executable for the testcase which is using googletest
add_executable(test_engine test_engine.cpp)
target_link_libraries(test_engine GTest::GTest GTest::Main ) 

# Add the include directory for test project.
target_include_directories(test_engine
    PUBLIC ${PROJECT_SOURCE_DIR}/src
)



# Add the test case use the gtest feature.
gtest_discover_tests(test_engine)