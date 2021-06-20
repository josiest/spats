#include <catch2/catch.hpp>
#include "kdtree.hpp"
#include <vector>
#include <stdexcept>

TEST_CASE("invalid inputs", "[kdtree][vector][invalid_argument]")
{
    using point = std::vector<int>;
    using kdtree = spats::kdtree<point, int>;
    constexpr auto dist = spats::L2sq<point, int>;

    std::vector<point> points;
    points.push_back(point{0, 2});
    points.push_back(point{1, -23, 3});
    points.push_back(point{-2, 1});

    REQUIRE_THROWS_AS(kdtree(points.begin(), points.end(), dist),
                      std::invalid_argument);
}
