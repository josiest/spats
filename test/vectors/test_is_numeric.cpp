#include <catch2/catch.hpp>
#include "spatula/vectors.hpp"

#include <SDL2/SDL.h>
#include <SFML/System.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <Eigen/Dense>
#include "spatula_extensions/eigen.hpp"

#include <vector>
#include <string>

#include <cstdint>

namespace test_is_numeric {
struct point2fx { float x, y; };
struct point2fX { float X, Y; };
struct point3fX { float X, Y, Z; };
struct point4fX { float X, Y, Z, W; };
struct point2iX { int X, Y; };
struct point3iX { int X, Y, Z; };
struct point4iX { int X, Y, Z, W; };
}

using namespace sp;
using namespace test_is_numeric;
namespace eig = Eigen;

TEST_CASE("basic-is-2d-numeric", "[is_numeric]") {
    REQUIRE(is_2d_numeric<point2fx>);
    REQUIRE(is_2d_numeric<point2fX>);
    REQUIRE(is_2d_numeric<point2iX>);
    REQUIRE(is_2d_numeric<SDL_Point>);

    REQUIRE(is_2d_numeric<point3iX>);
    REQUIRE(is_2d_numeric<point3fX>);

    REQUIRE(is_2d_numeric<point4fX>);
    REQUIRE(is_2d_numeric<point4iX>);
}

TEST_CASE("basic-is-3d-numeric", "[is_numeric]") {
    REQUIRE(not is_3d_numeric<point2fx>);
    REQUIRE(not is_3d_numeric<point2fX>);
    REQUIRE(not is_3d_numeric<point2iX>);
    REQUIRE(not is_3d_numeric<SDL_Point>);

    REQUIRE(is_3d_numeric<point3fX>);
    REQUIRE(is_3d_numeric<point3iX>);

    REQUIRE(is_3d_numeric<point4fX>);
    REQUIRE(is_3d_numeric<point4iX>);

}

TEST_CASE("basic-is-4d-numeric", "[is_numeric]") {
    REQUIRE(not is_4d_numeric<point2fx>);
    REQUIRE(not is_4d_numeric<point2fX>);
    REQUIRE(not is_4d_numeric<point2iX>);
    REQUIRE(not is_4d_numeric<SDL_Point>);

    REQUIRE(not is_4d_numeric<point3fX>);
    REQUIRE(not is_4d_numeric<point3iX>);

    REQUIRE(is_4d_numeric<point4fX>);
    REQUIRE(is_4d_numeric<point4iX>);

}

TEST_CASE("sfml-is-2d-numeric", "[is_numeric]") {
    REQUIRE(is_2d_numeric<sf::Vector2i>);
    REQUIRE(is_2d_numeric<sf::Vector2u>);
    REQUIRE(is_2d_numeric<sf::Vector2f>);

    REQUIRE(is_2d_numeric<sf::Vector3i>);
    REQUIRE(is_2d_numeric<sf::Vector3f>);
}

TEST_CASE("sfml-is-3d-numeric", "[is_numeric]") {
    REQUIRE(not is_3d_numeric<sf::Vector2i>);
    REQUIRE(not is_3d_numeric<sf::Vector2u>);
    REQUIRE(not is_3d_numeric<sf::Vector2f>);

    REQUIRE(is_3d_numeric<sf::Vector3i>);
    REQUIRE(is_3d_numeric<sf::Vector3f>);
}

TEST_CASE("sfml-is-4d-numeric", "[is_numeric]") {
    REQUIRE(not is_4d_numeric<sf::Vector2i>);
    REQUIRE(not is_4d_numeric<sf::Vector2u>);
    REQUIRE(not is_4d_numeric<sf::Vector2f>);

    REQUIRE(not is_4d_numeric<sf::Vector3i>);
    REQUIRE(not is_4d_numeric<sf::Vector3f>);
}

