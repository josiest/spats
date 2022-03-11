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

namespace test_semivector {
struct point2iX { int X, Y; };
struct point2dX { double X, Y; };
struct point3fX { float X, Y, Z; };
struct point4uX { unsigned int X, Y, Z, W; };
struct point4fX { float X, Y, Z, W; };
}

using namespace sp;
using namespace test_semivector;

TEST_CASE("semivector2:custom", "[semivector][custom][2D]") {
    REQUIRE(semivector2<point2iX>);
    REQUIRE(semivector2<point2dX>);
    REQUIRE(not semivector2<point3fX>);
    REQUIRE(not semivector2<point4uX>);
    REQUIRE(not semivector2<point4fX>);
}

TEST_CASE("semivector3:custom", "[semivector][custom][3D]") {
    REQUIRE(not semivector3<point2iX>);
    REQUIRE(not semivector3<point2dX>);
    REQUIRE(semivector2<point3fX>);
    REQUIRE(not semivector3<point4uX>);
    REQUIRE(not semivector3<point4fX>);
}

TEST_CASE("semivector4:custom", "[semivector][custom][4D]") {
    REQUIRE(not semivector4<point2iX>);
    REQUIRE(not semivector4<point2dX>);
    REQUIRE(not semivector4<point3fX>);
    REQUIRE(semivector4<point4uX>);
    REQUIRE(semivector4<point4fX>);
}

TEST_CASE("semivector2:SDL", "[semivector][SDL][2D]") {
    REQUIRE(semivector2<SDL_Point>);
}
TEST_CASE("semivector3:SDL", "[semivector][SDL][3D]") {
    REQUIRE(not semivector3<SDL_Point>);
}
TEST_CASE("semivector4:SDL", "[semivector][SDL][4D]") {
    REQUIRE(not semivector4<SDL_Point>);
}

TEST_CASE("semivector2:sfml", "[semivector][SFML][2D]") {
    REQUIRE(semivector2<sf::Vector2i>);
    REQUIRE(semivector2<sf::Vector2u>);
    REQUIRE(semivector2<sf::Vector2f>);

    REQUIRE(not semivector2<sf::Vector3i>);
    REQUIRE(not semivector2<sf::Vector3f>);
}

TEST_CASE("semivector3:sfml", "[semivector][SFML][3D]") {
    REQUIRE(not semivector3<sf::Vector2i>);
    REQUIRE(not semivector3<sf::Vector2u>);
    REQUIRE(not semivector3<sf::Vector2f>);

    REQUIRE(semivector3<sf::Vector3i>);
    REQUIRE(semivector3<sf::Vector3f>);
}

TEST_CASE("semivector4:sfml", "[semivector][SFML][4D]") {
    REQUIRE(not semivector4<sf::Vector2i>);
    REQUIRE(not semivector4<sf::Vector2u>);
    REQUIRE(not semivector4<sf::Vector2f>);

    REQUIRE(not semivector4<sf::Vector3i>);
    REQUIRE(not semivector4<sf::Vector3f>);
}

TEST_CASE("semivector2:glm", "[semivector][glm][2D]") {
    REQUIRE(semivector2<glm::vec2>);
    REQUIRE(semivector2<glm::ivec2>);
    REQUIRE(semivector2<glm::dvec2>);

    REQUIRE(not semivector2<glm::vec3>);
    REQUIRE(not semivector2<glm::ivec3>);
    REQUIRE(not semivector2<glm::dvec3>);

    REQUIRE(not semivector2<glm::vec4>);
    REQUIRE(not semivector2<glm::ivec4>);
    REQUIRE(not semivector2<glm::dvec4>);
}

TEST_CASE("semivector3:glm", "[semivector][glm][3D]") {
    REQUIRE(not semivector3<glm::vec2>);
    REQUIRE(not semivector3<glm::ivec2>);
    REQUIRE(not semivector3<glm::dvec2>);

    REQUIRE(semivector3<glm::vec3>);
    REQUIRE(semivector3<glm::ivec3>);
    REQUIRE(semivector3<glm::dvec3>);

    REQUIRE(not semivector3<glm::vec4>);
    REQUIRE(not semivector3<glm::ivec4>);
    REQUIRE(not semivector3<glm::dvec4>);
}

TEST_CASE("semivector4:glm", "[semivector][glm][4D]") {
    REQUIRE(not semivector4<glm::vec2>);
    REQUIRE(not semivector4<glm::ivec2>);
    REQUIRE(not semivector4<glm::dvec2>);

    REQUIRE(not semivector4<glm::vec3>);
    REQUIRE(not semivector4<glm::ivec3>);
    REQUIRE(not semivector4<glm::dvec3>);

    REQUIRE(semivector4<glm::vec4>);
    REQUIRE(semivector4<glm::ivec4>);
    REQUIRE(semivector4<glm::dvec4>);
}

TEST_CASE("semivector2:Eigen", "[semivector][Eigen][2D]") {
    REQUIRE(semivector2<Eigen::Vector2i>);
    REQUIRE(semivector2<Eigen::Vector2f>);
    REQUIRE(semivector2<Eigen::Vector2d>);
    REQUIRE(semivector2<Eigen::Vector2cf>);
    REQUIRE(semivector2<Eigen::Vector2cd>);

    REQUIRE(not semivector2<Eigen::Vector3i>);
    REQUIRE(not semivector2<Eigen::Vector3f>);
    REQUIRE(not semivector2<Eigen::Vector3d>);
    REQUIRE(not semivector2<Eigen::Vector3cf>);
    REQUIRE(not semivector2<Eigen::Vector3cd>);

    REQUIRE(not semivector2<Eigen::Vector4i>);
    REQUIRE(not semivector2<Eigen::Vector4f>);
    REQUIRE(not semivector2<Eigen::Vector4d>);
    REQUIRE(not semivector2<Eigen::Vector4cf>);
    REQUIRE(not semivector2<Eigen::Vector4cd>);
}

