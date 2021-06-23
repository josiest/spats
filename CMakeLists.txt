cmake_minimum_required(VERSION 3.10)

project(spatula VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(spatula_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)

option(TESTING "Run tests" OFF)
if(TESTING)
    add_subdirectory(test)
endif()

add_library(spatula INTERFACE)
target_include_directories(spatula INTERFACE include)
