cmake_minimum_required(VERSION 3.21)
project(SafeMode)

find_package(Geode REQUIRED)

add_geode_mod(SafeMode
src/main.cpp
)
