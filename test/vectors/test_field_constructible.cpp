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
#include <eigen3/Eigen/Dense>
#include <SFML/System.hpp>

using namespace sp;
namespace eig = Eigen;

struct ipoint2x4 { int x, y; };

TEST_CASE("SDL2: field-2d-constructible", "[field_constructible]") {
    REQUIRE(field_2d_constructible<SDL_Point>);
    REQUIRE(field_2d_constructible<ipoint2x4>);
}

TEST_CASE("glm: field-2d-constructble", "[field_constructible]") {
    REQUIRE(field_2d_constructible<glm::vec2>);
    REQUIRE(field_2d_constructible<glm::ivec2>);
    REQUIRE(field_2d_constructible<glm::dvec2>);
    REQUIRE(field_2d_constructible<glm::uvec2>);
}

TEST_CASE("glm: field-3d-constructible", "[field_constructible]") {
    REQUIRE(field_3d_constructible<glm::vec3>);
    REQUIRE(field_3d_constructible<glm::ivec3>);
    REQUIRE(field_3d_constructible<glm::dvec3>);
    REQUIRE(field_3d_constructible<glm::uvec3>);
}

TEST_CASE("glm: field-4d-constructible", "[field_constructible]") {
    REQUIRE(field_4d_constructible<glm::vec4>);
    REQUIRE(field_4d_constructible<glm::ivec4>);
    REQUIRE(field_4d_constructible<glm::dvec4>);
    REQUIRE(field_4d_constructible<glm::uvec4>);
}

TEST_CASE("sfml: field-2d-constructible", "[field_constructible]") {
    REQUIRE(field_2d_constructible<sf::Vector2i>);
    REQUIRE(field_2d_constructible<sf::Vector2u>);
    REQUIRE(field_2d_constructible<sf::Vector2f>);
}

TEST_CASE("sfml: field-3d-constructible", "[field_constructible]") {
    REQUIRE(field_3d_constructible<sf::Vector3i>);
    REQUIRE(field_3d_constructible<sf::Vector3f>);
}

TEST_CASE("eigen: field-2d-constructible", "[field_constructible]") {
    REQUIRE(field_2d_constructible<eig::Vector2i>);
    REQUIRE(field_2d_constructible<eig::Vector2f>);
    REQUIRE(field_2d_constructible<eig::Vector2d>);
    REQUIRE(field_2d_constructible<eig::Vector2cf>);
    REQUIRE(field_2d_constructible<eig::Vector2cd>);
}

TEST_CASE("eigen: field-3d-constructible", "[field_constructible]") {
    REQUIRE(field_3d_constructible<eig::Vector3i>);
    REQUIRE(field_3d_constructible<eig::Vector3f>);
    REQUIRE(field_3d_constructible<eig::Vector3d>);
    REQUIRE(field_3d_constructible<eig::Vector3cf>);
    REQUIRE(field_3d_constructible<eig::Vector3cd>);
}

TEST_CASE("eigen: field-4d-constructible", "[field_constructible]") {
    REQUIRE(field_4d_constructible<eig::Vector4i>);
    REQUIRE(field_4d_constructible<eig::Vector4f>);
    REQUIRE(field_4d_constructible<eig::Vector4d>);
    REQUIRE(field_4d_constructible<eig::Vector4cf>);
    REQUIRE(field_4d_constructible<eig::Vector4cd>);
}

TEST_CASE("std::vector: field-2d-constructible", "[field_constructible]") {
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

TEST_CASE("std::vector: field-3d-constructible", "[field_constructible]") {
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

TEST_CASE("std::vector: field-4d-constructible", "[field_constructible]") {
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

TEST_CASE("std::array: field-2d-constructible", "[field_constructible]") {
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

TEST_CASE("std::array: field-3d-constructible", "[field_constructible]") {
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

TEST_CASE("std::array: field-4d-constructible", "[field_constructible]") {
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

TEST_CASE("not 2d-constructible", "[field_constructible]") {
    REQUIRE(not field_2d_constructible<glm::vec4>);
    REQUIRE(not field_2d_constructible<glm::ivec3>);
    REQUIRE(not field_2d_constructible<glm::uvec4>);
    REQUIRE(not field_2d_constructible<glm::dvec3>);

    REQUIRE(not field_2d_constructible<sf::Vector3i>);
    REQUIRE(not field_2d_constructible<sf::Vector3f>);
}

TEST_CASE("not 3d-constructible", "[field_constructible]") {
    REQUIRE(not field_3d_constructible<glm::vec4>);
    REQUIRE(not field_3d_constructible<glm::ivec2>);
    REQUIRE(not field_3d_constructible<glm::uvec4>);
    REQUIRE(not field_3d_constructible<glm::dvec2>);

    REQUIRE(not field_3d_constructible<sf::Vector2i>);
    REQUIRE(not field_3d_constructible<sf::Vector2f>);
}

TEST_CASE("not 4d-constructible", "[field_constructible]") {
    REQUIRE(not field_4d_constructible<glm::vec3>);
    REQUIRE(not field_4d_constructible<glm::ivec2>);
    REQUIRE(not field_4d_constructible<glm::uvec3>);
    REQUIRE(not field_4d_constructible<glm::dvec2>);

    REQUIRE(not field_4d_constructible<sf::Vector2i>);
    REQUIRE(not field_4d_constructible<sf::Vector2f>);
}
