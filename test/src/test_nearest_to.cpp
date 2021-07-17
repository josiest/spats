// testing
#include <gtest/gtest.h>
#include "spatula/kdtree.hpp"
#include "spatula/geometry.hpp"

// data structures
#include "util.hpp"
#include <vector>

// utility
#include <cstdlib>
#include <stdexcept>

namespace sp = spatula;

TEST(NearestToTest, EmptyTreeWithKas0)
{
    using point = std::vector<int>;
    using kdtree = sp::kdtree<point>;
    auto constexpr dist = sp::L2<point>;

    std::vector<point> points;
    kdtree index(points.begin(), points.end());

    point const p{0, 0};
    auto found = index.nearest_to(p, 0, dist);

    EXPECT_TRUE(found.empty());
}

TEST(NearestToTest, EmptyTreeWithKas1)
{
    using point = std::vector<float>;

    std::vector<point> points;
    sp::kdtree index(points);

    point const p{1.0f, 2.0f};
    auto found = index.nearest_to(p);

    EXPECT_TRUE(found.empty());
}

TEST(NearestToTest, SingletonTreeWithKas0)
{
    using point = std::vector<double>;
    using kdtree = sp::kdtree<point>;
    auto constexpr dist = sp::L2<point>;

    std::vector<point> points;
    points.push_back(point{0, 0});
    kdtree index(points.begin(), points.end());

    point const p{0.0, 0.0};
    auto found = index.nearest_to(p, 0, dist);

    EXPECT_TRUE(found.empty());
}

TEST(NearestToTest, SingletonOriginTreeNearestToOrigin)
{
    using point = std::vector<int>;
    auto constexpr dist = sp::L2<point>;

    std::vector<point> points;
    points.push_back(point{0, 0});
    sp::kdtree index(points);

    point const p{0, 0};
    auto found = index.nearest_to(p, 1, dist);

    EXPECT_EQ(found.size(), 1);
    EXPECT_EQ(found[0][0], 0);
    EXPECT_EQ(found[0][1], 0);
}

TEST(NearestToTest, SingletonRealTreeWithKas1)
{
    using point = std::vector<double>;
    auto constexpr dist = sp::L2<point>;

    std::vector<point> points;
    points.push_back(point{3.837089043, 3.367744091});
    sp::kdtree index(points);

    point const p{8.368067038, 3.221732361};
    auto found = index.nearest_to(p, 1, dist);

    EXPECT_EQ(found.size(), 1);
    point const & q = found[0];
    EXPECT_LT(std::abs(q[0] - 3.837089043), 0.000000001);
    EXPECT_LT(std::abs(q[1] - 3.367744091), 0.000000001);
}

TEST(NearestToTest, SingletonRealTreeWithKMoreThan1)
{
    using point = std::vector<float>;
    using kdtree = sp::kdtree<point>;
    auto constexpr dist = sp::L2<point>;

    std::vector<point> points;
    points.push_back(point{0.28f, 2.09f});
    kdtree index(points.begin(), points.end());

    point const p{12.35f, 5.95f};
    auto found = index.nearest_to(p, 3, dist);

    EXPECT_EQ(found.size(), 1);

    auto q = found[0];
    EXPECT_LT(std::abs(q[0] - 0.28f), 0.01f);
    EXPECT_LT(std::abs(q[1] - 2.09f), 0.01f);
}

TEST(NearestToTest, RandomIntTreeWithKMoreThanSize)
{
    using point = std::vector<int>;
    using kdtree = sp::kdtree<point>;
    auto constexpr dist = sp::L2<point>;

    std::vector<point> points;
    points.push_back(point{30, 43});
    points.push_back(point{85, 31});
    points.push_back(point{80, 43});
    kdtree index(points.begin(), points.end());

    point const p{40, 89};
    auto found = index.nearest_to(p, 4, dist);

    EXPECT_EQ(found.size(), 3);

    point const & q1 = found[0];
    EXPECT_EQ(q1[0], 30);
    EXPECT_EQ(q1[1], 43);
    
    point const & q2 = found[1];
    EXPECT_EQ(q2[0], 80);
    EXPECT_EQ(q2[1], 43);

    point const & q3 = found[2];
    EXPECT_EQ(q3[0], 85);
    EXPECT_EQ(q3[1], 31);
}

