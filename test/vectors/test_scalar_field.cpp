#include <catch2/catch.hpp>
#include "spatula/vectors.hpp"
#include <concepts>

#include <vector>
#include <array>
#include <string>
#include <cstddef>

#include <SDL2/SDL.h>
#include <SFML/System.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

using namespace sp;

struct chpoint3x2 { char x, y, z; };
struct ipoint3x2 { int x, y, z; };
struct lpoint2x2 { long x, y; };
struct fpoint3x2 { float x, y, z; };
struct dpoint2x2 { double x, y; };

struct chpoint2x2 { char X, Y; };
struct ipoint2X2 { int X, Y; };
struct lpoint3X2 { long X, Y, Z; };
struct fpoint2X2 { float X, Y; };
struct dpoint3X2 { double X, Y, Z; };

struct comp_and_idx_vec {
    int x, y, z;
    int & operator[](std::size_t i)
    {
        if (i % 3 == 0) { return x; }
        else if (i % 3 == 1) { return y; }
        else { return z; }
    }
    int const & operator[](std::size_t i) const
    {
        if (i % 3 == 0) { return x; }
        else if (i % 3 == 1) { return y; }
        else { return z; }
    }
};

TEST_CASE("scalar field: x component", "[scalar_field]") {
    REQUIRE(std::same_as<scalar_field_t<chpoint3x2>, char>);
    REQUIRE(std::same_as<scalar_field_t<ipoint3x2>, int>);
    REQUIRE(std::same_as<scalar_field_t<lpoint2x2>, long>);
    REQUIRE(std::same_as<scalar_field_t<fpoint3x2>, float>);
    REQUIRE(std::same_as<scalar_field_t<dpoint2x2>, double>);
}

TEST_CASE("scalar field: X component", "[scalar_field]") {
    REQUIRE(std::same_as<scalar_field_t<chpoint2x2>, char>);
    REQUIRE(std::same_as<scalar_field_t<ipoint2X2>, int>);
    REQUIRE(std::same_as<scalar_field_t<lpoint3X2>, long>);
    REQUIRE(std::same_as<scalar_field_t<fpoint2X2>, float>);
    REQUIRE(std::same_as<scalar_field_t<dpoint3X2>, double>);
}

TEST_CASE("scalar field: vector i component", "[scalar_field]") {
    REQUIRE(std::same_as<scalar_field_t<std::vector<int>>, int>);
    REQUIRE(std::same_as<scalar_field_t<std::vector<char>>, char>);
    REQUIRE(std::same_as<scalar_field_t<std::vector<double>>, double>);
}

TEST_CASE("scalar field: string i component", "[scalar_field]") {
    REQUIRE(std::same_as<scalar_field_t<std::string>, char>);
    REQUIRE(std::same_as<scalar_field_t<std::wstring>, wchar_t>);
    REQUIRE(std::same_as<scalar_field_t<std::u8string>, char8_t>);
}

TEST_CASE("scalar field: i and x component", "[scalar_field]") {
    REQUIRE(std::same_as<scalar_field_t<comp_and_idx_vec>, int>);
}

TEST_CASE("scalar field: sdl spatial structs", "[scalar_field]") {
    REQUIRE(std::same_as<scalar_field_t<SDL_Point>, int>);
    REQUIRE(std::same_as<scalar_field_t<SDL_Rect>, int>);
}

TEST_CASE("scalar field: sfml vectors", "[scalar_field]") {
    REQUIRE(std::same_as<scalar_field_t<sf::Vector2i>, int>);
    REQUIRE(std::same_as<scalar_field_t<sf::Vector2u>, unsigned int>);
    REQUIRE(std::same_as<scalar_field_t<sf::Vector2f>, float>);

    REQUIRE(std::same_as<scalar_field_t<sf::Vector3i>, int>);
    REQUIRE(std::same_as<scalar_field_t<sf::Vector3f>, float>);
}

TEST_CASE("scalar field: glm vectors", "[scalar_field]") {
    REQUIRE(std::same_as<scalar_field_t<glm::vec2>, float>);
    REQUIRE(std::same_as<scalar_field_t<glm::vec3>, float>);
    REQUIRE(std::same_as<scalar_field_t<glm::vec4>, float>);

    REQUIRE(std::same_as<scalar_field_t<glm::dvec2>, double>);
    REQUIRE(std::same_as<scalar_field_t<glm::dvec3>, double>);
    REQUIRE(std::same_as<scalar_field_t<glm::dvec4>, double>);

    REQUIRE(std::same_as<scalar_field_t<glm::ivec2>, int>);
    REQUIRE(std::same_as<scalar_field_t<glm::ivec3>, int>);
    REQUIRE(std::same_as<scalar_field_t<glm::ivec4>, int>);
}
