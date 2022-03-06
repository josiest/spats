#include <catch2/catch.hpp>
#include "spatula/vectors.hpp"
#include <vector>
#include <string>

using namespace sp;

struct ipoint2x1 { int x, y; };
struct fpoint2x1 { float x, y; };

struct ipoint2X1 { int X, Y; };
struct fpoint2X1 { float X, Y; };

struct ipoint3x1 { int x, y, z; };
struct dpoint3x1 { double x, y, z; };

struct chpoint3X1 { char X, Y, Z; };
struct dpoint3X1 { double X, Y, Z; };

TEST_CASE("has_x_component", "[has_component]") {
    REQUIRE(has_x_component<ipoint2x1>);
    REQUIRE(has_x_component<fpoint2x1>);
    REQUIRE(has_x_component<ipoint3x1>);
    REQUIRE(has_x_component<dpoint3x1>);

    REQUIRE(not has_x_component<ipoint2X1>);
    REQUIRE(not has_x_component<fpoint2X1>);
    REQUIRE(not has_x_component<chpoint3X1>);
    REQUIRE(not has_x_component<dpoint3X1>);
    REQUIRE(not has_x_component<std::vector<int>>);
    REQUIRE(not has_x_component<std::string>);
}

TEST_CASE("has_X_component", "[has_component]") {
    REQUIRE(has_X_component<ipoint2X1>);
    REQUIRE(has_X_component<fpoint2X1>);
    REQUIRE(has_X_component<chpoint3X1>);
    REQUIRE(has_X_component<dpoint3X1>);

    REQUIRE(not has_X_component<ipoint2x1>);
    REQUIRE(not has_X_component<fpoint2x1>);
    REQUIRE(not has_X_component<ipoint3x1>);
    REQUIRE(not has_X_component<dpoint3x1>);
    REQUIRE(not has_X_component<std::vector<int>>);
    REQUIRE(not has_X_component<std::string>);
}

TEST_CASE("has_y_component", "[has_component]") {
    REQUIRE(has_y_component<ipoint2x1>);
    REQUIRE(has_y_component<fpoint2x1>);
    REQUIRE(has_y_component<ipoint3x1>);
    REQUIRE(has_y_component<dpoint3x1>);

    REQUIRE(not has_y_component<ipoint2X1>);
    REQUIRE(not has_y_component<fpoint2X1>);
    REQUIRE(not has_y_component<chpoint3X1>);
    REQUIRE(not has_y_component<dpoint3X1>);
    REQUIRE(not has_y_component<std::vector<int>>);
    REQUIRE(not has_y_component<std::string>);
}

TEST_CASE("has_Y_component", "[has_component]") {
    REQUIRE(has_Y_component<ipoint2X1>);
    REQUIRE(has_Y_component<fpoint2X1>);
    REQUIRE(has_Y_component<chpoint3X1>);
    REQUIRE(has_Y_component<dpoint3X1>);

    REQUIRE(not has_Y_component<ipoint2x1>);
    REQUIRE(not has_Y_component<fpoint2x1>);
    REQUIRE(not has_Y_component<ipoint3x1>);
    REQUIRE(not has_Y_component<dpoint3x1>);
    REQUIRE(not has_Y_component<std::vector<int>>);
    REQUIRE(not has_Y_component<std::string>);
}
TEST_CASE("has_z_component", "[has_component]") {
    REQUIRE(has_z_component<ipoint3x1>);
    REQUIRE(has_z_component<dpoint3x1>);

    REQUIRE(not has_z_component<ipoint2x1>);
    REQUIRE(not has_z_component<fpoint2x1>);
    REQUIRE(not has_z_component<ipoint2X1>);
    REQUIRE(not has_z_component<fpoint2X1>);
    REQUIRE(not has_z_component<chpoint3X1>);
    REQUIRE(not has_z_component<dpoint3X1>);
    REQUIRE(not has_z_component<std::vector<int>>);
    REQUIRE(not has_z_component<std::string>);
}

TEST_CASE("has_Z_component", "[has_component]") {
    REQUIRE(has_Z_component<chpoint3X1>);
    REQUIRE(has_Z_component<dpoint3X1>);

    REQUIRE(not has_Z_component<ipoint2X1>);
    REQUIRE(not has_Z_component<fpoint2X1>);
    REQUIRE(not has_Z_component<ipoint2x1>);
    REQUIRE(not has_Z_component<fpoint2x1>);
    REQUIRE(not has_Z_component<ipoint3x1>);
    REQUIRE(not has_Z_component<dpoint3x1>);
    REQUIRE(not has_Z_component<std::vector<int>>);
    REQUIRE(not has_Z_component<std::string>);
}

TEST_CASE("has_i_component", "[has_component]") {

    REQUIRE(has_i_component<std::vector<double>>);
    REQUIRE(has_i_component<std::string>);

    REQUIRE(not has_i_component<ipoint2X1>);
    REQUIRE(not has_i_component<fpoint2X1>);
    REQUIRE(not has_i_component<chpoint3X1>);
    REQUIRE(not has_i_component<dpoint3X1>);

    REQUIRE(not has_i_component<ipoint2x1>);
    REQUIRE(not has_i_component<fpoint2x1>);
    REQUIRE(not has_i_component<ipoint3x1>);
    REQUIRE(not has_i_component<dpoint3x1>);
}
