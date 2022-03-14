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

TEST_CASE("vector2:SDL", "[vector][SDL][2D]") {
    REQUIRE(not vector2<SDL_Point>);
    REQUIRE(not vector2<SDL_Rect>);
    REQUIRE(not vector2<SDL_Color>);
}

TEST_CASE("vector3:SDL", "[vector][SDL][3D]") {
    REQUIRE(not vector3<SDL_Point>);
    REQUIRE(not vector3<SDL_Rect>);
    REQUIRE(not vector3<SDL_Color>);
}

TEST_CASE("vector4:SDL", "[vector][SDL][4D]") {
    REQUIRE(not vector4<SDL_Point>);
    REQUIRE(not vector4<SDL_Rect>);
    REQUIRE(not vector4<SDL_Color>);
}

TEST_CASE("vector2:SFML", "[vector][SFML][2D]") {
    REQUIRE(vector2<sf::Vector2u>);
    REQUIRE(vector2<sf::Vector2i>);
    REQUIRE(vector2<sf::Vector2f>);

    REQUIRE(not vector2<sf::Vector3i>);
    REQUIRE(not vector2<sf::Vector3f>);
}

TEST_CASE("vector3:SFML", "[vector][SFML][3D]") {
    REQUIRE(not vector3<sf::Vector2u>);
    REQUIRE(not vector3<sf::Vector2i>);
    REQUIRE(not vector3<sf::Vector2f>);

    REQUIRE(vector3<sf::Vector3i>);
    REQUIRE(vector3<sf::Vector3f>);
}

TEST_CASE("vector4:SFML", "[vector][SFML][3D]") {
    REQUIRE(not vector4<sf::Vector2u>);
    REQUIRE(not vector4<sf::Vector2i>);
    REQUIRE(not vector4<sf::Vector2f>);

    REQUIRE(not vector4<sf::Vector3i>);
    REQUIRE(not vector4<sf::Vector3f>);
}

TEST_CASE("vector2:Eigen", "[vector][Eigen][2D]") {
    REQUIRE(vector2<Eigen::Vector2i>);
    REQUIRE(vector2<Eigen::Vector2f>);
    REQUIRE(vector2<Eigen::Vector2d>);
    REQUIRE(vector2<Eigen::Vector2cf>);
    REQUIRE(vector2<Eigen::Vector2cd>);

    REQUIRE(not vector2<Eigen::Vector3i>);
    REQUIRE(not vector2<Eigen::Vector3f>);
    REQUIRE(not vector2<Eigen::Vector3d>);
    REQUIRE(not vector2<Eigen::Vector3cf>);
    REQUIRE(not vector2<Eigen::Vector3cd>);

    REQUIRE(not vector2<Eigen::Vector4i>);
    REQUIRE(not vector2<Eigen::Vector4f>);
    REQUIRE(not vector2<Eigen::Vector4d>);
    REQUIRE(not vector2<Eigen::Vector4cf>);
    REQUIRE(not vector2<Eigen::Vector4cd>);
}

TEST_CASE("vector3:Eigen", "[vector][Eigen][3D]") {
    REQUIRE(not vector3<Eigen::Vector2i>);
    REQUIRE(not vector3<Eigen::Vector2f>);
    REQUIRE(not vector3<Eigen::Vector2d>);
    REQUIRE(not vector3<Eigen::Vector2cf>);
    REQUIRE(not vector3<Eigen::Vector2cd>);

    REQUIRE(vector3<Eigen::Vector3i>);
    REQUIRE(vector3<Eigen::Vector3f>);
    REQUIRE(vector3<Eigen::Vector3d>);
    REQUIRE(vector3<Eigen::Vector3cf>);
    REQUIRE(vector3<Eigen::Vector3cd>);

    REQUIRE(not vector3<Eigen::Vector4i>);
    REQUIRE(not vector3<Eigen::Vector4f>);
    REQUIRE(not vector3<Eigen::Vector4d>);
    REQUIRE(not vector3<Eigen::Vector4cf>);
    REQUIRE(not vector3<Eigen::Vector4cd>);
}

TEST_CASE("vector4:Eigen", "[vector][Eigen][4D]") {
    REQUIRE(not vector4<Eigen::Vector2i>);
    REQUIRE(not vector4<Eigen::Vector2f>);
    REQUIRE(not vector4<Eigen::Vector2d>);
    REQUIRE(not vector4<Eigen::Vector2cf>);
    REQUIRE(not vector4<Eigen::Vector2cd>);

    REQUIRE(not vector4<Eigen::Vector3i>);
    REQUIRE(not vector4<Eigen::Vector3f>);
    REQUIRE(not vector4<Eigen::Vector3d>);
    REQUIRE(not vector4<Eigen::Vector3cf>);
    REQUIRE(not vector4<Eigen::Vector3cd>);

    REQUIRE(vector4<Eigen::Vector4i>);
    REQUIRE(vector4<Eigen::Vector4f>);
    REQUIRE(vector4<Eigen::Vector4d>);
    REQUIRE(vector4<Eigen::Vector4cf>);
    REQUIRE(vector4<Eigen::Vector4cd>);
}

