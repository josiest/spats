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

TEST_CASE("is-2d-numeric:custom", "[is_numeric][custom][2D]") {
    REQUIRE(is_2d_numeric<point2fx>);
    REQUIRE(is_2d_numeric<point2fX>);
    REQUIRE(is_2d_numeric<point2iX>);
    REQUIRE(is_2d_numeric<SDL_Point>);

    REQUIRE(not is_2d_numeric<point3iX>);
    REQUIRE(not is_2d_numeric<point3fX>);

    REQUIRE(not is_2d_numeric<point4fX>);
    REQUIRE(not is_2d_numeric<point4iX>);
}

TEST_CASE("is-3d-numeric:custom", "[is_numeric][custom][3D]") {
    REQUIRE(not is_3d_numeric<point2fx>);
    REQUIRE(not is_3d_numeric<point2fX>);
    REQUIRE(not is_3d_numeric<point2iX>);
    REQUIRE(not is_3d_numeric<SDL_Point>);

    REQUIRE(is_3d_numeric<point3fX>);
    REQUIRE(is_3d_numeric<point3iX>);

    REQUIRE(not is_3d_numeric<point4fX>);
    REQUIRE(not is_3d_numeric<point4iX>);

}

TEST_CASE("is-4d-numeric:custom", "[is_numeric][custom][4D]") {
    REQUIRE(not is_4d_numeric<point2fx>);
    REQUIRE(not is_4d_numeric<point2fX>);
    REQUIRE(not is_4d_numeric<point2iX>);
    REQUIRE(not is_4d_numeric<SDL_Point>);

    REQUIRE(not is_4d_numeric<point3fX>);
    REQUIRE(not is_4d_numeric<point3iX>);

    REQUIRE(is_4d_numeric<point4fX>);
    REQUIRE(is_4d_numeric<point4iX>);

}

TEST_CASE("is-2d-numeric:SFML", "[is_numeric][SFML][2D]") {
    REQUIRE(is_2d_numeric<sf::Vector2i>);
    REQUIRE(is_2d_numeric<sf::Vector2u>);
    REQUIRE(is_2d_numeric<sf::Vector2f>);

    REQUIRE(not is_2d_numeric<sf::Vector3i>);
    REQUIRE(not is_2d_numeric<sf::Vector3f>);
}

TEST_CASE("is-3d-numeric:SFML", "[is_numeric][SFML][3D]") {
    REQUIRE(not is_3d_numeric<sf::Vector2i>);
    REQUIRE(not is_3d_numeric<sf::Vector2u>);
    REQUIRE(not is_3d_numeric<sf::Vector2f>);

    REQUIRE(is_3d_numeric<sf::Vector3i>);
    REQUIRE(is_3d_numeric<sf::Vector3f>);
}

TEST_CASE("is-4d-numeric:SFML", "[is_numeric][SFML][4D]") {
    REQUIRE(not is_4d_numeric<sf::Vector2i>);
    REQUIRE(not is_4d_numeric<sf::Vector2u>);
    REQUIRE(not is_4d_numeric<sf::Vector2f>);

    REQUIRE(not is_4d_numeric<sf::Vector3i>);
    REQUIRE(not is_4d_numeric<sf::Vector3f>);
}

TEST_CASE("is-2d-numeric:glm", "[is_numeric][glm][2D]") {
    REQUIRE(is_2d_numeric<glm::vec2>);
    REQUIRE(is_2d_numeric<glm::ivec2>);
    REQUIRE(is_2d_numeric<glm::dvec2>);

    REQUIRE(not is_2d_numeric<glm::vec3>);
    REQUIRE(not is_2d_numeric<glm::ivec3>);
    REQUIRE(not is_2d_numeric<glm::dvec3>);

    REQUIRE(not is_2d_numeric<glm::vec4>);
    REQUIRE(not is_2d_numeric<glm::ivec4>);
    REQUIRE(not is_2d_numeric<glm::dvec4>);
}

TEST_CASE("is-3d-numeric:glm", "[is_numeric][glm][3D]") {
    REQUIRE(not is_3d_numeric<glm::vec2>);
    REQUIRE(not is_3d_numeric<glm::ivec2>);
    REQUIRE(not is_3d_numeric<glm::dvec2>);

    REQUIRE(is_3d_numeric<glm::vec3>);
    REQUIRE(is_3d_numeric<glm::ivec3>);
    REQUIRE(is_3d_numeric<glm::dvec3>);

    REQUIRE(not is_3d_numeric<glm::vec4>);
    REQUIRE(not is_3d_numeric<glm::ivec4>);
    REQUIRE(not is_3d_numeric<glm::dvec4>);
}

