#include <catch2/catch.hpp>
#include "spatula/vectors.hpp"
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
    REQUIRE(not has_x_component<std::vector<int>>);
    REQUIRE(not has_x_component<std::string>);
}

TEST_CASE("has-X-component", "[has_component]") {
    REQUIRE(has_X_component<point2iX>);
    REQUIRE(has_X_component<point2fX>);
    REQUIRE(has_X_component<point3chX>);
    REQUIRE(has_X_component<point3dX>);

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

    REQUIRE(not has_w_component<point4fX>);
    REQUIRE(not has_w_component<std::vector<float>>);
    REQUIRE(not has_w_component<std::string>);
}

TEST_CASE("has-W-component", "[has_component]") {
    REQUIRE(has_W_component<point4fX>);

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
}

TEST_CASE("has-1d-component", "[has_component]") {
    REQUIRE(has_1d_component<point2ix>);
    REQUIRE(has_1d_component<SDL_Point>);

    REQUIRE(has_1d_component<glm::vec2>);
    REQUIRE(has_1d_component<glm::ivec3>);
    REQUIRE(has_1d_component<glm::dvec4>);
}
