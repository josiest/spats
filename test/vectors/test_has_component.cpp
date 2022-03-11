#include <catch2/catch.hpp>

#include "spatula/vectors.hpp"

#include <SDL2/SDL.h>
#include <SFML/System.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <Eigen/Dense>
#include <spatula_extensions/eigen.hpp>

#include <vector>
#include <string>

namespace test_has_component {

struct point2ix { int x, y; };
struct point2fx { float x, y; };

struct point2iX { int X, Y; };
struct point3chX { char X, Y, Z; };

struct point2fX { float X, Y; };
struct point3ix { int x, y, z; };

struct point3dx { double x, y, z; };
struct point3dX { double X, Y, Z; };

struct point4chx { char x, y, z, w; };
struct point4fX { float X, Y, Z, W; };
}

namespace eig = Eigen;

using namespace sp;
using namespace test_has_component;

TEST_CASE("has-x-component", "[has_component]") {
    REQUIRE(has_x_component<point2ix>);
    REQUIRE(has_x_component<point2fx>);
    REQUIRE(has_x_component<point3ix>);
    REQUIRE(has_x_component<point3dx>);

    REQUIRE(not has_x_component<point2iX>);
    REQUIRE(not has_x_component<point2fX>);
    REQUIRE(not has_x_component<point3chX>);
    REQUIRE(not has_x_component<point3dX>);

    REQUIRE(has_x_component<SDL_Point>);
    REQUIRE(has_x_component<sf::Vector2i>);
    REQUIRE(has_x_component<sf::Vector2f>);
    REQUIRE(has_x_component<sf::Vector3f>);

    REQUIRE(has_x_component<glm::ivec2>);
    REQUIRE(has_x_component<glm::vec3>);
    REQUIRE(has_x_component<glm::dvec4>);

    REQUIRE(not has_x_component<eig::Vector2d>);
    REQUIRE(not has_x_component<eig::Vector3cd>);
    REQUIRE(not has_x_component<eig::Vector4i>);

    REQUIRE(not has_x_component<std::vector<int>>);
    REQUIRE(not has_x_component<std::string>);
}

TEST_CASE("has-X-component", "[has_component]") {
    REQUIRE(has_X_component<point2iX>);
    REQUIRE(has_X_component<point2fX>);
    REQUIRE(has_X_component<point3chX>);
    REQUIRE(has_X_component<point3dX>);

    REQUIRE(not has_X_component<SDL_Point>);
    REQUIRE(not has_X_component<sf::Vector2i>);
    REQUIRE(not has_X_component<sf::Vector2f>);
    REQUIRE(not has_X_component<sf::Vector3f>);

    REQUIRE(not has_X_component<glm::ivec2>);
    REQUIRE(not has_X_component<glm::vec3>);
    REQUIRE(not has_X_component<glm::dvec4>);

    REQUIRE(not has_X_component<eig::Vector2d>);
    REQUIRE(not has_X_component<eig::Vector3cd>);
    REQUIRE(not has_X_component<eig::Vector4i>);

    REQUIRE(not has_X_component<point2ix>);
    REQUIRE(not has_X_component<point2fx>);
    REQUIRE(not has_X_component<point3ix>);
    REQUIRE(not has_X_component<point3dx>);
    REQUIRE(not has_X_component<std::vector<int>>);
    REQUIRE(not has_X_component<std::string>);
}

TEST_CASE("has-y-component", "[has_component]") {
    REQUIRE(has_y_component<point2ix>);
    REQUIRE(has_y_component<point2fx>);
    REQUIRE(has_y_component<point3ix>);
    REQUIRE(has_y_component<point3dx>);

    REQUIRE(has_y_component<SDL_Point>);
    REQUIRE(has_y_component<sf::Vector2f>);
    REQUIRE(has_y_component<sf::Vector2u>);
    REQUIRE(has_y_component<sf::Vector3i>);

    REQUIRE(has_y_component<glm::dvec2>);
    REQUIRE(has_y_component<glm::uvec3>);
    REQUIRE(has_y_component<glm::vec4>);

    REQUIRE(not has_y_component<eig::Vector2i>);
    REQUIRE(not has_y_component<eig::Vector3d>);
    REQUIRE(not has_y_component<eig::Vector4cf>);

    REQUIRE(not has_y_component<point2iX>);
    REQUIRE(not has_y_component<point2fX>);
    REQUIRE(not has_y_component<point3chX>);
    REQUIRE(not has_y_component<point3dX>);
    REQUIRE(not has_y_component<std::vector<int>>);
    REQUIRE(not has_y_component<std::string>);
}

