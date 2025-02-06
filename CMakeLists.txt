cmake_minimum_required(VERSION 3.10)
project(Controls)

# Require a C++17 compiler for all targets
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "C:/Users/ricar/Documents/OpenCV/opencv/build")
# find_package(OpenCV REQUIRED)

# Include directories from OpenCV
include_directories(${OpenCV_INCLUDE_DIRS})

# Add executable for the main project
add_executable(Controls projectmap.cpp)
target_compile_options(Controls PRIVATE -Werror -Wall -Wextra -Wconversion -Wnarrowing -Wpedantic -Wno-sign-compare -Wno-unused-variable)
target_link_libraries(Controls PRIVATE ${OpenCV_LIBS})

# Fetch and include Catch2 for testing
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0 # or a later release
)
FetchContent_MakeAvailable(Catch2)
