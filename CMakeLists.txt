# ROOT CMAKELISTS FILE
# FOR MAIN USE ONLY

cmake_minimum_required(VERSION 3.10)

# Set CMake Standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project name
project(TPED_Controls)

# Include directories
set(CL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Control_Loop/include)
set(DR_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Dragon/include)

# Create the library for Electric Car functionality
add_library(CompuTronLib src/computron.cpp)
target_include_directories(CompuTronLib PRIVATE ${INCLUDE_DIR})

# Create the main executable
add_executable(CompuTron src/main.cpp)
target_link_libraries(CompuTron PRIVATE CompuTronLib)
target_include_directories(CompuTron PRIVATE ${INCLUDE_DIR})

# Enable testing
enable_testing()

# Create the test executable
add_executable(studentTests test/test.cpp)
target_link_libraries(studentTests PRIVATE CompuTronLib)
target_include_directories(studentTests PRIVATE ${INCLUDE_DIR})

# Register the test
add_test(NAME studentTests COMMAND studentTests)