TEST_CASE("has-Y-component", "[has_component]") {
    REQUIRE(has_Y_component<point2iX>);
    REQUIRE(has_Y_component<point2fX>);
    REQUIRE(has_Y_component<point3chX>);
    REQUIRE(has_Y_component<point3dX>);

    REQUIRE(not has_Y_component<SDL_Point>);
    REQUIRE(not has_Y_component<sf::Vector2u>);
    REQUIRE(not has_Y_component<sf::Vector2i>);
    REQUIRE(not has_Y_component<sf::Vector3f>);

    REQUIRE(not has_Y_component<glm::dvec2>);
    REQUIRE(not has_Y_component<glm::ivec3>);
    REQUIRE(not has_Y_component<glm::vec4>);

    REQUIRE(not has_Y_component<eig::Vector2i>);
    REQUIRE(not has_Y_component<eig::Vector3cf>);
    REQUIRE(not has_Y_component<eig::Vector4f>);

    REQUIRE(not has_Y_component<point2ix>);
    REQUIRE(not has_Y_component<point2fx>);
    REQUIRE(not has_Y_component<point3ix>);
    REQUIRE(not has_Y_component<point3dx>);
    REQUIRE(not has_Y_component<std::vector<int>>);
    REQUIRE(not has_Y_component<std::string>);
}
TEST_CASE("has-z-component", "[has_component]") {
    REQUIRE(has_z_component<point3ix>);
    REQUIRE(has_z_component<point3dx>);

    REQUIRE(not has_z_component<SDL_Point>);
    REQUIRE(not has_z_component<sf::Vector2f>);
    REQUIRE(not has_z_component<sf::Vector2i>);
    REQUIRE(has_z_component<sf::Vector3i>);

    REQUIRE(not has_z_component<glm::ivec2>);
    REQUIRE(has_z_component<glm::vec3>);
    REQUIRE(has_z_component<glm::dvec4>);

    REQUIRE(not has_z_component<eig::Vector2cd>);
    REQUIRE(not has_z_component<eig::Vector3i>);
    REQUIRE(not has_z_component<eig::Vector4f>);

    REQUIRE(not has_z_component<point2ix>);
    REQUIRE(not has_z_component<point2fx>);
    REQUIRE(not has_z_component<point2iX>);
    REQUIRE(not has_z_component<point2fX>);
    REQUIRE(not has_z_component<point3chX>);
    REQUIRE(not has_z_component<point3dX>);
    REQUIRE(not has_z_component<std::vector<int>>);
    REQUIRE(not has_z_component<std::string>);
}

TEST_CASE("has-Z-component", "[has_component]") {
    REQUIRE(has_Z_component<point3chX>);
    REQUIRE(has_Z_component<point3dX>);

    REQUIRE(not has_Z_component<SDL_Point>);
    REQUIRE(not has_Z_component<sf::Vector2f>);
    REQUIRE(not has_Z_component<sf::Vector2i>);
    REQUIRE(not has_Z_component<sf::Vector3i>);

    REQUIRE(not has_Z_component<glm::vec2>);
    REQUIRE(not has_Z_component<glm::vec3>);
    REQUIRE(not has_Z_component<glm::vec4>);

    REQUIRE(not has_Z_component<eig::Vector2cd>);
    REQUIRE(not has_Z_component<eig::Vector3i>);
    REQUIRE(not has_Z_component<eig::Vector4d>);

    REQUIRE(not has_Z_component<point2iX>);
    REQUIRE(not has_Z_component<point2fX>);
    REQUIRE(not has_Z_component<point2ix>);
    REQUIRE(not has_Z_component<point2fx>);
    REQUIRE(not has_Z_component<point3ix>);
    REQUIRE(not has_Z_component<point3dx>);
    REQUIRE(not has_Z_component<std::vector<int>>);
    REQUIRE(not has_Z_component<std::string>);
}

