cmake_minimum_required(VERSION 3.18)
project(spatula-examples)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

find_package(spatula REQUIRED)
# find_package(spatula REQUIRED COMPONENTS geometry)
add_executable(add_example add_example.cpp)
include_directories(spatula)