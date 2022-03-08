cmake_minimum_required(VERSION 3.18)
project(foobar)

find_package(spatula REQUIRED)
add_executable(foobar foobar.cpp)

target_link_libraries(foobar PUBLIC sp::spatula)
set_target_properties(foobar PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED true)