TEST_CASE("has-w-component", "[has_component]") {
    REQUIRE(has_w_component<point4chx>);
    REQUIRE(has_w_component<glm::vec4>);
    REQUIRE(has_w_component<glm::ivec4>);
    REQUIRE(has_w_component<glm::dvec4>);

    REQUIRE(not has_w_component<SDL_Point>);
    REQUIRE(not has_w_component<sf::Vector2f>);
    REQUIRE(not has_w_component<sf::Vector2i>);
    REQUIRE(not has_w_component<sf::Vector3i>);

    REQUIRE(not has_w_component<glm::ivec2>);
    REQUIRE(not has_w_component<glm::vec3>);
    REQUIRE(has_w_component<glm::dvec4>);

    REQUIRE(not has_w_component<eig::Vector2cd>);
    REQUIRE(not has_w_component<eig::Vector3i>);
    REQUIRE(not has_w_component<eig::Vector4f>);

    REQUIRE(not has_w_component<point4fX>);
    REQUIRE(not has_w_component<std::vector<float>>);
    REQUIRE(not has_w_component<std::string>);
}

TEST_CASE("has-W-component", "[has_component]") {
    REQUIRE(has_W_component<point4fX>);

    REQUIRE(not has_W_component<SDL_Point>);
    REQUIRE(not has_W_component<sf::Vector2f>);
    REQUIRE(not has_W_component<sf::Vector2i>);
    REQUIRE(not has_W_component<sf::Vector3i>);

    REQUIRE(not has_W_component<glm::vec2>);
    REQUIRE(not has_W_component<glm::vec3>);
    REQUIRE(not has_W_component<glm::vec4>);

    REQUIRE(not has_W_component<eig::Vector2cd>);
    REQUIRE(not has_W_component<eig::Vector3i>);
    REQUIRE(not has_W_component<eig::Vector4d>);

    REQUIRE(not has_W_component<point2fX>);
    REQUIRE(not has_W_component<point3dX>);
    REQUIRE(not has_W_component<SDL_Point>);
    REQUIRE(not has_W_component<glm::vec3>);
    REQUIRE(not has_W_component<std::string>);
    REQUIRE(not has_W_component<std::vector<double>>);
}

TEST_CASE("has-i-component", "[has_component]") {

    REQUIRE(has_i_component<std::vector<double>>);
    REQUIRE(has_i_component<std::string>);

    REQUIRE(not has_i_component<point2iX>);
    REQUIRE(not has_i_component<point2fX>);
    REQUIRE(not has_i_component<point3chX>);
    REQUIRE(not has_i_component<point3dX>);

    REQUIRE(not has_i_component<point2ix>);
    REQUIRE(not has_i_component<point2fx>);
    REQUIRE(not has_i_component<point3ix>);
    REQUIRE(not has_i_component<point3dx>);

    REQUIRE(has_i_component<eig::Vector2i>);
    REQUIRE(has_i_component<eig::Vector3d>);
    REQUIRE(has_i_component<eig::Vector4cf>);

    REQUIRE(has_i_component<glm::vec2>);
    REQUIRE(has_i_component<glm::ivec3>);
    REQUIRE(has_i_component<glm::dvec4>);
}

