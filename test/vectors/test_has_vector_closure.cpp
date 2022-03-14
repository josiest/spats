#include <catch2/catch.hpp>
#include "spatula/vectors.hpp"

#include <SDL2/SDL.h>
#include <SFML/System.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <Eigen/Dense>

#include <vector>
#include <complex>
#include <string>

using namespace sp;

TEST_CASE("has-vector-closure:SDL", "[has_vector_closure][SDL]") {
    REQUIRE(not has_vector_closure<SDL_Point>);
    REQUIRE(not has_vector_closure<SDL_Rect>);
    REQUIRE(not has_vector_closure<SDL_Color>);
}

TEST_CASE("has-vector-closure:SFML", "[has_vector_closure][SFML]") {
    REQUIRE(has_vector_closure<sf::Vector2u>);
    REQUIRE(has_vector_closure<sf::Vector2i>);
    REQUIRE(has_vector_closure<sf::Vector2f>);
    REQUIRE(has_vector_closure<sf::Vector3i>);
    REQUIRE(has_vector_closure<sf::Vector3f>);
}

TEST_CASE("has-vector-closure:Eigen", "[has_vector_closure][Eigen]") {
    REQUIRE(has_vector_closure<Eigen::Vector2i>);
    REQUIRE(has_vector_closure<Eigen::Vector2f>);
    REQUIRE(has_vector_closure<Eigen::Vector2d>);
    REQUIRE(has_vector_closure<Eigen::Vector2cf>);
    REQUIRE(has_vector_closure<Eigen::Vector2cd>);

    REQUIRE(has_vector_closure<Eigen::Vector3i>);
    REQUIRE(has_vector_closure<Eigen::Vector3f>);
    REQUIRE(has_vector_closure<Eigen::Vector3d>);
    REQUIRE(has_vector_closure<Eigen::Vector3cf>);
    REQUIRE(has_vector_closure<Eigen::Vector3cd>);

    REQUIRE(has_vector_closure<Eigen::Vector4i>);
    REQUIRE(has_vector_closure<Eigen::Vector4f>);
    REQUIRE(has_vector_closure<Eigen::Vector4d>);
    REQUIRE(has_vector_closure<Eigen::Vector4cf>);
    REQUIRE(has_vector_closure<Eigen::Vector4cd>);
}

TEST_CASE("has-vector-closure:glm", "[has_vector_closure][glm]") {
    REQUIRE(has_vector_closure<glm::vec2>);
    REQUIRE(has_vector_closure<glm::ivec2>);
    REQUIRE(has_vector_closure<glm::uvec2>);
    REQUIRE(has_vector_closure<glm::dvec2>);

    REQUIRE(has_vector_closure<glm::vec3>);
    REQUIRE(has_vector_closure<glm::ivec3>);
    REQUIRE(has_vector_closure<glm::uvec3>);
    REQUIRE(has_vector_closure<glm::dvec3>);

    REQUIRE(has_vector_closure<glm::vec4>);
    REQUIRE(has_vector_closure<glm::ivec4>);
    REQUIRE(has_vector_closure<glm::uvec4>);
    REQUIRE(has_vector_closure<glm::dvec4>);
}

TEST_CASE("has-vector-closure:std::vector",
          "[has_vector_closure][std::vector]") {

    REQUIRE(not has_vector_closure<std::vector<int>>);
    REQUIRE(not has_vector_closure<std::vector<float>>);
    REQUIRE(not has_vector_closure<std::vector<std::complex<double>>>);
    REQUIRE(not has_vector_closure<std::vector<std::string>>);
}

TEST_CASE("has-vector-closure:std::string",
          "[has_vector_closure][std::string]") {

    REQUIRE(not has_vector_closure<std::string>);
    REQUIRE(not has_vector_closure<std::wstring>);
    REQUIRE(not has_vector_closure<std::u8string>);
    REQUIRE(not has_vector_closure<std::u16string>);
    REQUIRE(not has_vector_closure<std::u32string>);
}
