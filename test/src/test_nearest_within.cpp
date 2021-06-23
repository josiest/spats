#include <catch2/catch.hpp>
#include "spatula/kdtree.hpp"

#include "util.hpp"
#include <vector>

#include <cstdlib>
#include <stdexcept>

TEST_CASE("empty tree", "[kdtree][vector]")
{
    using point = std::vector<int>;
    constexpr auto dist = spats::L2sq<point, int>;

    std::vector<point> points;
    spats::kdtree<point, int> index(points.begin(), points.end(), dist);

    point const p{0, 0};
    auto found = index.nearest_within(p, 1, 1);
    REQUIRE(found.empty());
}

TEST_CASE("singleton integer point tree with k = 0", "[kdtree][vector]")
{
    using point = std::vector<int>;
    constexpr auto dist = spats::L2sq<point, int>;

    std::vector<point> points;
    points.push_back(point{0, 0});
    spats::kdtree<point, int> index(points.begin(), points.end(), dist);

    point const p{0, 0};
    auto found = index.nearest_within(p, 1, 0);
    REQUIRE(found.empty());
}

TEST_CASE("singleton real point tree with points within radius",
          "[kdtree][vector][abs]")
{
    using point = std::vector<double>;
    constexpr auto dist = spats::L2sq<point, double>;

    std::vector<point> points;
    points.push_back(point{3.909, 6.154});
    spats::kdtree<point, double> index(points.begin(), points.end(), dist);

    point const p{8.514, 6.342};
    auto found = index.nearest_within(p, 5.0, 3);
    REQUIRE(found.size() == 1);


    point const & q = found.back();
    REQUIRE(std::abs(q[0] - 3.909) < 0.001);
    REQUIRE(std::abs(q[1] - 6.154) < 0.001);
}

TEST_CASE("random integer point tree with no points within radius",
          "[kdtree][vector]")
{
    using point = std::vector<int>;
    using kdtree = spats::kdtree<point, int>;
    constexpr auto dist = spats::L2sq<point, int>;

    std::vector<point> points;
    points.push_back(point{65, 64});
    points.push_back(point{97, 15});
    points.push_back(point{14, 21});
    kdtree index(points.begin(), points.end(), dist);

    point const p{4, 67};
    auto found = index.nearest_within(p, 40, 2);
    REQUIRE(found.empty());
}

TEST_CASE(
    "random integer point tree with less points within radius than k and negatives",
    "[kdtree][vector]")
{
    using point = std::vector<int>;
    using kdtree = spats::kdtree<point, int>;
    constexpr auto dist = spats::L2sq<point, int>;

    std::vector<point> points;
    points.push_back(point{4, -1});
    points.push_back(point{-10, -1});
    points.push_back(point{-9, 1});
    points.push_back(point{5, -4});
    points.push_back(point{-8, 1});
    kdtree index(points.begin(), points.end(), dist);

    point const p{9, 5};
    size_t const k = 3;
    auto found = index.nearest_within(p, 10, k);
    REQUIRE(found.size() == 2);

    point const & q1 = found[0];
    REQUIRE(q1[0] == 4);
    REQUIRE(q1[1] == -1);

    point const & q2 = found[1];
    REQUIRE(q2[0] == 5);
    REQUIRE(q2[1] == -4);
}

TEST_CASE(
    "random real point tree with less points in tree than k and negative values"
    "[kdtree][Vector3d][abs]")
{
    using point = Vector3d;
    using kdtree = spats::kdtree<point, double>;
    constexpr auto dist = spats::L2sq<point, double>;

    std::vector<point> points;
    points.push_back(point{75.892, -0.514, 53.958});
    points.push_back(point{7.810, -16.497, 70.660});
    kdtree index(points.begin(), points.end(), dist);

    point const p{58.711, -88.995, 20.744};
    size_t const k = 3;
    UNSCOPED_INFO("about to search");
    auto found = index.nearest_within(p, 150.0, k);
    UNSCOPED_INFO("finished searcing");
    REQUIRE(found.size() == k);

    point const & q1 = found[0];
    REQUIRE(std::abs(q1[0]-(75.892)) < 0.001);
    REQUIRE(std::abs(q1[1]-(-0.514)) < 0.001);
    REQUIRE(std::abs(q1[2]-(53.958)) < 0.001);

    point const & q2 = found[0];
    REQUIRE(std::abs(q2[0]-(7.810)) < 0.001);
    REQUIRE(std::abs(q2[1]-(-16.497)) < 0.001);
    REQUIRE(std::abs(q2[2]-(70.660)) < 0.001);
}

TEST_CASE("random tree with r = 0",
          "[kdtree][vector][invalid_argument]")
{
    using point = std::vector<double>;
    using kdtree = spats::kdtree<point, double>;
    constexpr auto dist = spats::L2sq<point, double>;

    std::vector<point> points;
    points.push_back(point{13.29, -20.3});
    points.push_back(point{-21.2, -92.33});
    kdtree index(points.begin(), points.end(), dist);

    point const p{93.2, -83.0};
    REQUIRE_THROWS_AS(index.nearest_within(p, 0, 1), std::invalid_argument);
}

TEST_CASE("random tree with negative r",
          "[kdtree][vector][invalid_argument]")
{
    using point = std::vector<double>;
    using kdtree = spats::kdtree<point, double>;
    constexpr auto dist = spats::L2sq<point, double>;

    std::vector<point> points;
    points.push_back(point{-30, 20});
    points.push_back(point{13, 23});
    kdtree index(points.begin(), points.end(), dist);

    point const p{-2, -3};
    REQUIRE_THROWS_AS(index.nearest_within(p, -2, 13), std::invalid_argument);
}

TEST_CASE("incompatible input point", "[kdtree][vector][invalid_argument]")
{
    using point = std::vector<int>;
    using kdtree = spats::kdtree<point, int>;
    constexpr auto dist = spats::L2sq<point, int>;

    std::vector<point> points;
    points.push_back(point{2, 3});
    kdtree index(points.begin(), points.end(), dist);

    point const p{0, 1, 2};
    REQUIRE_THROWS_AS(index.nearest_within(p, 1, 1), std::invalid_argument);
}
