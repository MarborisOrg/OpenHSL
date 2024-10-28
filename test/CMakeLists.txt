cmake_minimum_required(VERSION 3.10)
project(MyTaskflowProject)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the Taskflow package
find_package(Taskflow REQUIRED)

# Add the executable
add_executable(my_program taskflow-go.cc)

# Link the Taskflow library
target_link_libraries(my_program PRIVATE Taskflow::Taskflow)
