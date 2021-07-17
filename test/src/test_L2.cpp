#include <gtest/gtest.h>
#include "spatula/geometry.hpp"

#include "util.hpp"
#include <vector>

#include <cstdlib>
#include <stdexcept>

TEST(L2Test, BetweenOrigin)
{
    using point = std::vector<int>;
    constexpr auto dist = spatula::L2<point>;

    point const a{0, 0};
    point const b{0, 0};
    EXPECT_EQ(dist(a, b), 0);
}

TEST(L2Test, BetweenOriginCustomPoint)
{
    using point = Vector2i;
    constexpr auto dist = spatula::L2<point>;

    point const a{0, 0};
    point const b{0, 0};
    EXPECT_EQ(dist(a, b), 0);
}

TEST(L2Test, BetweenRandomIntVecAndOrigin)
{
    using point = Vector2i;
    constexpr auto dist = spatula::L2<point>;

    point const a{0, 0};
    point const b{11, 5};
    EXPECT_EQ(dist(a, b), 146);
}

TEST(L2Test, BetweenRandomRealVecAndOrigin)
{
    using point = std::vector<double>;
    constexpr auto dist = spatula::L2<point>;

    point const a{78.7270, 16.1431, 16.9849};
    point const b{0, 0, 0};
    EXPECT_LT(std::abs(dist(a, b) - 6747.02), 0.01);
}

TEST(L2Test, BetweenRandomRealPoints)
{
    using point = std::vector<float>;
    constexpr auto dist = spatula::L2<point>;

    point const a{0.050760, 0.999944, 0.868459, 0.954534, 0.926416};
    point const b{0.184868, 0.553611, 0.972474, 0.364502, 0.552099};
    EXPECT_LT(std::abs(dist(a, b) - 0.7162), 0.0001);
}

TEST(L2Test, BetweenIncompatibleDimensions)
{
    using point = std::vector<double>;
    constexpr auto dist = spatula::L2<point>;

    point const a{1, 2};
    point const b{3, 4, 5};
    EXPECT_THROW(dist(a, b), std::invalid_argument);
}
