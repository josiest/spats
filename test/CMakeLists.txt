
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB SOURCES *.cpp)
add_executable(test ${SOURCES})

target_link_libraries(test PRIVATE kdtree ${CONAN_LIBS})
target_include_directories(test PRIVATE ${CONAN_INCLUDE_DIRS})
