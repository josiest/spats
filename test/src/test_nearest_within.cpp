// project
#include <gtest/gtest.h>
#include "spatula/kdtree.hpp"
#include "spatula/geometry.hpp"

// point types
#include "util.hpp"
#include <vector>

// utilities
#include <cstdlib>
#include <stdexcept>

TEST(NearestWithinTest, EmptyTree)
{
    using point = std::vector<int>;
    using kdtree = spatula::kdtree<point>;
    constexpr auto L2 = spatula::L2<point>;

    std::vector<point> points;
    spatula::kdtree<point> index(points.begin(), points.end());

    point const p{0, 0};
    auto found = index.nearest_within(p, 1, 1, L2);
    EXPECT_TRUE(found.empty());
}

TEST(NearestWithinTest, SingletonTreeWithKas0)
{
    using point = std::vector<int>;
    constexpr auto L2 = spatula::L2<point>;

    std::vector<point> points;
    points.push_back(point{0, 0});
    spatula::kdtree<point> index(points.begin(), points.end());

    point const p{0, 0};
    auto found = index.nearest_within(p, 1, 0, L2);
    EXPECT_TRUE(found.empty());
}

TEST(NearestWithinTest, SingletonTreeWithPointsWithinRadius)
{
    using point = std::vector<double>;
    constexpr auto L2 = spatula::L2<point>;

    std::vector<point> points;
    points.push_back(point{3.909, 6.154});
    spatula::kdtree<point> index(points.begin(), points.end());

    point const p{8.514, 6.342};
    auto found = index.nearest_within(p, 5.0, 3, L2);
    EXPECT_EQ(found.size(), 1);


    point const & q = found.back();
    EXPECT_LT(std::abs(q[0] - 3.909), 0.001);
    EXPECT_LT(std::abs(q[1] - 6.154), 0.001);
}

TEST(NearestWithinTest, RandomTreeWithNoPointsInRadius)
{
    using point = std::vector<int>;
    using kdtree = spatula::kdtree<point>;
    constexpr auto L2 = spatula::L2<point>;

    std::vector<point> points;
    points.push_back(point{65, 64});
    points.push_back(point{97, 15});
    points.push_back(point{14, 21});
    kdtree index(points.begin(), points.end());

    point const p{4, 67};
    auto found = index.nearest_within(p, 40, 2, L2);
    EXPECT_TRUE(found.empty());
}

TEST(NearestWithinTest, RandomTreeWithLessPointsInRadiusThanK)
{
    using point = std::vector<int>;
    using kdtree = spatula::kdtree<point>;
    constexpr auto L2 = spatula::L2<point>;

    std::vector<point> points;
    points.push_back(point{4, -1});
    points.push_back(point{-10, -1});
    points.push_back(point{-9, 1});
    points.push_back(point{5, -4});
    points.push_back(point{-8, 1});
    kdtree index(points.begin(), points.end());

    point const p{9, 5};
    size_t const k = 3;
    auto found = index.nearest_within(p, 10, k);
    EXPECT_EQ(found.size(), 2);

    point const & q1 = found[0];
    EXPECT_EQ(q1[0], 4);
    EXPECT_EQ(q1[1], -1);

    point const & q2 = found[1];
    EXPECT_EQ(q2[0], 5);
    EXPECT_EQ(q2[1], -4);
}

TEST(NearestWithinTest, RandomTreeWithNegativeValues)
{
    using point = Vector3d;
    using kdtree = spatula::kdtree<point>;
    constexpr auto L2 = spatula::L2<point>;

    std::vector<point> points;
    points.push_back(point{75.892, -0.514, 53.958});
    points.push_back(point{7.810, -16.497, 70.660});
    kdtree index(points.begin(), points.end());

    point const p{58.711, -88.995, 20.744};
    size_t const k = 3;
    auto found = index.nearest_within(p, 150.0, k);
    EXPECT_EQ(found.size(), 2);

    point const & q1 = found[0];
    EXPECT_LT(std::abs(q1[0]-(75.892)), 0.001);
    EXPECT_LT(std::abs(q1[1]-(-0.514)), 0.001);
    EXPECT_LT(std::abs(q1[2]-(53.958)), 0.001);

    point const & q2 = found[1];
    EXPECT_LT(std::abs(q2[0]-(7.810)), 0.001);
    EXPECT_LT(std::abs(q2[1]-(-16.497)), 0.001);
    EXPECT_LT(std::abs(q2[2]-(70.660)), 0.001);
}

TEST(NearestWithinTest, RandomTreeWithZeroRadius)
{
    using point = std::vector<double>;
    using kdtree = spatula::kdtree<point>;
    constexpr auto L2 = spatula::L2<point>;

    std::vector<point> points;
    points.push_back(point{13.29, -20.3});
    points.push_back(point{-21.2, -92.33});
    kdtree index(points.begin(), points.end());

    point const p{93.2, -83.0};
    EXPECT_THROW(index.nearest_within(p, 0, 1), std::invalid_argument);
}

TEST(NearestWithinTest, RandomTreeWithNegativeRadius)
{
    using point = std::vector<double>;
    using kdtree = spatula::kdtree<point>;
    constexpr auto L2 = spatula::L2<point>;

    std::vector<point> points;
    points.push_back(point{-30, 20});
    points.push_back(point{13, 23});
    kdtree index(points.begin(), points.end());

    point const p{-2, -3};
    EXPECT_THROW(index.nearest_within(p, -2, 13), std::invalid_argument);
}

TEST(NearestWithinTest, InocmpatiblePoints)
{
    using point = std::vector<int>;
    using kdtree = spatula::kdtree<point>;
    constexpr auto L2 = spatula::L2<point>;

    std::vector<point> points;
    points.push_back(point{2, 3});
    kdtree index(points.begin(), points.end());

    point const p{0, 1, 2};
    EXPECT_THROW(index.nearest_within(p, 1, 1), std::invalid_argument);
}
