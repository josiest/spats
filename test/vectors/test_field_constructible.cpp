#include <catch2/catch.hpp>
#include "spatula/vectors.hpp"

#include <cstdint>
#include <vector>
#include <array>
#include <string>

#include <SDL2/SDL.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <Eigen/Dense>
#include <SFML/System.hpp>

namespace test_field_constructible {
struct ipoint2x { int x, y; };
}

using namespace sp;
using namespace test_field_constructible;

TEST_CASE("field-2d-constructible:custom",
          "[field_constructible][custom][2D]") {

    REQUIRE(field_2d_constructible<ipoint2x>);
}

TEST_CASE("field-2d-constructible:SDL",
          "[field_constructible][SDL][2D]") {

    REQUIRE(field_2d_constructible<SDL_Point>);
}

TEST_CASE("field-2d-constructble:glm",
          "[field_constructible][glm][2D]") {

    REQUIRE(field_2d_constructible<glm::vec2>);
    REQUIRE(field_2d_constructible<glm::ivec2>);
    REQUIRE(field_2d_constructible<glm::dvec2>);
    REQUIRE(field_2d_constructible<glm::uvec2>);
}

TEST_CASE("field-3d-constructible:glm",
          "[field_constructible][glm][3D]") {

    REQUIRE(field_3d_constructible<glm::vec3>);
    REQUIRE(field_3d_constructible<glm::ivec3>);
    REQUIRE(field_3d_constructible<glm::dvec3>);
    REQUIRE(field_3d_constructible<glm::uvec3>);
}

TEST_CASE("field-4d-constructible:glm",
          "[field_constructible][glm][4D]") {

    REQUIRE(field_4d_constructible<glm::vec4>);
    REQUIRE(field_4d_constructible<glm::ivec4>);
    REQUIRE(field_4d_constructible<glm::dvec4>);
    REQUIRE(field_4d_constructible<glm::uvec4>);
}

TEST_CASE("field-2d-constructible:SFML",
          "[field_constructible][SFML][2D]") {

    REQUIRE(field_2d_constructible<sf::Vector2i>);
    REQUIRE(field_2d_constructible<sf::Vector2u>);
    REQUIRE(field_2d_constructible<sf::Vector2f>);
}

TEST_CASE("field-3d-constructible:SFML",
          "[field_constructible][SFML][3D]") {
    REQUIRE(field_3d_constructible<sf::Vector3i>);
    REQUIRE(field_3d_constructible<sf::Vector3f>);
}

TEST_CASE("field-2d-constructible:Eigen",
          "[field_constructible][Eigen][2D]") {

    REQUIRE(field_2d_constructible<Eigen::Vector2i>);
    REQUIRE(field_2d_constructible<Eigen::Vector2f>);
    REQUIRE(field_2d_constructible<Eigen::Vector2d>);
    REQUIRE(field_2d_constructible<Eigen::Vector2cf>);
    REQUIRE(field_2d_constructible<Eigen::Vector2cd>);
}

TEST_CASE("field-3d-constructible:Eigen",
          "[field_constructible][Eigen][3D]") {

    REQUIRE(field_3d_constructible<Eigen::Vector3i>);
    REQUIRE(field_3d_constructible<Eigen::Vector3f>);
    REQUIRE(field_3d_constructible<Eigen::Vector3d>);
    REQUIRE(field_3d_constructible<Eigen::Vector3cf>);
    REQUIRE(field_3d_constructible<Eigen::Vector3cd>);
}

TEST_CASE("field-4d-constructible:Eigen",
          "[field_constructible][Eigen][4D]") {

    REQUIRE(field_4d_constructible<Eigen::Vector4i>);
    REQUIRE(field_4d_constructible<Eigen::Vector4f>);
    REQUIRE(field_4d_constructible<Eigen::Vector4d>);
    REQUIRE(field_4d_constructible<Eigen::Vector4cf>);
    REQUIRE(field_4d_constructible<Eigen::Vector4cd>);
}

TEST_CASE("field-2d-constructible:std::vector",
          "[field_constructible][std::vector][2D]") {

    REQUIRE(field_2d_constructible<std::vector<std::int8_t>>);
    REQUIRE(field_2d_constructible<std::vector<std::int16_t>>);
    REQUIRE(field_2d_constructible<std::vector<std::int32_t>>);
    REQUIRE(field_2d_constructible<std::vector<std::int64_t>>);

    REQUIRE(field_2d_constructible<std::vector<std::uint8_t>>);
    REQUIRE(field_2d_constructible<std::vector<std::uint16_t>>);
    REQUIRE(field_2d_constructible<std::vector<std::uint32_t>>);
    REQUIRE(field_2d_constructible<std::vector<std::uint64_t>>);

    REQUIRE(field_2d_constructible<std::vector<float>>);
    REQUIRE(field_2d_constructible<std::vector<double>>);
    REQUIRE(field_2d_constructible<std::vector<long double>>);
}