TEST_CASE("vector2:glm", "[vector][glm][2D]") {
    REQUIRE(vector2<glm::vec2>);
    REQUIRE(vector2<glm::ivec2>);
    REQUIRE(vector2<glm::uvec2>);
    REQUIRE(vector2<glm::dvec2>);

    REQUIRE(not vector2<glm::vec3>);
    REQUIRE(not vector2<glm::ivec3>);
    REQUIRE(not vector2<glm::uvec3>);
    REQUIRE(not vector2<glm::dvec3>);

    REQUIRE(not vector2<glm::vec4>);
    REQUIRE(not vector2<glm::ivec4>);
    REQUIRE(not vector2<glm::uvec4>);
    REQUIRE(not vector2<glm::dvec4>);
}

TEST_CASE("vector3:glm", "[vector][glm][3D]") {
    REQUIRE(not vector3<glm::vec2>);
    REQUIRE(not vector3<glm::ivec2>);
    REQUIRE(not vector3<glm::uvec2>);
    REQUIRE(not vector3<glm::dvec2>);

    REQUIRE(vector3<glm::vec3>);
    REQUIRE(vector3<glm::ivec3>);
    REQUIRE(vector3<glm::uvec3>);
    REQUIRE(vector3<glm::dvec3>);

    REQUIRE(not vector3<glm::vec4>);
    REQUIRE(not vector3<glm::ivec4>);
    REQUIRE(not vector3<glm::uvec4>);
    REQUIRE(not vector3<glm::dvec4>);
}

TEST_CASE("vector4:glm", "[vector][glm][4D]") {
    REQUIRE(not vector4<glm::vec2>);
    REQUIRE(not vector4<glm::ivec2>);
    REQUIRE(not vector4<glm::uvec2>);
    REQUIRE(not vector4<glm::dvec2>);

    REQUIRE(not vector4<glm::vec3>);
    REQUIRE(not vector4<glm::ivec3>);
    REQUIRE(not vector4<glm::uvec3>);
    REQUIRE(not vector4<glm::dvec3>);

    REQUIRE(vector4<glm::vec4>);
    REQUIRE(vector4<glm::ivec4>);
    REQUIRE(vector4<glm::uvec4>);
    REQUIRE(vector4<glm::dvec4>);
}

TEST_CASE("vector2:std::vector",
          "[vector][std::vector][2D]") {

    REQUIRE(not vector2<std::vector<int>>);
    REQUIRE(not vector2<std::vector<float>>);
    REQUIRE(not vector2<std::vector<std::complex<double>>>);
    REQUIRE(not vector2<std::vector<std::string>>);
}

TEST_CASE("vector3:std::vector",
          "[vector][std::vector][3D]") {

    REQUIRE(not vector3<std::vector<int>>);
    REQUIRE(not vector3<std::vector<float>>);
    REQUIRE(not vector3<std::vector<std::complex<double>>>);
    REQUIRE(not vector3<std::vector<std::string>>);
}

TEST_CASE("vector4:std::vector",
          "[vector][std::vector][4D]") {

    REQUIRE(not vector4<std::vector<int>>);
    REQUIRE(not vector4<std::vector<float>>);
    REQUIRE(not vector4<std::vector<std::complex<double>>>);
    REQUIRE(not vector4<std::vector<std::string>>);
}

TEST_CASE("vector2:std::string",
          "[vector][std::string][2D]") {

    REQUIRE(not vector2<std::string>);
    REQUIRE(not vector2<std::wstring>);
    REQUIRE(not vector2<std::u8string>);
    REQUIRE(not vector2<std::u16string>);
    REQUIRE(not vector2<std::u32string>);
}

TEST_CASE("vector3:std::string",
          "[vector][std::string][3D]") {

    REQUIRE(not vector3<std::string>);
    REQUIRE(not vector3<std::wstring>);
    REQUIRE(not vector3<std::u8string>);
    REQUIRE(not vector3<std::u16string>);
    REQUIRE(not vector3<std::u32string>);
}

TEST_CASE("vector4:std::string",
          "[vector][std::string][4D]") {

    REQUIRE(not vector4<std::string>);
    REQUIRE(not vector4<std::wstring>);
    REQUIRE(not vector4<std::u8string>);
    REQUIRE(not vector4<std::u16string>);
    REQUIRE(not vector4<std::u32string>);
}