TEST_CASE("glm-is-4d-numeric", "[is_numeric][glm][4D]") {
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

TEST_CASE("is-2d-numeric:Eigen", "[is_numeric][Eigen][2D]") {
    REQUIRE(is_2d_numeric<Eigen::Vector2i>);
    REQUIRE(is_2d_numeric<Eigen::Vector2f>);
    REQUIRE(is_2d_numeric<Eigen::Vector2d>);
    REQUIRE(is_2d_numeric<Eigen::Vector2cf>);
    REQUIRE(is_2d_numeric<Eigen::Vector2cd>);

    REQUIRE(not is_2d_numeric<Eigen::Vector3i>);
    REQUIRE(not is_2d_numeric<Eigen::Vector3f>);
    REQUIRE(not is_2d_numeric<Eigen::Vector3d>);
    REQUIRE(not is_2d_numeric<Eigen::Vector3cf>);
    REQUIRE(not is_2d_numeric<Eigen::Vector3cd>);

    REQUIRE(not is_2d_numeric<Eigen::Vector4i>);
    REQUIRE(not is_2d_numeric<Eigen::Vector4f>);
    REQUIRE(not is_2d_numeric<Eigen::Vector4d>);
    REQUIRE(not is_2d_numeric<Eigen::Vector4cf>);
    REQUIRE(not is_2d_numeric<Eigen::Vector4cd>);
}

TEST_CASE("is-3d-numeric:Eigen", "[is_numeric][Eigen][3D]") {
    REQUIRE(not is_3d_numeric<Eigen::Vector2i>);
    REQUIRE(not is_3d_numeric<Eigen::Vector2f>);
    REQUIRE(not is_3d_numeric<Eigen::Vector2d>);
    REQUIRE(not is_3d_numeric<Eigen::Vector2cf>);
    REQUIRE(not is_3d_numeric<Eigen::Vector2cd>);

    REQUIRE(is_3d_numeric<Eigen::Vector3i>);
    REQUIRE(is_3d_numeric<Eigen::Vector3f>);
    REQUIRE(is_3d_numeric<Eigen::Vector3d>);
    REQUIRE(is_3d_numeric<Eigen::Vector3cf>);
    REQUIRE(is_3d_numeric<Eigen::Vector3cd>);

    REQUIRE(not is_3d_numeric<Eigen::Vector4i>);
    REQUIRE(not is_3d_numeric<Eigen::Vector4f>);
    REQUIRE(not is_3d_numeric<Eigen::Vector4d>);
    REQUIRE(not is_3d_numeric<Eigen::Vector4cf>);
    REQUIRE(not is_3d_numeric<Eigen::Vector4cd>);
}

TEST_CASE("is-4d-numeric:Eigen", "[is_numeric][Eigen][4D]") {
    REQUIRE(not is_4d_numeric<Eigen::Vector2i>);
    REQUIRE(not is_4d_numeric<Eigen::Vector2f>);
    REQUIRE(not is_4d_numeric<Eigen::Vector2d>);
    REQUIRE(not is_4d_numeric<Eigen::Vector2cf>);
    REQUIRE(not is_4d_numeric<Eigen::Vector2cd>);

    REQUIRE(not is_4d_numeric<Eigen::Vector3i>);
    REQUIRE(not is_4d_numeric<Eigen::Vector3f>);
    REQUIRE(not is_4d_numeric<Eigen::Vector3d>);
    REQUIRE(not is_4d_numeric<Eigen::Vector3cf>);
    REQUIRE(not is_4d_numeric<Eigen::Vector3cd>);

    REQUIRE(is_4d_numeric<Eigen::Vector4i>);
    REQUIRE(is_4d_numeric<Eigen::Vector4f>);
    REQUIRE(is_4d_numeric<Eigen::Vector4d>);
    REQUIRE(is_4d_numeric<Eigen::Vector4cf>);
    REQUIRE(is_4d_numeric<Eigen::Vector4cd>);
}

TEST_CASE("is-2d-numeric:std::vector", "[is_numeric][std::vector][2D]") {
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

TEST_CASE("is-3d-numeric:std::vector", "[is_numeric][std::vector][3D]") {
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

TEST_CASE("is-4d-numeric:std::vector", "[is_numeric][std::vector][4D]") {
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