TEST_CASE("field-3d-constructible:std::vector",
          "[field_constructible][std::vector][3D]") {

    REQUIRE(field_3d_constructible<std::vector<std::int8_t>>);
    REQUIRE(field_3d_constructible<std::vector<std::int16_t>>);
    REQUIRE(field_3d_constructible<std::vector<std::int32_t>>);
    REQUIRE(field_3d_constructible<std::vector<std::int64_t>>);

    REQUIRE(field_3d_constructible<std::vector<std::uint8_t>>);
    REQUIRE(field_3d_constructible<std::vector<std::uint16_t>>);
    REQUIRE(field_3d_constructible<std::vector<std::uint32_t>>);
    REQUIRE(field_3d_constructible<std::vector<std::uint64_t>>);

    REQUIRE(field_3d_constructible<std::vector<float>>);
    REQUIRE(field_3d_constructible<std::vector<double>>);
    REQUIRE(field_3d_constructible<std::vector<long double>>);
}

TEST_CASE("field-4d-constructible:std::field",
          "[field_constructible][std::vector][4D]") {

    REQUIRE(field_4d_constructible<std::vector<std::int8_t>>);
    REQUIRE(field_4d_constructible<std::vector<std::int16_t>>);
    REQUIRE(field_4d_constructible<std::vector<std::int32_t>>);
    REQUIRE(field_4d_constructible<std::vector<std::int64_t>>);

    REQUIRE(field_4d_constructible<std::vector<std::uint8_t>>);
    REQUIRE(field_4d_constructible<std::vector<std::uint16_t>>);
    REQUIRE(field_4d_constructible<std::vector<std::uint32_t>>);
    REQUIRE(field_4d_constructible<std::vector<std::uint64_t>>);

    REQUIRE(field_4d_constructible<std::vector<float>>);
    REQUIRE(field_4d_constructible<std::vector<double>>);
    REQUIRE(field_4d_constructible<std::vector<long double>>);
}

TEST_CASE("field-2d-constructible:std::array",
          "[field_constructible][std::array][2D]") {

    REQUIRE(field_2d_constructible<std::array<std::int8_t, 2>>);
    REQUIRE(field_2d_constructible<std::array<std::int16_t, 2>>);
    REQUIRE(field_2d_constructible<std::array<std::int32_t, 2>>);
    REQUIRE(field_2d_constructible<std::array<std::int64_t, 2>>);

    REQUIRE(field_2d_constructible<std::array<std::uint8_t, 2>>);
    REQUIRE(field_2d_constructible<std::array<std::uint16_t, 2>>);
    REQUIRE(field_2d_constructible<std::array<std::uint32_t, 2>>);
    REQUIRE(field_2d_constructible<std::array<std::uint64_t, 2>>);

    REQUIRE(field_2d_constructible<std::array<float, 2>>);
    REQUIRE(field_2d_constructible<std::array<double, 2>>);
    REQUIRE(field_2d_constructible<std::array<long double, 2>>);
}

TEST_CASE("field-3d-constructible:std::array",
          "[field_constructible][std::array][3D]") {

    REQUIRE(field_3d_constructible<std::array<std::int8_t, 3>>);
    REQUIRE(field_3d_constructible<std::array<std::int16_t, 3>>);
    REQUIRE(field_3d_constructible<std::array<std::int32_t, 3>>);
    REQUIRE(field_3d_constructible<std::array<std::int64_t, 3>>);

    REQUIRE(field_3d_constructible<std::array<std::uint8_t, 3>>);
    REQUIRE(field_3d_constructible<std::array<std::uint16_t, 3>>);
    REQUIRE(field_3d_constructible<std::array<std::uint32_t, 3>>);
    REQUIRE(field_3d_constructible<std::array<std::uint64_t, 3>>);

    REQUIRE(field_3d_constructible<std::array<float, 3>>);
    REQUIRE(field_3d_constructible<std::array<double, 3>>);
    REQUIRE(field_3d_constructible<std::array<long double, 3>>);
}

TEST_CASE("field-4d-constructible:std::arry",
          "[field_constructible][std::array][4D]") {

    REQUIRE(field_4d_constructible<std::array<std::int8_t, 4>>);
    REQUIRE(field_4d_constructible<std::array<std::int16_t, 4>>);
    REQUIRE(field_4d_constructible<std::array<std::int32_t, 4>>);
    REQUIRE(field_4d_constructible<std::array<std::int64_t, 4>>);

    REQUIRE(field_4d_constructible<std::array<std::uint8_t, 4>>);
    REQUIRE(field_4d_constructible<std::array<std::uint16_t, 4>>);
    REQUIRE(field_4d_constructible<std::array<std::uint32_t, 4>>);
    REQUIRE(field_4d_constructible<std::array<std::uint64_t, 4>>);

    REQUIRE(field_4d_constructible<std::array<float, 4>>);
    REQUIRE(field_4d_constructible<std::array<double, 4>>);
    REQUIRE(field_4d_constructible<std::array<long double, 4>>);
}
