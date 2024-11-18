cmake_minimum_required(VERSION 3.10)

project(Test)

# C++23
set(CMAKE_CXX_STANDARD 23)

# چاپ مسیر فعلی
message(STATUS "Current source directory: ${CMAKE_CURRENT_SOURCE_DIR}")

# مسیر فایل .properties را مشخص کنید
set(PROPERTIES_FILE "${CMAKE_CURRENT_SOURCE_DIR}/.properties")

# بررسی وجود فایل
if(EXISTS ${PROPERTIES_FILE})
    message(STATUS "Found properties file: ${PROPERTIES_FILE}")
else()
    message(FATAL_ERROR "Properties file not found: ${PROPERTIES_FILE}")
endif()

# تابع برای خواندن فایل .properties
function(read_properties_file filename)
    file(READ ${filename} properties_content)
    string(REPLACE "\n" ";" properties_list ${properties_content})
    foreach(property ${properties_list})
        string(STRIP ${property} stripped_property)  # حذف فضاهای خالی
        if(stripped_property MATCHES "^(.*)=(.*)$")
            set(var_name ${CMAKE_MATCH_1})
            set(var_value ${CMAKE_MATCH_2})
            set(${var_name} ${var_value} PARENT_SCOPE)
        endif()
    endforeach()
endfunction()

# خواندن فایل و تنظیم متغیرها
read_properties_file(${PROPERTIES_FILE})

# حالا می‌توانید از VCPKG_ROOT استفاده کنید
if(DEFINED VCPKG_ROOT)
    include(${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
else()
    message(FATAL_ERROR "VCPKG_ROOT is not defined in the properties file.")
endif()

add_executable(main main.cc)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(main PRIVATE fmt::fmt)

find_package(Taskflow CONFIG REQUIRED)
target_link_libraries(main PRIVATE Taskflow::Taskflow)