TEST(NearestToTest, RandomRealTreeWithKLessThanSize)
{
    using point = Vector3d;
    constexpr auto dist = sp::L2<point>;

    std::vector<point> points;
    points.push_back(point{94.29, 77.56, 27.34});
    points.push_back(point{83.24, 34.92, 24.6});
    points.push_back(point{31.72, 71.77, 86.23});
    points.push_back(point{13.79, 51.14, 9.46});
    points.push_back(point{31.66, 72.02, 45.94});
    sp::kdtree index(points);

    point const p{49.88, 98.03, 80.90};
    auto found = index.nearest_to(p, 2, dist);

    EXPECT_EQ(found.size(), 2);
    
    auto const & q1 = found[0];
    EXPECT_LT(std::abs(q1[0] - 31.72), 0.01);
    EXPECT_LT(std::abs(q1[1] - 71.77), 0.01);
    EXPECT_LT(std::abs(q1[2] - 86.23), 0.01);

    auto const & q2 = found[1];
    EXPECT_LT(std::abs(q2[0] - 31.66), 0.01);
    EXPECT_LT(std::abs(q2[1] - 72.02), 0.01);
    EXPECT_LT(std::abs(q2[2] - 45.94), 0.01);
}

TEST(NearestToTest, NegativeValuesPositiveQuery)
{
    using point = std::vector<double>;
    using kdtree = sp::kdtree<point>;

    std::vector<point> points;
    points.push_back(point{-68.05, -0.67});
    points.push_back(point{12.1, 51.7});
    kdtree index(points.begin(), points.end());

    point const p{1.2, 0};
    auto found = index.nearest_to(p);

    EXPECT_EQ(found.size(), 1);

    point const & q = found[0];
    EXPECT_LT(std::abs(q[0] - 12.1), 0.1);
    EXPECT_LT(std::abs(q[1] - 51.7), 0.1);
}

TEST(NearestToTest, NegativeValuesNegativeQuery)
{
    using point = std::vector<int>;

    std::vector<point> points;
    points.push_back(point{-2, 0});
    points.push_back(point{13, -23});
    points.push_back(point{-29, -32});
    sp::kdtree<point> index(points.begin(), points.end());

    point const p{-3, -2};
    auto found = index.nearest_to(p);
    EXPECT_EQ(found.size(), 1);

    point const & q = found.back();
    EXPECT_EQ(q[0], -2);
    EXPECT_EQ(q[1], 0);
}

TEST(NearestToTest, JustOutsideBoundingBox)
{
    using point = std::vector<double>;

    std::vector<point> points;
    points.push_back(point{0.32472, 0.63294});
    points.push_back(point{0.06862, 0.63722});
    sp::kdtree<point> index(points.begin(), points.end());

    point const p{0.06863, 0.37821};
    auto found = index.nearest_to(p);
    EXPECT_EQ(found.size(), 1);

    point const & q = found.back();
    EXPECT_LT(std::abs(q[0]-0.06862), 0.00001);
    EXPECT_LT(std::abs(q[1]-0.63722), 0.00001);
}

TEST(NearestToTest, FarOutsideBoundingBox)
{
    using point = std::vector<int>;

    std::vector<point> points;
    points.push_back(point{-3, 1});
    points.push_back(point{-1, 9});
    sp::kdtree<point> index(points.begin(), points.end());

    point const p{-2781, 2009};
    auto found = index.nearest_to(p);
    EXPECT_EQ(found.size(), 1);

    point const & q = found.back();
    EXPECT_EQ(q[0], -1);
    EXPECT_EQ(q[1], 9);
}

TEST(NearestToTest, IncompatiblePoint)
{
    using point = std::vector<int>;
    using kdtree = sp::kdtree<point>;

    std::vector<point> points;
    points.push_back(point{-1, 2, 13});
    kdtree index(points.begin(), points.end());

    point const p{0, 1};
    EXPECT_THROW(index.nearest_to(p), std::invalid_argument);
}

TEST(NearestToTest, MultipleCallsEmptyTree)
{
    using point = std::vector<int>;
    std::vector<point> points;
    sp::kdtree index(points);

    {
        point const p{1, 2};
        auto const found = index.nearest_to(p);
        EXPECT_TRUE(found.empty());
    }
    {
        point const p{0, 0};
        auto const found = index.nearest_to(p);
        EXPECT_TRUE(found.empty());
    }
}

TEST(NearestToTest, MultipleCallsSingletonTree)
{
    using point = std::vector<double>;

    std::vector<point> points;
    points.push_back(point{0.1, -3.2});
    sp::kdtree index(points);

    {
        point const p{-2, 4.8};
        auto const found = index.nearest_to(p, 7);
        EXPECT_EQ(found.size(), 1);

        auto const q = found.back();
        EXPECT_LT(std::abs(q[0]-0.1), 0.1);
        EXPECT_LT(std::abs(q[1]+3.2), 0.1);
    }
    {
        point const p{72, -108};
        auto const found = index.nearest_to(p, 7);
        EXPECT_EQ(found.size(), 1);

        auto const q = found.back();
        EXPECT_LT(std::abs(q[0]-0.1), 0.1);
        EXPECT_LT(std::abs(q[1]+3.2), 0.1);
    }
}

