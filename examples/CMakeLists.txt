cmake_minimum_required(VERSION 3.18)
project(spatula-examples)

# find_package(spatula REQUIRED)
add_executable(string-example strings/foobar.cpp)
add_executable(print-directions directions/print-directions.cpp)
add_executable(random-directions directions/random-directions.cpp)

#target_link_libraries(foobar PUBLIC sp::spatula)
set_target_properties(string-example PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED true)

include_directories(include)