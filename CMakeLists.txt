# ROOT CMAKELISTS FILE
# FOR MAIN USE ONLY
#
# CONTACT EMILY, EMMA, OR AARON IF YOU NEED TO MAKE 
# ADJUSTMENTS TO THIS FILE
##############################################################
# TODO:
# - Add the libraries for the pi
# 
# AS OF 3/4/2025
#############################################
cmake_minimum_required(VERSION 3.10)

# Set CMake Standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")

# Project name
project(TPED_Controls)
# Check OS
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(FATAL_ERROR "Emily, stop using Linux")
    set(PLATFORM_LINUX TRUE)
    #find_library(I2cLib i2c) # Should be using the wiring pi I2C
    find_library(WiringPiLib wiringPi)
    # TODO: Fix this for linux. The following two lines don't build
    target_compile_definitions(TPED_Controls PRIVATE PLATFORM_LINUX)
    target_link_libraries(TPED_Controls ${WiringPiLib} ${I2cLib})
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Using Windows")
    set(PLATFORM_LINUX FALSE)
else()
    message(FATAL_ERROR "OS Not supported")
endif()


# Include directories
set(CL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Control_Loop)
set(DR_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Dragon)
set(HID_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/HIDs)
set(HMI_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/HMI)
set(MC_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Motor_Control)

######################################################################
# Use the following as a template #
###################################
# The template should used below the ControlLoopLib but before the executable definitions
# 
# add_library({FolderHere}Lib /path/to/file.cpp)    # 'FolderHere' should be Pascal Case (FirstName, LastName, etc.)
# target_include_directories({FolderHere}Lib PRIVATE ${INCLUDE_DIR})
###################################

# Create the library for Control Loop functionality
add_library(ControlLoopLib Control_Loop/ControlLoop.cpp)
target_include_directories(ControlLoopLib PRIVATE ${INCLUDE_DIR})

# Create the library for HID functionality
add_library(HIDLib HIDs/HID.cpp)
target_include_directories(HIDLib PRIVATE ${INCLUDE_DIR})

# Create the library for HMI functionality
add_library(HMILib HMI/HMI.cpp)
target_include_directories(HMILib PRIVATE ${INCLUDE_DIR})

# Create the library for Motor Control functionality
add_library(MotorControlLib Motor_Control/MotorControl.cpp)
target_include_directories(MotorControlLib PRIVATE ${INCLUDE_DIR})

######################################################################
# Use the following as a template #
###################################
# The template should used below the executable definitions but before testing
# 
# add_executable({Executable_Name} path/to/executable.cpp)  # ExecutableName should be unique and Pascal_Case (with underscores)
# target_link_libraries({Executable_Name} PRIVATE {LibraryNeeded}) # LibraryNeeded is the library used to build the executable
# target_include_directories({Executable_Name} PRIVATE ${INCLUDE_DIR})
###################################

# Create the main executable
add_executable(TPED_Controls main.cpp)  # This is where we will put the main file if needed
target_link_libraries(TPED_Controls PRIVATE MotorControlLib)# The other libraries can be added on here
target_include_directories(TPED_Controls PRIVATE ${INCLUDE_DIR})

if(PLATFORM_LINUX)
    add_executable(Blink_Example blink.cpp)
    target_include_directories(TPED_Controls PRIVATE ${INCLUDE_DIR})
endif()

# # Create the Control Loop executable
# add_executable(Control_Loop Control_Loop/src/ControlLoop.cpp)
# target_link_libraries(Control_Loop PRIVATE ControlLoopLib)
# target_include_directories(Control_Loop PRIVATE ${INCLUDE_DIR})

# # Create the Motor Control executable
# add_executable(Motor_Control Motor_Control/src/MotorControl.cpp)
# target_link_libraries(Motor_Control PRIVATE MotorControlLib)
# target_include_directories(Motor_Control PRIVATE ${INCLUDE_DIR})

######################################################################

# Enable testing
enable_testing()

# Create the test executable
add_executable(OverallTests WIN32 test/test.cpp)
target_link_libraries(OverallTests PRIVATE ControlLoopLib)
target_include_directories(OverallTests PRIVATE ${CMAKE_SOURCE_DIR})

# Register the test
add_test(NAME OverallTests COMMAND OverallTests)