TEST_CASE("glm-is-2d-numeric", "[is_numeric]") {
    REQUIRE(is_2d_numeric<glm::vec2>);
    REQUIRE(is_2d_numeric<glm::ivec2>);
    REQUIRE(is_2d_numeric<glm::dvec2>);

    REQUIRE(is_2d_numeric<glm::vec3>);
    REQUIRE(is_2d_numeric<glm::ivec3>);
    REQUIRE(is_2d_numeric<glm::dvec3>);

    REQUIRE(is_2d_numeric<glm::vec4>);
    REQUIRE(is_2d_numeric<glm::ivec4>);
    REQUIRE(is_2d_numeric<glm::dvec4>);
}

TEST_CASE("glm-is-3d-numeric", "[is_numeric]") {
    REQUIRE(not is_3d_numeric<glm::vec2>);
    REQUIRE(not is_3d_numeric<glm::ivec2>);
    REQUIRE(not is_3d_numeric<glm::dvec2>);

    REQUIRE(is_3d_numeric<glm::vec3>);
    REQUIRE(is_3d_numeric<glm::ivec3>);
    REQUIRE(is_3d_numeric<glm::dvec3>);

    REQUIRE(is_3d_numeric<glm::vec4>);
    REQUIRE(is_3d_numeric<glm::ivec4>);
    REQUIRE(is_3d_numeric<glm::dvec4>);
}

TEST_CASE("glm-is-4d-numeric", "[is_numeric]") {
    REQUIRE(not is_4d_numeric<glm::vec2>);
    REQUIRE(not is_4d_numeric<glm::ivec2>);
    REQUIRE(not is_4d_numeric<glm::dvec2>);

    REQUIRE(not is_4d_numeric<glm::vec3>);
    REQUIRE(not is_4d_numeric<glm::ivec3>);
    REQUIRE(not is_4d_numeric<glm::dvec3>);

    REQUIRE(is_4d_numeric<glm::vec4>);
    REQUIRE(is_4d_numeric<glm::ivec4>);
    REQUIRE(is_4d_numeric<glm::dvec4>);
}

TEST_CASE("eigen-is-2d-numeric", "[is_numeric]") {
    REQUIRE(is_2d_numeric<eig::Vector2i>);
    REQUIRE(is_2d_numeric<eig::Vector2f>);
    REQUIRE(is_2d_numeric<eig::Vector2d>);
    REQUIRE(is_2d_numeric<eig::Vector2cf>);
    REQUIRE(is_2d_numeric<eig::Vector2cd>);

    REQUIRE(is_2d_numeric<eig::Vector3i>);
    REQUIRE(is_2d_numeric<eig::Vector3f>);
    REQUIRE(is_2d_numeric<eig::Vector3d>);
    REQUIRE(is_2d_numeric<eig::Vector3cf>);
    REQUIRE(is_2d_numeric<eig::Vector3cd>);

    REQUIRE(is_2d_numeric<eig::Vector4i>);
    REQUIRE(is_2d_numeric<eig::Vector4f>);
    REQUIRE(is_2d_numeric<eig::Vector4d>);
    REQUIRE(is_2d_numeric<eig::Vector4cf>);
    REQUIRE(is_2d_numeric<eig::Vector4cd>);
}

TEST_CASE("eigen-is-3d-numeric", "[is_numeric]") {
    REQUIRE(not is_3d_numeric<eig::Vector2i>);
    REQUIRE(not is_3d_numeric<eig::Vector2f>);
    REQUIRE(not is_3d_numeric<eig::Vector2d>);
    REQUIRE(not is_3d_numeric<eig::Vector2cf>);
    REQUIRE(not is_3d_numeric<eig::Vector2cd>);

    REQUIRE(is_3d_numeric<eig::Vector3i>);
    REQUIRE(is_3d_numeric<eig::Vector3f>);
    REQUIRE(is_3d_numeric<eig::Vector3d>);
    REQUIRE(is_3d_numeric<eig::Vector3cf>);
    REQUIRE(is_3d_numeric<eig::Vector3cd>);

    REQUIRE(is_3d_numeric<eig::Vector4i>);
    REQUIRE(is_3d_numeric<eig::Vector4f>);
    REQUIRE(is_3d_numeric<eig::Vector4d>);
    REQUIRE(is_3d_numeric<eig::Vector4cf>);
    REQUIRE(is_3d_numeric<eig::Vector4cd>);
}