TEST_CASE("has-1d-component", "[has_component]") {
    REQUIRE(has_1d_component<point2ix>);
    REQUIRE(has_1d_component<SDL_Point>);

    REQUIRE(has_1d_component<glm::vec2>);
    REQUIRE(has_1d_component<glm::ivec3>);
    REQUIRE(has_1d_component<glm::dvec4>);

    REQUIRE(has_1d_component<sf::Vector2f>);
    REQUIRE(has_1d_component<sf::Vector3i>);

    REQUIRE(has_1d_component<eig::Vector2i>);
    REQUIRE(has_1d_component<eig::Vector4f>);

    REQUIRE(has_1d_component<std::array<float, 2>>);
    REQUIRE(has_1d_component<std::array<long, 4>>);

    REQUIRE(not has_1d_component<std::vector<int>>);
    REQUIRE(not has_1d_component<std::vector<float>>);
    REQUIRE(not has_1d_component<std::vector<std::string>>);
    REQUIRE(not has_1d_component<std::string>);
}

TEST_CASE("has-2d-component", "[has_component]") {
    REQUIRE(has_2d_component<point2ix>);
    REQUIRE(has_2d_component<SDL_Point>);

    REQUIRE(has_2d_component<glm::vec2>);
    REQUIRE(has_2d_component<glm::ivec3>);
    REQUIRE(has_2d_component<glm::dvec4>);

    REQUIRE(has_2d_component<sf::Vector2f>);
    REQUIRE(has_2d_component<sf::Vector3i>);

    REQUIRE(has_2d_component<eig::Vector2d>);
    REQUIRE(has_2d_component<eig::Vector3i>);

    REQUIRE(has_2d_component<std::array<float, 2>>);
    REQUIRE(has_2d_component<std::array<long, 4>>);
    REQUIRE(not has_2d_component<std::array<double, 1>>);

    REQUIRE(not has_2d_component<std::vector<long>>);
    REQUIRE(not has_2d_component<std::vector<double>>);
    REQUIRE(not has_2d_component<std::vector<std::string>>);
    REQUIRE(not has_2d_component<std::string>);
}

TEST_CASE("has-3d-component", "[has_component]") {
    REQUIRE(not has_3d_component<point2fx>);
    REQUIRE(not has_3d_component<SDL_Point>);

    REQUIRE(not has_3d_component<glm::dvec2>);
    REQUIRE(has_3d_component<glm::vec3>);
    REQUIRE(has_3d_component<glm::ivec4>);

    REQUIRE(not has_3d_component<sf::Vector2u>);
    REQUIRE(has_3d_component<sf::Vector3f>);

    REQUIRE(not has_3d_component<eig::Vector2cf>);
    REQUIRE(has_3d_component<eig::Vector3d>);
    REQUIRE(has_3d_component<eig::Vector4i>);

    REQUIRE(has_3d_component<std::array<int, 3>>);
    REQUIRE(has_3d_component<std::array<short, 4>>);
    REQUIRE(not has_3d_component<std::array<float, 2>>);

    REQUIRE(not has_3d_component<std::vector<char>>);
    REQUIRE(not has_3d_component<std::vector<float>>);
    REQUIRE(not has_3d_component<std::vector<std::string>>);
    REQUIRE(not has_3d_component<std::string>);
}

TEST_CASE("has-4d-component", "[has_component]") {
    REQUIRE(not has_4d_component<point2fx>);
    REQUIRE(not has_4d_component<SDL_Point>);

    REQUIRE(not has_4d_component<glm::ivec2>);
    REQUIRE(not has_4d_component<glm::dvec3>);
    REQUIRE(has_4d_component<glm::vec4>);

    REQUIRE(not has_4d_component<sf::Vector2f>);
    REQUIRE(not has_4d_component<sf::Vector3i>);

    REQUIRE(not has_4d_component<eig::Vector2cd>);
    REQUIRE(not has_4d_component<eig::Vector3f>);
    REQUIRE(has_4d_component<eig::Vector4i>);

    REQUIRE(has_4d_component<std::array<double, 4>>);
    REQUIRE(not has_4d_component<std::array<float, 3>>);
    REQUIRE(not has_4d_component<std::array<int, 2>>);

    REQUIRE(not has_4d_component<std::vector<char>>);
    REQUIRE(not has_4d_component<std::vector<float>>);
    REQUIRE(not has_4d_component<std::vector<std::string>>);
    REQUIRE(not has_4d_component<std::string>);
}
