cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME test)
project(${PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 17)

# Options
option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors." ON)
option(ENABLE_PVS_STUDIO "Check using command-line PVS-Studio." ON)
option(ENABLE_SANITIZERS    "Use sanitizers to detect errors." OFF) # Option for the test builds. Do not use it in the production builds.

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# Include fixed CMake configuration
include(../cmake/config.cmake)

# Include headers
include_directories(include)

# Project source compilation
add_executable(${PROJECT_NAME} src/main.cpp include/optional.h)

# set output directory (bin)
set_target_properties(${PROJECT_NAME}
						PROPERTIES
						RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
