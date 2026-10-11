cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(SafeMode VERSION 1.0.0)

if(NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Set GEODE_SDK environment variable")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

add_library(${PROJECT_NAME} SHARED
    "src/main.cpp"
)

setup_geode_mod(${PROJECT_NAME})
