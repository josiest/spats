find_package(Catch2 REQUIRED)

# find libraries with predefined vector types
find_package(glm REQUIRED)
find_package(SFML 2.5 COMPONENTS system REQUIRED)
find_package(SDL2 REQUIRED)
find_package(Eigen3 REQUIRED)

file(GLOB vector_tests vectors/*.cpp)
add_executable(test_vectors ${vector_tests})
target_link_libraries(test_vectors PRIVATE
    Catch2::Catch2WithMain
    sp::spatula
    glm::glm sfml-system SDL2)

set_target_properties(test_vectors PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED true)   