TEST_CASE("eigen-is-4d-numeric", "[is_numeric]") {
    REQUIRE(not is_4d_numeric<eig::Vector2i>);
    REQUIRE(not is_4d_numeric<eig::Vector2f>);
    REQUIRE(not is_4d_numeric<eig::Vector2d>);
    REQUIRE(not is_4d_numeric<eig::Vector2cf>);
    REQUIRE(not is_4d_numeric<eig::Vector2cd>);

    REQUIRE(not is_4d_numeric<eig::Vector3i>);
    REQUIRE(not is_4d_numeric<eig::Vector3f>);
    REQUIRE(not is_4d_numeric<eig::Vector3d>);
    REQUIRE(not is_4d_numeric<eig::Vector3cf>);
    REQUIRE(not is_4d_numeric<eig::Vector3cd>);

    REQUIRE(is_4d_numeric<eig::Vector4i>);
    REQUIRE(is_4d_numeric<eig::Vector4f>);
    REQUIRE(is_4d_numeric<eig::Vector4d>);
    REQUIRE(is_4d_numeric<eig::Vector4cf>);
    REQUIRE(is_4d_numeric<eig::Vector4cd>);
}

TEST_CASE("std::vector-is-2d-numeric", "[is_numeric]") {
    REQUIRE(not is_2d_numeric<std::vector<char>>);
    REQUIRE(not is_2d_numeric<std::vector<short>>);
    REQUIRE(not is_2d_numeric<std::vector<int>>);
    REQUIRE(not is_2d_numeric<std::vector<long>>);
    REQUIRE(not is_2d_numeric<std::vector<long long>>);

    REQUIRE(not is_2d_numeric<std::vector<std::uint8_t>>);
    REQUIRE(not is_2d_numeric<std::vector<std::uint16_t>>);
    REQUIRE(not is_2d_numeric<std::vector<std::uint32_t>>);
    REQUIRE(not is_2d_numeric<std::vector<std::uint64_t>>);

    REQUIRE(not is_2d_numeric<std::vector<float>>);
    REQUIRE(not is_2d_numeric<std::vector<double>>);
    REQUIRE(not is_2d_numeric<std::vector<long double>>);
}

TEST_CASE("std::vector-is-3d-numeric", "[is_numeric]") {
    REQUIRE(not is_3d_numeric<std::vector<char>>);
    REQUIRE(not is_3d_numeric<std::vector<short>>);
    REQUIRE(not is_3d_numeric<std::vector<int>>);
    REQUIRE(not is_3d_numeric<std::vector<long>>);
    REQUIRE(not is_3d_numeric<std::vector<long long>>);

    REQUIRE(not is_3d_numeric<std::vector<std::uint8_t>>);
    REQUIRE(not is_3d_numeric<std::vector<std::uint16_t>>);
    REQUIRE(not is_3d_numeric<std::vector<std::uint32_t>>);
    REQUIRE(not is_3d_numeric<std::vector<std::uint64_t>>);

    REQUIRE(not is_3d_numeric<std::vector<float>>);
    REQUIRE(not is_3d_numeric<std::vector<double>>);
    REQUIRE(not is_3d_numeric<std::vector<long double>>);
}

TEST_CASE("std::vector-is-4d-numeric", "[is_numeric]") {
    REQUIRE(not is_4d_numeric<std::vector<char>>);
    REQUIRE(not is_4d_numeric<std::vector<short>>);
    REQUIRE(not is_4d_numeric<std::vector<int>>);
    REQUIRE(not is_4d_numeric<std::vector<long>>);
    REQUIRE(not is_4d_numeric<std::vector<long long>>);

    REQUIRE(not is_4d_numeric<std::vector<std::uint8_t>>);
    REQUIRE(not is_4d_numeric<std::vector<std::uint16_t>>);
    REQUIRE(not is_4d_numeric<std::vector<std::uint32_t>>);
    REQUIRE(not is_4d_numeric<std::vector<std::uint64_t>>);

    REQUIRE(not is_4d_numeric<std::vector<float>>);
    REQUIRE(not is_4d_numeric<std::vector<double>>);
    REQUIRE(not is_4d_numeric<std::vector<long double>>);
}
