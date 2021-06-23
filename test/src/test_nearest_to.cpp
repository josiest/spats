// testing
#include <catch2/catch.hpp>
#include "spatula/kdtree.hpp"

// data structures
#include "util.hpp"
#include <vector>

// utility
#include <cstdlib>
#include <stdexcept>

TEST_CASE("empty tree with k = 0", "[kdtree][vector]")
{
    using point = std::vector<int>;
    std::vector<point> points;
    spats::kdtree<point, int> index(points.begin(), points.end(),
                                    spats::L2sq<point, int>);

    point const p{0, 0};
    auto found = index.nearest_to(p, 0);

    REQUIRE(found.empty());
}

TEST_CASE("empty tree with k = 1", "[kdtree][vector]")
{
    using point = std::vector<float>;
    std::vector<point> points;
    spats::kdtree<point, float> index(points.begin(), points.end(),
                                      spats::L2sq<point, float>);

    point const p{1.0f, 2.0f};
    auto found = index.nearest_to(p, 1);

    REQUIRE(found.empty());
}

TEST_CASE("singleton tree with k = 0", "[kdtree][vector]")
{
    using point = std::vector<double>;
    std::vector<point> points;
    points.push_back(point{0, 0});
    spats::kdtree<point> index(points.begin(), points.end(),
                               spats::L2sq<point, double>);

    point const p{0.0, 0.0};
    auto found = index.nearest_to(p, 0);

    REQUIRE(found.empty());
}

TEST_CASE("singleton origin tree with k = 1, p = origin", "[kdtree][vector]")
{
    using point = std::vector<int>;
    std::vector<point> points;
    points.push_back(point{0, 0});
    spats::kdtree<point, int> index(points.begin(), points.end(),
                                    spats::L2sq<point, int>);

    point const p{0, 0};
    auto found = index.nearest_to(p, 1);

    REQUIRE(found.size() == 1);
    REQUIRE(found[0][0] == 0);
    REQUIRE(found[0][1] == 0);
}

TEST_CASE("singleton random tree with k = 1",
          "[kdtree][vector][abs]")
{
    using point = std::vector<double>;
    std::vector<point> points;
    points.push_back(point{3.837089043, 3.367744091});
    spats::kdtree<point> index(points.begin(), points.end(),
                               spats::L2sq<point, double>);

    point const p{8.368067038, 3.221732361};
    auto found = index.nearest_to(p, 1);

    REQUIRE(found.size() == 1);
    point const & q = found[0];
    REQUIRE(std::abs(q[0] - 3.837089043) < 0.000000001);
    REQUIRE(std::abs(q[1] - 3.367744091) < 0.000000001);
}

TEST_CASE("singleton random tree with k > 1",
          "[kdtree][vector][abs]")
{
    using point = std::vector<float>;
    std::vector<point> points;
    points.push_back(point{0.28f, 2.09f});
    spats::kdtree<point, float> index(points.begin(), points.end(),
                                      spats::L2sq<point, float>);

    point const p{12.35f, 5.95f};
    auto found = index.nearest_to(p, 3);

    REQUIRE(found.size() == 1);

    auto q = found[0];
    REQUIRE(std::abs(q[0] - 0.28f) < 0.01f);
    REQUIRE(std::abs(q[1] - 2.09f) < 0.01f);
}

TEST_CASE("random tree with k > tree size", "[kdtree][vector]")
{
    using point = std::vector<int>;
    std::vector<point> points;
    points.push_back(point{30, 43});
    points.push_back(point{85, 31});
    points.push_back(point{80, 43});
    spats::kdtree<point, int> index(points.begin(), points.end(),
                                    spats::L2sq<point, int>);

    point const p{40, 89};
    auto found = index.nearest_to(p, 4);

    REQUIRE(found.size() == 3);

    point const & q1 = found[0];
    REQUIRE(q1[0] == 30);
    REQUIRE(q1[1] == 43);
    
    point const & q2 = found[1];
    REQUIRE(q2[0] == 80);
    REQUIRE(q2[1] == 43);

    point const & q3 = found[2];
    REQUIRE(q3[0] == 85);
    REQUIRE(q3[1] == 31);
}

