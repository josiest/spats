find_package(Catch2 REQUIRED)

file(GLOB vector_tests vectors/*.cpp)
add_executable(test_vectors ${vector_tests})
target_link_libraries(test_vectors PRIVATE Catch2::Catch2WithMain sp::spatula)

set_target_properties(test_vectors PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED true)   
