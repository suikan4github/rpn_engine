# Google Test requires C++11
set(CMAKE_CXX_STANDARD 11)


# List all source file in this directory
file(GLOB TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Add the executable for the testcase which is using googletest
add_executable(rpn_test 
                ${TEST_SRC})

# Add the include directory for test project.
target_include_directories(rpn_test PUBLIC 
                        ${PROJECT_SOURCE_DIR}/src
)

# Which library have to be linked?
target_link_libraries(rpn_test 
                        gtest_main
                        rpn_engine
                        ) 

# Find and integrate the Google Test package

# Load the FetchContent module
# New in CMake 3.11
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

# Search test cases and link 
# New in CMake 3.10
gtest_discover_tests(rpn_test)