TEST_CASE("random tree with k < tree size", "[kdtree][vector][abs]")
{
    using point = Vector3d;
    using kdtree = spats::kdtree<point, double>;
    constexpr auto dist = spats::L2sq<point, double>;

    std::vector<point> points;
    points.push_back(point{94.29, 77.56, 27.34});
    points.push_back(point{83.24, 34.92, 24.6});
    points.push_back(point{31.72, 71.77, 86.23});
    points.push_back(point{13.79, 51.14, 9.46});
    points.push_back(point{31.66, 72.02, 45.94});
    kdtree index(points.begin(), points.end(), dist);

    point const p{49.88, 98.03, 80.90};
    auto found = index.nearest_to(p, 2);

    REQUIRE(found.size() == 2);
    
    auto const & q1 = found[0];
    REQUIRE(std::abs(q1[0] - 31.72) < 0.01);
    REQUIRE(std::abs(q1[1] - 71.77) < 0.01);
    REQUIRE(std::abs(q1[2] - 86.23) < 0.01);

    auto const & q2 = found[1];
    REQUIRE(std::abs(q2[0] - 31.66) < 0.01);
    REQUIRE(std::abs(q2[1] - 72.02) < 0.01);
    REQUIRE(std::abs(q2[2] - 45.94) < 0.01);
}

TEST_CASE("random tree with negative values but positive query",
          "[kdtree][vector][abs]")
{
    using point = std::vector<double>;
    using kdtree = spats::kdtree<point, double>;
    constexpr auto dist = spats::L2sq<point, double>;

    std::vector<point> points;
    points.push_back(point{-68.05, -0.67});
    points.push_back(point{12.1, 51.7});
    UNSCOPED_INFO("points size: " << points.size());
    kdtree index(points.begin(), points.end(), dist);

    point const p{1.2, 0};
    INFO("about to search");
    auto found = index.nearest_to(p);
    INFO("finished search");

    REQUIRE(found.size() == 1);

    point const & q = found[0];
    REQUIRE(std::abs(q[0] - 12.1) < 0.1);
    REQUIRE(std::abs(q[1] - 51.7) < 0.1);
}

TEST_CASE("random tree with negative values and query", "[kdtree][vector]")
{
    using point = std::vector<int>;
    std::vector<point> points;
    points.push_back(point{-2, 0});
    points.push_back(point{13, -23});
    points.push_back(point{-29, -32});
    spats::kdtree<point, int> index(points.begin(), points.end(),
                                    spats::L2sq<point, int>);

    point const p{-3, -2};
    auto found = index.nearest_to(p);
    REQUIRE(found.size() == 1);

    point const & q = found.back();
    REQUIRE(q[0] == -2);
    REQUIRE(q[1] == 0);
}

TEST_CASE("query just outside of bounding box", "[kdtree][vector][abs]")
{
    using point = std::vector<double>;
    std::vector<point> points;
    points.push_back(point{0.32472, 0.63294});
    points.push_back(point{0.06862, 0.63722});
    spats::kdtree<point> index(points.begin(), points.end(),
                               spats::L2sq<point, double>);

    point const p{0.06863, 0.37821};
    auto found = index.nearest_to(p);
    REQUIRE(found.size() == 1);

    point const & q = found.back();
    REQUIRE(std::abs(q[0]-0.06862) < 0.00001);
    REQUIRE(std::abs(q[1]-0.63722) < 0.00001);
}

TEST_CASE("query far outside of bounding box", "[kdtree][vector]")
{
    using point = std::vector<int>;
    std::vector<point> points;
    points.push_back(point{-3, 1});
    points.push_back(point{-1, 9});
    spats::kdtree<point, int> index(points.begin(), points.end(),
                                    spats::L2sq<point, int>);

    point const p{-2781, 2009};
    auto found = index.nearest_to(p);
    REQUIRE(found.size() == 1);

    point const & q = found.back();
    REQUIRE(q[0] == -1);
    REQUIRE(q[1] == 9);
}

TEST_CASE("nearest_to incompatible input point",
          "[kdtree][vector][invalid_argument]")
{
    using point = std::vector<int>;
    using kdtree = spats::kdtree<point, int>;
    constexpr auto dist = spats::L2sq<point, int>;

    std::vector<point> points;
    points.push_back(point{-1, 2, 13});
    kdtree index(points.begin(), points.end(), dist);

    point const p{0, 1};
    REQUIRE_THROWS_AS(index.nearest_to(p), std::invalid_argument);
}