TEST_CASE("semivector3:Eigen", "[semivector][Eigen][3D]") {
    REQUIRE(not semivector3<Eigen::Vector2i>);
    REQUIRE(not semivector3<Eigen::Vector2f>);
    REQUIRE(not semivector3<Eigen::Vector2d>);
    REQUIRE(not semivector3<Eigen::Vector2cf>);
    REQUIRE(not semivector3<Eigen::Vector2cd>);

    REQUIRE(semivector3<Eigen::Vector3i>);
    REQUIRE(semivector3<Eigen::Vector3f>);
    REQUIRE(semivector3<Eigen::Vector3d>);
    REQUIRE(semivector3<Eigen::Vector3cf>);
    REQUIRE(semivector3<Eigen::Vector3cd>);

    REQUIRE(not semivector3<Eigen::Vector4i>);
    REQUIRE(not semivector3<Eigen::Vector4f>);
    REQUIRE(not semivector3<Eigen::Vector4d>);
    REQUIRE(not semivector3<Eigen::Vector4cf>);
    REQUIRE(not semivector3<Eigen::Vector4cd>);
}

TEST_CASE("semivector4:Eigen", "[semivector][Eigen][4D]") {
    REQUIRE(not semivector4<Eigen::Vector2i>);
    REQUIRE(not semivector4<Eigen::Vector2f>);
    REQUIRE(not semivector4<Eigen::Vector2d>);
    REQUIRE(not semivector4<Eigen::Vector2cf>);
    REQUIRE(not semivector4<Eigen::Vector2cd>);

    REQUIRE(not semivector4<Eigen::Vector3i>);
    REQUIRE(not semivector4<Eigen::Vector3f>);
    REQUIRE(not semivector4<Eigen::Vector3d>);
    REQUIRE(not semivector4<Eigen::Vector3cf>);
    REQUIRE(not semivector4<Eigen::Vector3cd>);

    REQUIRE(semivector4<Eigen::Vector4i>);
    REQUIRE(semivector4<Eigen::Vector4f>);
    REQUIRE(semivector4<Eigen::Vector4d>);
    REQUIRE(semivector4<Eigen::Vector4cf>);
    REQUIRE(semivector4<Eigen::Vector4cd>);
}

TEST_CASE("semivector2:std::vector", "[semivector][std::vector][2D]") {
    REQUIRE(not semivector2<std::vector<char>>);
    REQUIRE(not semivector2<std::vector<short>>);
    REQUIRE(not semivector2<std::vector<int>>);
    REQUIRE(not semivector2<std::vector<long>>);
    REQUIRE(not semivector2<std::vector<long long>>);

    REQUIRE(not semivector2<std::vector<std::uint8_t>>);
    REQUIRE(not semivector2<std::vector<std::uint16_t>>);
    REQUIRE(not semivector2<std::vector<std::uint32_t>>);
    REQUIRE(not semivector2<std::vector<std::uint64_t>>);

    REQUIRE(not semivector2<std::vector<float>>);
    REQUIRE(not semivector2<std::vector<double>>);
    REQUIRE(not semivector2<std::vector<long double>>);
}

TEST_CASE("semivector3:std::vector", "[semivector][std::vector][3D]") {
    REQUIRE(not semivector3<std::vector<char>>);
    REQUIRE(not semivector3<std::vector<short>>);
    REQUIRE(not semivector3<std::vector<int>>);
    REQUIRE(not semivector3<std::vector<long>>);
    REQUIRE(not semivector3<std::vector<long long>>);

    REQUIRE(not semivector3<std::vector<std::uint8_t>>);
    REQUIRE(not semivector3<std::vector<std::uint16_t>>);
    REQUIRE(not semivector3<std::vector<std::uint32_t>>);
    REQUIRE(not semivector3<std::vector<std::uint64_t>>);

    REQUIRE(not semivector3<std::vector<float>>);
    REQUIRE(not semivector3<std::vector<double>>);
    REQUIRE(not semivector3<std::vector<long double>>);
}

TEST_CASE("semivector4:std::vector", "[semivector][std::vector][4D]") {
    REQUIRE(not semivector4<std::vector<char>>);
    REQUIRE(not semivector4<std::vector<short>>);
    REQUIRE(not semivector4<std::vector<int>>);
    REQUIRE(not semivector4<std::vector<long>>);
    REQUIRE(not semivector4<std::vector<long long>>);

    REQUIRE(not semivector4<std::vector<std::uint8_t>>);
    REQUIRE(not semivector4<std::vector<std::uint16_t>>);
    REQUIRE(not semivector4<std::vector<std::uint32_t>>);
    REQUIRE(not semivector4<std::vector<std::uint64_t>>);

    REQUIRE(not semivector4<std::vector<float>>);
    REQUIRE(not semivector4<std::vector<double>>);
    REQUIRE(not semivector4<std::vector<long double>>);
}
