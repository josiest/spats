# spatula/CMakeLists.txt

cmake_minimum_required(VERSION 3.12)

project(spatula VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# define the include directories and header files
set(spatula_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
list(APPEND spatula_INCLUDE_DIRS ${spatula_INCLUDE_DIR})
file(GLOB_RECURSE spatula_HEADERS ${spatula_INCLUDE_DIR}/*.hpp)

# add cmake directory to cmake path so it can use FindSphinx
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# add test subdir if specified
option(TESTING "Run tests" OFF)
if (TESTING)
    add_compile_definitions(DEBUG)
    add_subdirectory(test)
endif()

# add docs subdir if specified
option(DOCS "Build the documentation" OFF)
if (DOCS)
    add_subdirectory(docs/doxygen)
    add_subdirectory(docs/source)
endif()

add_library(spatula INTERFACE)
