cmake_minimum_required(VERSION 3.20)

project(Test LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE Release)

message(STATUS "Current source directory: ${CMAKE_CURRENT_SOURCE_DIR}")

set(PROPERTIES_FILE "${CMAKE_CURRENT_SOURCE_DIR}/.properties")

if(EXISTS ${PROPERTIES_FILE})
    message(STATUS "Found properties file: ${PROPERTIES_FILE}")
else()
    message(FATAL_ERROR "Properties file not found: ${PROPERTIES_FILE}")
endif()

function(read_properties_file filename)
    file(READ ${filename} properties_content)
    string(REPLACE "\n" ";" properties_list ${properties_content})
    foreach(property ${properties_list})
        string(STRIP ${property} stripped_property)  
        if(stripped_property MATCHES "^(.*)=(.*)$")
            set(var_name ${CMAKE_MATCH_1})
            set(var_value ${CMAKE_MATCH_2})
            set(${var_name} ${var_value} PARENT_SCOPE)
        endif()
    endforeach()
endfunction()

read_properties_file(${PROPERTIES_FILE})

if(DEFINED VCPKG_ROOT)
    include(${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
else()
    message(FATAL_ERROR "VCPKG_ROOT is not defined in the properties file.")
endif()

add_executable(main main.cc)

# Find and link libraries
find_package(fmt CONFIG REQUIRED)
target_link_libraries(main PRIVATE fmt::fmt)

find_package(Taskflow CONFIG REQUIRED)
target_link_libraries(main PRIVATE Taskflow::Taskflow)

# Optional: Add include directories if needed
# target_include_directories(main PRIVATE ${YOUR_INCLUDE_DIRS})

if(MSVC)
    target_compile_options(main PRIVATE /O2 /arch:AVX2)
else()
    target_compile_options(main PRIVATE -O3 -march=native)
    target_compile_options(main PRIVATE -flto)
endif()