TEST(NearestToTest, MultipleCallsRandomTree)
{
    using point = std::vector<int>;
    std::vector<point> points{
        point{97, 18}, point{87, 12}, point{77, 1}, point{35, 44},
        point{70, 98}, point{37, 67}, point{91, 49}, point{87, 75},
        point{76, 11}, point{50, 81}
    };

    sp::kdtree index(points);
    {
        point const p{30, 59};
        auto const found = index.nearest_to(p);
        EXPECT_EQ(found.size(), 1);

        auto const q = found.back();
        EXPECT_EQ(q[0], 37);
        EXPECT_EQ(q[1], 67);
    }
    {
        point const p{86, 50};
        auto const found = index.nearest_to(p);
        EXPECT_EQ(found.size(), 1);

        auto const q = found.back();
        EXPECT_EQ(q[0], 91);
        EXPECT_EQ(q[1], 49);
    }
}

TEST(NearestToTest, MultipleCallsDifferentK)
{
    using point = std::vector<double>;
    std::vector<point> points{
        point{0.06401002, 0.86531857, 0.91255358},
        point{0.42437839, 0.49417762, 0.93911275},
        point{0.20925616, 0.94025944, 0.95517817},
        point{0.49702887, 0.05699803, 0.91081403},
        point{0.79188309, 0.20555514, 0.41013056},
        point{0.762743  , 0.28364261, 0.93471565},
        point{0.03226933, 0.71271885, 0.67170604},
        point{0.2534846 , 0.70316813, 0.54959815},
        point{0.48318503, 0.59268384, 0.40294836},
        point{0.04818292, 0.14127757, 0.9156365}
    };
    sp::kdtree index(points);
    {
        point const p{0.38055231, 0.51514748, 0.77579524};
        auto const found = index.nearest_to(p, 3);
        EXPECT_EQ(found.size(), 3);

        auto const q0 = found[0];
        EXPECT_EQ(q0.size(), 3);
        EXPECT_LT(std::abs(q0[0]-0.42437839), 0.001);
        EXPECT_LT(std::abs(q0[1]-0.49417762), 0.001);
        EXPECT_LT(std::abs(q0[2]-0.93911275), 0.001);

        auto const q1 = found[1];
        EXPECT_EQ(q1.size(), 3);
        EXPECT_LT(std::abs(q1[0]-0.2534846), 0.001);
        EXPECT_LT(std::abs(q1[1]-0.70316813), 0.001);
        EXPECT_LT(std::abs(q1[2]-0.54959815), 0.001);

        auto const q2 = found[2];
        EXPECT_EQ(q2.size(), 3);
        EXPECT_LT(std::abs(q2[0]-0.48318503), 0.001);
        EXPECT_LT(std::abs(q2[1]-0.59268384), 0.001);
        EXPECT_LT(std::abs(q2[2]-0.40294836), 0.001);
    }
    {
        point const p{0.58005779, 0.22356875, 0.08289481};
        auto const found = index.nearest_to(p, 5);
        EXPECT_EQ(found.size(), 5);

        auto const q0 = found[0];
        EXPECT_EQ(q0.size(), 3);
        EXPECT_LT(std::abs(q0[0]-0.79188309), 0.001);
        EXPECT_LT(std::abs(q0[1]-0.20555514), 0.001);
        EXPECT_LT(std::abs(q0[2]-0.41013056), 0.001);

        auto const q1 = found[1];
        EXPECT_EQ(q1.size(), 3);
        EXPECT_LT(std::abs(q1[0]-0.48318503), 0.001);
        EXPECT_LT(std::abs(q1[1]-0.59268384), 0.001);
        EXPECT_LT(std::abs(q1[2]-0.40294836), 0.001);

        auto const q2 = found[2];
        EXPECT_EQ(q2.size(), 3);
        EXPECT_LT(std::abs(q2[0]-0.2534846), 0.001);
        EXPECT_LT(std::abs(q2[1]-0.70316813), 0.001);
        EXPECT_LT(std::abs(q2[2]-0.54959815), 0.001);

        auto const q3 = found[3];
        EXPECT_EQ(q3.size(), 3);
        EXPECT_LT(std::abs(q3[0]-0.49702887), 0.001);
        EXPECT_LT(std::abs(q3[1]-0.05699803), 0.001);
        EXPECT_LT(std::abs(q3[2]-0.91081403), 0.001);

        auto const q4 = found[4];
        EXPECT_EQ(q4.size(), 3);
        EXPECT_LT(std::abs(q4[0]-0.762743), 0.001);
        EXPECT_LT(std::abs(q4[1]-0.28364261), 0.001);
        EXPECT_LT(std::abs(q4[2]-0.93471565), 0.001);
    }
}
