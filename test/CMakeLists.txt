
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Boost REQUIRED)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(test ${SOURCES})

target_link_libraries(test PRIVATE ${CONAN_LIBS})
target_include_directories(test PRIVATE
    ${CONAN_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${spatula_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include)
