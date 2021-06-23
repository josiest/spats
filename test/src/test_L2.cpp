#include <catch2/catch.hpp>
#include "spatula/kdtree.hpp"

#include "util.hpp"
#include <vector>

#include <cstdlib>
#include <stdexcept>

TEST_CASE("distance bewteen integer vector origins", "[L2][vector]")
{
    using point = std::vector<int>;
    constexpr auto dist = spatula::L2<point, int>;

    point const a{0, 0};
    point const b{0, 0};
    REQUIRE(dist(a, b) == 0);
}

TEST_CASE("distance between custom integer points origins", "[L2][Vector2i]")
{
    using point = Vector2i;
    constexpr auto dist = spatula::L2<point, int>;
    point const a{0, 0};
    point const b{0, 0};
    REQUIRE(dist(a, b) == 0);
}

TEST_CASE("distance between random integer point and origin", "[L2][Vector2i]")
{
    using point = Vector2i;
    constexpr auto dist = spatula::L2<point, int>;
    point const a{0, 0};
    point const b{11, 5};
    REQUIRE(dist(a, b) == 146);
}

TEST_CASE("distance between random real point and origin",
          "[L2][vector][abs]")
{
    using point = std::vector<double>;
    constexpr auto dist = spatula::L2<point, double>;
    point const a{78.7270, 16.1431, 16.9849};
    point const b{0, 0, 0};
    REQUIRE(std::abs(dist(a, b) - 6747.02) < 0.01);
}

TEST_CASE("distance between two random real points", "[L2][vector][abs]")
{
    using point = std::vector<float>;
    constexpr auto dist = spatula::L2<point, float>;
    point const a{0.050760, 0.999944, 0.868459, 0.954534, 0.926416};
    point const b{0.184868, 0.553611, 0.972474, 0.364502, 0.552099};
    REQUIRE(std::abs(dist(a, b) - 0.7162) < 0.0001);
}

TEST_CASE("distance between incompatible points",
          "[L2][vector][invalid_argument]")
{
    using point = std::vector<double>;
    constexpr auto dist = spatula::L2<point, double>;
    point const a{1, 2};
    point const b{3, 4, 5};
    REQUIRE_THROWS_AS(dist(a, b), std::invalid_argument);
}
