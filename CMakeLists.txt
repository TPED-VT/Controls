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
set(HID_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/HIDs/include)
set(HMI_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/HMI/include)
set(MC_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Motor_Control/include)

###################################
# Use the following as a template #
###################################
# Create the library for Control Loop functionality
add_library(ControlLoopLib Control_Loop/src/ControlLoop.cpp)
target_include_directories(ControlLoopLib PRIVATE ${INCLUDE_DIR})
###################################

# Create the main executable
add_executable(TPED_Controls main.cpp)
target_link_libraries(TPED_Controls PRIVATE ControlLoopLib)# The other libraries can be added on here
target_include_directories(TPED_Controls PRIVATE ${INCLUDE_DIR})

# Enable testing
enable_testing()

# Create the test executable
add_executable(OverallTests test/test.cpp)
target_link_libraries(OverallTests PRIVATE ControlLoopLib)
target_include_directories(OverallTests PRIVATE ${INCLUDE_DIR})

# Register the test
add_test(NAME OverallTests COMMAND OverallTests)

