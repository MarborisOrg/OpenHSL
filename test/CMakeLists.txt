cmake_minimum_required(VERSION 3.10)
project(MyTaskflowProject)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Set compiler optimization flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-O3 -flto -ffunction-sections -fdata-sections)
    add_link_options(-Wl,--gc-sections)
elseif(MSVC)
    add_compile_options(/O2 /GL)
    add_link_options(/LTCG)
endif()

# Find the Taskflow package
find_package(Taskflow REQUIRED)

# Add the executable
add_executable(my_program taskflow-go.cc)

# Link the Taskflow library
target_link_libraries(my_program PRIVATE Taskflow::Taskflow)
