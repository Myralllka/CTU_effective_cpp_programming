cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME semestral_project)
project(${PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 20)

# Options
set(WARNINGS_AS_ERRORS ON)
set(ENABLE_PVS_STUDIO ON)
#! ENABLE_SANITIZERS is the option for the test builds!
#  Definitely enable it while developing.
#  Disable it for the production builds and before submitting for grading!
set(ENABLE_SANITIZERS ON)

#set(CMAKE_CXX_COMPILER clang++)

# warnings as errors should be imported here.
include(cmake/defaults/CompilerWarnings.cmake)

#! Build release version if not specified otherwise.
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# Include headers
include_directories(include)

# Project source compilation
add_executable(${PROJECT_NAME} src/main.cpp src/tests/test3_copy.cpp src/tests/test4_copy_move.cpp src/tests/test2_constructor.cpp src/tests/test1_default_constructor.cpp src/tests/test5_copy_assignment.cpp src/tests/test6_move_asignment.cpp)
add_executable(test_1 src/tests/test1_default_constructor.cpp)
add_executable(test_2 src/tests/test2_constructor.cpp)
add_executable(test_3 src/tests/test3_copy.cpp)
add_executable(test_4 src/tests/test4_copy_move.cpp)
add_executable(test_5 src/tests/test5_copy_assignment.cpp)
add_executable(test_6 src/tests/test6_move_asignment.cpp)
add_executable(test_7 src/tests/test7_swap.cpp)

# Add external packages
#find_package(Boost 1.71.0 COMPONENTS program_options REQUIRED)
#include_directories(${Boost_INCLUDE_DIR})
#target_link_libraries(${PROJECT_NAME} Boost::program_options)

# set output directory (bin)
set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#####################################
# Define ALL_TARGETS variable to use in PVS and Sanitizers
set(ALL_TARGETS ${PROJECT_NAME} test_1 test_2 test_3 test_4 test_5 test_6 test_7)

# Include fixed CMake configuration
include(cmake/config.cmake)
